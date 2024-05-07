// IR Proximity Sensor constants
const int proximitySensorPin = 2;
const int ledPin = 13;

// L298N Motor Driver constants
const int leftMotorEnablePin = 9;
const int leftMotorForwardPin = 8;
const int leftMotorBackwardPin = 7;

const int rightMotorEnablePin = 3;
const int rightMotorForwardPin = 5;
const int rightMotorBackwardPin = 4;

void setup()
{
    // Initialize digital pins as outputs
    pinMode(ledPin, OUTPUT);
    pinMode(proximitySensorPin, INPUT);
    pinMode(leftMotorEnablePin, OUTPUT);
    pinMode(leftMotorForwardPin, OUTPUT);
    pinMode(leftMotorBackwardPin, OUTPUT);
    pinMode(rightMotorEnablePin, OUTPUT);
    pinMode(rightMotorForwardPin, OUTPUT);
    pinMode(rightMotorBackwardPin, OUTPUT);

    // Initialize motors to stopped state
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorBackwardPin, LOW);
}

void loop()
{
    int sensorState = digitalRead(proximitySensorPin);

    if (sensorState == HIGH)
    {
        digitalWrite(ledPin, HIGH); // Set LED on if obstacle detected
        stopMotors();               // Stop motors if obstacle detected
    }
    else
    {
        digitalWrite(ledPin, LOW); // Set LED off if no obstacle detected
        moveForward();             // Move forward if no obstacle detected
    }

    delay(100);
}

void moveForward()
{
    // Set motor speeds to maximum
    analogWrite(leftMotorEnablePin, 255);
    analogWrite(rightMotorEnablePin, 255);

    // Turn on motors in forward direction
    digitalWrite(leftMotorForwardPin, HIGH);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, HIGH);
    digitalWrite(rightMotorBackwardPin, LOW);
}

void moveBackward()
{
    // Set motor speeds to maximum
    analogWrite(leftMotorEnablePin, 255);
    analogWrite(rightMotorEnablePin, 255);

    // Turn on motors in backward direction
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorBackwardPin, HIGH);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorBackwardPin, HIGH);
}

void stopMotors()
{
    digitalWrite(leftMotorForwardPin, LOW);
    digitalWrite(leftMotorBackwardPin, LOW);
    digitalWrite(rightMotorForwardPin, LOW);
    digitalWrite(rightMotorBackwardPin, LOW);
}