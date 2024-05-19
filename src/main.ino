#include <SoftwareSerial.h>

// Pin definitions
const uint8_t kProximitySensorPin = 2;
const uint8_t kLedPin = 13;

// L298N Motor Driver pins
const uint8_t kLeftMotorEnablePin = 9;
const uint8_t kLeftMotorForwardPin = 8;
const uint8_t kLeftMotorBackwardPin = 7;
const uint8_t kRightMotorEnablePin = 3;
const uint8_t kRightMotorForwardPin = 5;
const uint8_t kRightMotorBackwardPin = 4;

// Motor speed constants
const uint8_t kMotorStopSpeed = 0;
const uint8_t kMotorMaxSpeed = 255;
uint8_t currentSpeed = kMotorMaxSpeed;

// Web control serial communication
const uint8_t kWebControlRxPin = 10;
const uint8_t kWebControlTxPin = 11;

SoftwareSerial webControlSerial(kWebControlRxPin, kWebControlTxPin);

void setup()
{
    pinMode(kLedPin, OUTPUT);
    pinMode(kProximitySensorPin, INPUT_PULLUP);
    pinMode(kLeftMotorEnablePin, OUTPUT);
    pinMode(kLeftMotorForwardPin, OUTPUT);
    pinMode(kLeftMotorBackwardPin, OUTPUT);
    pinMode(kRightMotorEnablePin, OUTPUT);
    pinMode(kRightMotorForwardPin, OUTPUT);
    pinMode(kRightMotorBackwardPin, OUTPUT);

    webControlSerial.begin(9600);
    Serial.begin(9600);

    stopMotors();
}

void loop()
{
    bool obstacleDetected = !digitalRead(kProximitySensorPin);
    Serial.print("IR Status: ");
    Serial.println(obstacleDetected ? "Obstacle Detected" : "No Obstacle");

    if (obstacleDetected)
    {
        digitalWrite(kLedPin, HIGH);
        stopMotors();
    }
    else
    {
        digitalWrite(kLedPin, LOW);
        if (webControlSerial.available() > 0)
        {
            String command = webControlSerial.readStringUntil('\n');
            Serial.println(command);
            handleCommand(command);
        }
    }
    delay(100);
}

void handleCommand(String command)
{
    if (command.startsWith("L"))
    {
        moveLeft(currentSpeed);
    }
    else if (command.startsWith("R"))
    {
        moveRight(currentSpeed);
    }
    else if (command.startsWith("S"))
    {
        stopMotors();
    }
    else if (command.startsWith("SP"))
    {
        int speed = command.substring(2).toInt();
        setSpeed(speed);
    }
    else
    {
        Serial.println("Invalid command");
    }
}

void moveLeft(uint8_t speed)
{
    analogWrite(kLeftMotorEnablePin, speed);
    digitalWrite(kLeftMotorForwardPin, LOW);
    digitalWrite(kLeftMotorBackwardPin, HIGH);
    analogWrite(kRightMotorEnablePin, speed);
    digitalWrite(kRightMotorForwardPin, LOW);
    digitalWrite(kRightMotorBackwardPin, HIGH);
}

void moveRight(uint8_t speed)
{
    analogWrite(kRightMotorEnablePin, speed);
    digitalWrite(kLeftMotorForwardPin, HIGH);
    digitalWrite(kLeftMotorBackwardPin, LOW);
    analogWrite(kLeftMotorEnablePin, speed);
    digitalWrite(kRightMotorForwardPin, HIGH);
    digitalWrite(kRightMotorBackwardPin, LOW);
}

void stopMotors()
{
    analogWrite(kLeftMotorEnablePin, kMotorStopSpeed);
    analogWrite(kRightMotorEnablePin, kMotorStopSpeed);
    digitalWrite(kLeftMotorForwardPin, LOW);
    digitalWrite(kLeftMotorBackwardPin, LOW);
    digitalWrite(kRightMotorForwardPin, LOW);
    digitalWrite(kRightMotorBackwardPin, LOW);
}

void setSpeed(uint8_t speed)
{
    currentSpeed = speed;
    Serial.print("Speed set to: ");
    Serial.println(speed);
}
