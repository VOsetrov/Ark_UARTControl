#Arduino Nano Boat Control Project (C Language)

##Project Overview

This project is a remote-controlled boat using an Arduino Nano and an Android 
app. The boat is controlled by a servo motor for steering and a water pump for 
propulsion. The Arduino receives commands from a mobile app via Bluetooth 
communication using an HM-10 module.

##Key Features

-Remote control of the boat using an Android app
-Servo motor for precise steering
-Water pump for propulsion
-Bluetooth communication for wireless control
-Arduino Nano for microcontroller capabilities

##Hardware Components

-Arduino Nano microcontroller board
-SG90 servo motor for steering
-5V water pump
-Relay to control the water pump
-NPN bipolar transistor 2N2219
-HM-10 Bluetooth module for communication with the mobile app
-2x Lithium-ion batteries for power supply
-7805 voltage regulator to provide stable 5V power

##Project Setup:

	1. Servo Motor Connection:
		- Connect the servo motor's signal wire to Arduino pin D9.
		- Connect the servo motor's power wires to an appropriate power source (5V).
	2. Bipolar Transistor:
		- Connect the transistor's collector to the relay module's control input.
		- Connect the transistor's base to Arduino pin D8.
		- Connect the transistor's emitter to ground.
		- Connect the relay module's power supply to an power source (5V).
	3. Water Pump Connection:
		- connect the water pump to the relay module's output terminals.
	4. HM-10 Bluetooth Module Connection:
		- Connect the HM-10 Bluetooth module's RX pin to Arduino pin D0.
		- Connect the HM-10 Bluetooth module's TX pin to Arduino pin D1.
		- Connect the HM-10 Bluetooth module's VCC pin to the power source (5V).
		- Connect the HM-10 Bluetooth module's GND pin to the ground.
	5. Battery and Voltage Regulator Connection:
		- Connect the batteries in series to the 7805 voltage regulator's input.
		- Connect the 7805 voltage regulator's output to the 5V power rail on the 
			Breatboard.
		- Connect the 7805 voltage regulator's ground to the GND rail on the 
			Breatboard.
	6. Product body:
		- Carry out according to your taste or following the drawings and 3D models.
		(ark_ucon_drawings.pdf)

##Software Setup:
	
	1. Install avr-gcc and necessary dependencies:
		- Follow the installation instructions for avr-gcc on your Linux system.
		- Ensure you have the required libraries and tools for compiling C code.
	2. Download the C code and Android app code:
		- Obtain the C code for boat control (assuming it is named main.c).
		- Get the Android .apk file (assuming it is named ark_ucon.apk).
	3. Compile the C code using avr-gcc and Makefile:
		- Open a terminal window and navigate to the project directory.
		- Run the 'make' command to compile the C code.
		- The compiled code will be named 'main.hex'.
	4. Flash the Arduino Nano:
		- Connect the Arduino Nano to your computer using a USB cable.
		- Use a programmer tool avrdude. The command is 'make deploy'

##Known Issues and Potential Improvements

1. Boat Weight and Pump Performance:
	- Issue: The initial boat design proved too heavy, causing the 5V water pump to 
	be underpowered. The weight increased significantly when the electrical 
	components were enclosed in a LEGO housing.
	###Potentional Solutions:
		1.1. Reduce boat weight: Explore weight-reduction techniques for the boat 
				 structure and components.
		1.2. Utilize two 5V pumps: Consider using two 5V pumps in parallel to provide 
				 sufficient water propulsion.
	
##Disclaimer

This project is for educational purposes only. Please use caution when handling 
electrical components and batteries. Always follow safety guidelines when working 
with electronics and water.
