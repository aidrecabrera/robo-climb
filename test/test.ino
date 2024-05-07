#include <Arduino.h>

// L298N Motor Driver pins
const uint8_t kLeftMotorEnablePin = 9;   // Left motor enable pin is connected to digital pin 9
const uint8_t kLeftMotorForwardPin = 8;  // Left motor forward pin is connected to digital pin 8
const uint8_t kLeftMotorBackwardPin = 7; // Left motor backward pin is connected to digital pin 7

const uint8_t kRightMotorEnablePin = 3;   // Right motor enable pin is connected to digital pin 3
const uint8_t kRightMotorForwardPin = 5;  // Right motor forward pin is connected to digital pin 5
const uint8_t kRightMotorBackwardPin = 4; // Right motor backward pin is connected to digital pin 4

// Motor speed constants
const uint8_t kMotorStopSpeed = 0;  // Motor stop speed is 0 (stopped)
const uint8_t kMotorMaxSpeed = 255; // Motor maximum speed is 255 (full speed)

void setup()
{
    // Initialize digital pins
    pinMode(kLeftMotorEnablePin, OUTPUT);             // Set left motor enable pin as output
    pinMode(kLeftMotorForwardPin, OUTPUT);            // Set left motor forward pin as output
    pinMode(kLeftMotorBackwardPin, OUTPUT);           // Set left motor backward pin as output
    pinMode(kRightMotorEnablePin, OUTPUT);            // Set right motor enable pin as output
    pinMode(kRightMotorForwardPin, OUTPUT);           // Set right motor forward pin as output
    pinMode(kRightMotorBackwardPin, OUTPUT);          // Set right motor backward pin as output
}

void loop()
{
    // Test left motor forward
    digitalWrite(kLeftMotorForwardPin, HIGH);
    digitalWrite(kLeftMotorBackwardPin, LOW);
    analogWrite(kLeftMotorEnablePin, kMotorMaxSpeed);
    delay(1000);

    // Test left motor backward
    digitalWrite(kLeftMotorForwardPin, LOW);
    digitalWrite(kLeftMotorBackwardPin, HIGH);
    analogWrite(kLeftMotorEnablePin, kMotorMaxSpeed);
    delay(1000);

    // Test right motor forward
    digitalWrite(kRightMotorForwardPin, HIGH);
    digitalWrite(kRightMotorBackwardPin, LOW);
    analogWrite(kRightMotorEnablePin, kMotorMaxSpeed);
    delay(1000);

    // Test right motor backward
    digitalWrite(kRightMotorForwardPin, LOW);
    digitalWrite(kRightMotorBackwardPin, HIGH);
    analogWrite(kRightMotorEnablePin, kMotorMaxSpeed);
    delay(1000);

    // Stop motors
    analogWrite(kLeftMotorEnablePin, kMotorStopSpeed);
    analogWrite(kRightMotorEnablePin, kMotorStopSpeed);
    delay(1000);
}