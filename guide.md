**ROBOCLIMB Assembly Guide**
================================

**Step 1: Motor Connections**
-----------------------------

| Motor | L298N Pin | Arduino Uno Pin |
| --- | --- | --- |
| Left Motor Forward | IN1 | Digital Pin 8 |
| Left Motor Backward | IN2 | Digital Pin 7 |
| Left Motor Enable | ENA | Digital Pin 9 |
| Right Motor Forward | IN3 | Digital Pin 5 |
| Right Motor Backward | IN4 | Digital Pin 4 |
| Right Motor Enable | ENB | Digital Pin 3 |

**Step 2: IR Proximity Sensor Connection**
-----------------------------------------

| Sensor | Arduino Uno Pin |
| --- | --- |
| VCC | 5V |
| GND | GND |
| OUT | Digital Pin 2 |

**Step 3: 3-Position Switch Connections**
-----------------------------------------

| Switch | Arduino Uno Pin |
| --- | --- |
| Common | Digital Pin 6 |
| Left | Digital Pin 5 |
| Right | Digital Pin 4 |

**Step 4: LED Indicator Connection**
-------------------------------------

| LED | Arduino Uno Pin |
| --- | --- |
| VCC | 5V |
| GND | GND |
| OUT | Digital Pin 13 |

**Step 5: Web Control Serial Connection**
-----------------------------------------

| Web Control | Arduino Uno Pin |
| --- | --- |
| RX | Digital Pin 10 |
| TX | Digital Pin 11 |

**Important Notes**
-------------------

* Make sure to connect the motors to the correct pins on the L298N motor driver.
* Use a breadboard or PCB to connect the components.
* Double-check the connections before powering on the robot.
* Make sure to use the correct power supply for the robot.

Here's a simple explanation of the pins on the Arduino Uno:

* Digital Pins: 0-13 (labeled as "Digital" on the board)
* Analog Pins: A0-A5 (labeled as "Analog" on the board)
* Power Pins: 5V, 3.3V, GND (labeled as "Power" on the board)