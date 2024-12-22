# ELE334-Embedded-Systems-Project

# Flappy Bird Game for TM4C123GH6PM Microcontroller

## Introduction

In This project,we implement a Flappy Bird game on the TM4C123GH6PM microcontroller using peripherals like GPIO, ADC, UART, and Timers. The game is displayed on a Nokia 5110 LCD screen, where a bird character moves vertically, avoiding poles that scroll horizontally across the screen. Players control the bird's movement using buttons, while gravity is dynamically adjusted based on input from the ADC module(Slider). The UART interface allows the user to set initial configurations (the game's speed).

## Features
1. Adjustable Game Speed: Players can choose the game speed via the UART console.
2. Dynamic Gravity: Gravity affecting the bird's descent can be controlled using an ADC-based input.
3. Button-Based Controls: The bird's ascent is controlled using a button.
4. Score Tracking: The score increments with each successful pass through the poles.
5. Increasing Difficulty: After six successful passes, the level increases which decreasing the slot size.
6. Collision Detection: Ensures the game ends when the bird collides with a pole or ground.

## Hardware Required
1. Tiva c launch bad 
2. Nokia5110 LCD 
3. Push Buttons 
4. LEDs 
5. Slider for ADC 
6. Jumper Wires

## How to Run the Game
1. Connect the TM4C123GH6PM to your development board and ensure all peripherals are connected.
2. Flash the provided code onto the microcontroller using an IDE like Keil uVision .
3. Open a UART console at 115200 baud rate and set the game speed.
4. Press SW2 to start the game.
5. Use SW1 to control the bird's movement.
6. Monitor your score and enjoy!

## License
This project is open-source and can be used for educational and personal purposes. Attribution to the original developer is appreciated.

