/**
 * ROBOCLIMB: IR Proximity Sensor and L298N Motor Driver Control with 3-Position Switch and Web Control
 *
 * DISCLAIMER: The verbose comments are for the group members to understand the code better
 * since they have no prior experience with programming. The comments are not necessary for
 * the code to function properly. The code is written in a way that it is self-explanatory.
 *
 * This code is designed to control a robot with two motors and an IR proximity sensor.
 * The robot can move left, right, or stop based on the position of a 3-position switch.
 * If an obstacle is detected by the IR proximity sensor, the robot will stop moving.
 * Additionally, the robot can be controlled using commands from a Python server.
 */

#include <SoftwareSerial.h>

// Pin definitions
const uint8_t kProximitySensorPin = 2; // IR proximity sensor is connected to digital pin 2
const uint8_t kLedPin = 13;            // LED indicator is connected to digital pin 13

// L298N Motor Driver pins
const uint8_t kLeftMotorEnablePin = 9;   // Left motor enable pin is connected to digital pin 9
const uint8_t kLeftMotorForwardPin = 8;  // Left motor forward pin is connected to digital pin 8
const uint8_t kLeftMotorBackwardPin = 7; // Left motor backward pin is connected to digital pin 7

const uint8_t kRightMotorEnablePin = 3;   // Right motor enable pin is connected to digital pin 3
const uint8_t kRightMotorForwardPin = 5;  // Right motor forward pin is connected to digital pin 5
const uint8_t kRightMotorBackwardPin = 4; // Right motor backward pin is connected to digital pin 4

// 3-Position Switch pins
const uint8_t kDirectionSwitchCommonPin = 6; // Common pin of the 3-position switch is connected to digital pin 6
const uint8_t kDirectionSwitchLeftPin = 5;   // Left pin of the 3-position switch is connected to digital pin 5
const uint8_t kDirectionSwitchRightPin = 4;  // Right pin of the 3-position switch is connected to digital pin 4

// Motor speed constants
const uint8_t kMotorStopSpeed = 0;  // Motor stop speed is 0 (stopped)
const uint8_t kMotorMaxSpeed = 255; // Motor maximum speed is 255 (full speed)

// Web control serial communication
const uint8_t kWebControlRxPin = 10; // Web control RX pin is connected to digital pin 10
const uint8_t kWebControlTxPin = 11; // Web control TX pin is connected to digital pin 11

SoftwareSerial webControlSerial(kWebControlRxPin, kWebControlTxPin); // Create a software serial object for web control communication

void setup()
{
    // Initialize digital pins
    pinMode(kLedPin, OUTPUT);                         // Set LED pin as output
    pinMode(kProximitySensorPin, INPUT_PULLUP);       // Set proximity sensor pin as input with internal pull-up resistor
    pinMode(kLeftMotorEnablePin, OUTPUT);             // Set left motor enable pin as output
    pinMode(kLeftMotorForwardPin, OUTPUT);            // Set left motor forward pin as output
    pinMode(kLeftMotorBackwardPin, OUTPUT);           // Set left motor backward pin as output
    pinMode(kRightMotorEnablePin, OUTPUT);            // Set right motor enable pin as output
    pinMode(kRightMotorForwardPin, OUTPUT);           // Set right motor forward pin as output
    pinMode(kRightMotorBackwardPin, OUTPUT);          // Set right motor backward pin as output
    pinMode(kDirectionSwitchCommonPin, INPUT_PULLUP); // Set switch common pin as input with internal pull-up resistor
    pinMode(kDirectionSwitchLeftPin, INPUT_PULLUP);   // Set switch left pin as input with internal pull-up resistor
    pinMode(kDirectionSwitchRightPin, INPUT_PULLUP);  // Set switch right pin as input with internal pull-up resistor

    // Initialize web control serial communication
    webControlSerial.begin(9600);
    Serial.begin(9600);

    // Initialize motors to stopped state
    stopMotors(); // Call the stopMotors function to stop the motors initially
}

void loop()
{
    // Read the state of the proximity sensor
    bool obstacleDetected = !digitalRead(kProximitySensorPin); // obstacleDetected will be true if an obstacle is detected

    // Print IR status
    Serial.print("IR Status: ");
    Serial.println(obstacleDetected ? "Obstacle Detected" : "No Obstacle");

    if (obstacleDetected)
    {
        digitalWrite(kLedPin, HIGH); // Turn on the LED to indicate an obstacle is detected
        stopMotors();                // Stop the motors if an obstacle is detected
    }
    else
    {
        digitalWrite(kLedPin, LOW); // Turn off the LED if no obstacle is detected

        // Read the state of the 3-position switch
        bool leftSwitchState = !digitalRead(kDirectionSwitchLeftPin);   // leftSwitchState will be true if the switch is in the left position
        bool rightSwitchState = !digitalRead(kDirectionSwitchRightPin); // rightSwitchState will be true if the switch is in the right position

        if (leftSwitchState && !rightSwitchState)
        {
            // If the switch is in the left position
            moveLeft(kMotorMaxSpeed); // Call the moveLeft function to move the robot left
        }
        else if (!leftSwitchState && rightSwitchState)
        {
            // If the switch is in the right position
            moveRight(kMotorMaxSpeed); // Call the moveRight function to move the robot right
        }
        else
        {
            // If the switch is in the middle position
            stopMotors(); // Call the stopMotors function to stop the robot
        }

        // Check for web control commands
        if (webControlSerial.available() > 0)
        {
            char command = webControlSerial.read();
            Serial.println(command); // Print the received command to serial monitor

            if (command == 'L')
            {
                moveLeft(kMotorMaxSpeed); // Move left at maximum speed
            }
            else if (command == 'R')
            {
                moveRight(kMotorMaxSpeed); // Move right at maximum speed
            }
            else if (command == 'S')
            {
                stopMotors(); // Stop the robot
            }
        }
    }

    delay(100); // Wait for 100 milliseconds (0.1 second) before checking again
}

void moveLeft(uint8_t speed)
{
    analogWrite(kLeftMotorEnablePin, speed);    // Set the speed of the left motor
    digitalWrite(kLeftMotorForwardPin, LOW);    // Set the left motor forward pin to LOW
    digitalWrite(kLeftMotorBackwardPin, HIGH);  // Set the left motor backward pin to HIGH
    digitalWrite(kRightMotorForwardPin, LOW);   // Set the right motor forward pin to LOW
    digitalWrite(kRightMotorBackwardPin, HIGH); // Set the right motor backward pin to HIGH
}

void moveRight(uint8_t speed)
{
    analogWrite(kRightMotorEnablePin, speed);  // Set the speed of the right motor
    digitalWrite(kLeftMotorForwardPin, HIGH);  // Set the left motor forward pin to HIGH
    digitalWrite(kLeftMotorBackwardPin, LOW);  // Set the left motor backward pin to LOW
    digitalWrite(kRightMotorForwardPin, HIGH); // Set the right motor forward pin to HIGH
    digitalWrite(kRightMotorBackwardPin, LOW); // Set the right motor backward pin to LOW
}

void stopMotors()
{
    analogWrite(kLeftMotorEnablePin, kMotorStopSpeed);  // Set the speed of the left motor to 0
    analogWrite(kRightMotorEnablePin, kMotorStopSpeed); // Set the speed of the right motor to 0
    digitalWrite(kLeftMotorForwardPin, LOW);            // Set the left motor forward pin to LOW
    digitalWrite(kLeftMotorBackwardPin, LOW);           // Set the left motor backward pin to LOW
    digitalWrite(kRightMotorForwardPin, LOW);           // Set the right motor forward pin to LOW
    digitalWrite(kRightMotorBackwardPin, LOW);          // Set the right motor backward pin to LOW
}
