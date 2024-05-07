/**
 * ROBOCLIMB: IR Proximity Sensor and L298N Motor Driver Control with 3-Position Switch with instructions for ground
 */

// IR Proximity Sensor constants
const int kProximitySensorPin = 2; // Connect IR proximity sensor to digital pin 2
const int kLedPin = 13;            // Connect LED to digital pin 13

// L298N Motor Driver constants
const int kLeftMotorEnablePin = 9;   // Connect left motor enable to digital pin 9
const int kLeftMotorForwardPin = 8;  // Connect left motor forward to digital pin 8
const int kLeftMotorBackwardPin = 7; // Connect left motor backward to digital pin 7

const int kRightMotorEnablePin = 3;   // Connect right motor enable to digital pin 3
const int kRightMotorForwardPin = 5;  // Connect right motor forward to digital pin 5
const int kRightMotorBackwardPin = 4; // Connect right motor backward to digital pin 4

// 3-Position Switch constants
const int kDirectionSwitchCommonPin = 6; // Connect switch common pin to digital pin 6
const int kDirectionSwitchLeftPin = 5;   // Connect switch left pin to digital pin 5
const int kDirectionSwitchRightPin = 4;  // Connect switch right pin to digital pin 4

void setup()
{
    // Initialize digital pins as outputs
    pinMode(kLedPin, OUTPUT);
    pinMode(kProximitySensorPin, INPUT);
    pinMode(kLeftMotorEnablePin, OUTPUT);
    pinMode(kLeftMotorForwardPin, OUTPUT);
    pinMode(kLeftMotorBackwardPin, OUTPUT);
    pinMode(kRightMotorEnablePin, OUTPUT);
    pinMode(kRightMotorForwardPin, OUTPUT);
    pinMode(kRightMotorBackwardPin, OUTPUT);
    pinMode(kDirectionSwitchCommonPin, INPUT); // Initialize switch common pin as input
    pinMode(kDirectionSwitchLeftPin, INPUT);   // Initialize switch left pin as input
    pinMode(kDirectionSwitchRightPin, INPUT);  // Initialize switch right pin as input

    // Initialize motors to stopped state
    digitalWrite(kLeftMotorForwardPin, LOW);
    digitalWrite(kLeftMotorBackwardPin, LOW);
    digitalWrite(kRightMotorForwardPin, LOW);
    digitalWrite(kRightMotorBackwardPin, LOW);
}

void loop()
{
    int sensorState = digitalRead(kProximitySensorPin);

    if (sensorState == HIGH)
    {
        digitalWrite(kLedPin, HIGH); // Set LED on if obstacle detected
        stopMotors();                // Stop motors if obstacle detected
    }
    else
    {
        digitalWrite(kLedPin, LOW); // Set LED off if no obstacle detected

        int leftSwitchState = digitalRead(kDirectionSwitchLeftPin);
        int rightSwitchState = digitalRead(kDirectionSwitchRightPin);

        if (leftSwitchState == HIGH && rightSwitchState == LOW)
        {
            // Switch is in left position
            moveLeft();
        }
        else if (leftSwitchState == LOW && rightSwitchState == HIGH)
        {
            // Switch is in right position
            moveRight();
        }
        else
        {
            // Switch is in middle position
            stopMotors();
        }
    }

    delay(100);
}

void moveLeft()
{
    // Set motor speeds to maximum
    analogWrite(kLeftMotorEnablePin, 255);
    analogWrite(kRightMotorEnablePin, 255);

    // Turn on motors in left direction
    digitalWrite(kLeftMotorForwardPin, LOW);
    digitalWrite(kLeftMotorBackwardPin, HIGH);
    digitalWrite(kRightMotorForwardPin, LOW);
    digitalWrite(kRightMotorBackwardPin, HIGH);
}

void moveRight()
{
    // Set motor speeds to maximum
    analogWrite(kLeftMotorEnablePin, 255);
    analogWrite(kRightMotorEnablePin, 255);

    // Turn on motors in right direction
    digitalWrite(kLeftMotorForwardPin, HIGH);
    digitalWrite(kLeftMotorBackwardPin, LOW);
    digitalWrite(kRightMotorForwardPin, HIGH);
    digitalWrite(kRightMotorBackwardPin, LOW);
}

void stopMotors()
{
    digitalWrite(kLeftMotorForwardPin, LOW);
    digitalWrite(kLeftMotorBackwardPin, LOW);
    digitalWrite(kRightMotorForwardPin, LOW);
    digitalWrite(kRightMotorBackwardPin, LOW);
}