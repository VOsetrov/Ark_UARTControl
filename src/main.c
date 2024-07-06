#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

enum {
  SERVO_MAX_RIGHT   = 250,
  SERVO_MAX_LEFT    = 500,          // 248 default
  SERVO_MID         = 375,
  BAUD              = 9600,
  FOSC              = 16000000,
  MYUBRR            = FOSC/16/BAUD-1,// (FOSC/(16*BAUD))-1
  BUT_L             = 97,           // Turn left button number (ASCII)
  BUT_R             = 100,
  BUT_MID           = 115,
  BUT_MOVE          = 119,
  BUT_STOP          = 101,
};

struct butt {
  unsigned char leftOn;
  unsigned char rightOn;
  unsigned char moveOn;
} butt;

static inline void portInit();
static inline void timerInit();
static inline void uartInit
  (unsigned int ubrr);
static inline void uart_send(char* str);
static inline void uart_boatControl
  (unsigned char data);
static inline void analog_boatControl(unsigned char bL,
  unsigned char bR, unsigned char mv);

int main(void)  
{
  portInit();
  timerInit();

  OCR1A = SERVO_MID;                // Set the Servo to midle (0 degree) 

  uartInit(MYUBRR);
  
  PORTD &= ~(1<<PD7);

  while(1) {
    uart_boatControl(UDR0);
 }
  return 0;
}

static inline void portInit() {
  DDRC &= ~(1<<DDC0);               // Set buttons ports direction to input  
  DDRC &= ~(1<<DDC1);
  DDRC &= ~(1<<DDC2);
  PORTC |= (1<<PORTC0);             // Apply 5v voltage to buttons ports 
  PORTC |= (1<<PORTC1);
  PORTC |= (1<<PORTC2);

  DDRB |= (1<<PB0);                 // Set output direction for Pump port pin
  PORTB &= ~(1<<PB0);               // Set 0V for Pump port
  DDRB |= (1<<PB1);                 // Set output direction for Servo port pin 
  PORTB &= ~(1<<PB1);               // Set 0V for servo port 
                                    
  DDRD |= (1<<PD7);
}

static inline void timerInit() {
  unsigned char sreg;

  TCCR1A |= (1<<COM1A1);            // Set the non-invert mode PWM 
  TCCR1A &= ~(1<<COM1A0);
  TCCR1A &= ~(1<<WGM10);            // Set the Fast PWM bit mode 
  TCCR1A |= (1<<WGM11);
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<WGM13);
  TCCR1B |= (1<<CS10);              // Set the prescaler CLKi/o/64
  TCCR1B |= (1<<CS11);
  TCCR1B &= ~(1<<CS12);

  sreg = SREG;                      // Disable global interrupt flag 
  cli();
  ICR1 = 5000;                      // Set the pulse width 

  SREG = sreg;                      // Restore global interrupt flag 
}

static inline void uartInit
  (unsigned int ubrr) {
  UBRR0H = (unsigned char)(ubrr>>8); // Set the BAUD rate in USART baud Rate 
  UBRR0L = (unsigned char)ubrr;     // Registers (to low & high)
  UCSR0B = 0b10011000;              // Set the RX&TX&Interrupt Rx enable
  UCSR0C &= ~(1<<USBS0);            // Set the 1 stop bit                       
  UCSR0C &= ~(1<<UCSZ02);           // Set the 8 bit package settings
  UCSR0C |= (1<<UCSZ01);             
  UCSR0C |= (1<<UCSZ00);
}

static inline void uart_send(char* str) {
  while(*str) {
    while(UCSR0A & (1<<UDRE0)) {    // While UDR is ready to recieve new data
      UDR0 = *str;
      str++;
    }
  }
}

static inline void uart_boatControl
  (unsigned char data) {
  
  while(!(UCSR0A & (1<<RXC0))) {
  };
 
  while (UCSR0A & (1<<RXC0)) {
    switch(UDR0) {
      case BUT_L:
        OCR1A = SERVO_MAX_LEFT;
        break;
      case BUT_R:
        OCR1A = SERVO_MAX_RIGHT;
        break;
      case BUT_MID:
        OCR1A = SERVO_MID;
        break;
      case BUT_MOVE:
        PORTB = (1<<PB0);
        break;
      case BUT_STOP:
        PORTB &= ~(1<<PB0);
        break;
      default:
        break;
      }
  }
}

static inline void analog_boatControl(unsigned char bL,
  unsigned char bR, unsigned char mv) {

  if (bL) {
    OCR1A = SERVO_MAX_LEFT;
  } else if (bR) {
    OCR1A = SERVO_MAX_RIGHT;
  } else if (mv) {
    PORTB |= (1<<PB0);
  } else {
    OCR1A = SERVO_MID;
    PORTB &= ~(1<<PB0);
  }

}
