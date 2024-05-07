#include <SoftwareSerial.h>

// Pin definitions
const uint8_t kProximitySensorPin = 2;
const uint8_t kLedPin = 13;

const uint8_t kLeftMotorEnablePin = 9;
const uint8_t kLeftMotorForwardPin = 8;
const uint8_t kLeftMotorBackwardPin = 7;

const uint8_t kRightMotorEnablePin = 3;
const uint8_t kRightMotorForwardPin = 5;
const uint8_t kRightMotorBackwardPin = 4;

const uint8_t kDirectionSwitchCommonPin = 6;
const uint8_t kDirectionSwitchLeftPin = 5;
const uint8_t kDirectionSwitchRightPin = 4;

const uint8_t kWebControlRxPin = 10;
const uint8_t kWebControlTxPin = 11;

SoftwareSerial webControlSerial(kWebControlRxPin, kWebControlTxPin);

const uint8_t kMotorStopSpeed = 0;
const uint8_t kMotorMaxSpeed = 255;

uint8_t currentSpeed = kMotorStopSpeed;

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
    pinMode(kDirectionSwitchCommonPin, INPUT_PULLUP);
    pinMode(kDirectionSwitchLeftPin, INPUT_PULLUP);
    pinMode(kDirectionSwitchRightPin, INPUT_PULLUP);

    webControlSerial.begin(9600);
    Serial.begin(9600);

    stopMotors();
}

void loop()
{
    bool obstacleDetected = !digitalRead(kProximitySensorPin);

    if (obstacleDetected)
    {
        digitalWrite(kLedPin, HIGH);
        stopMotors();
    }
    else
    {
        digitalWrite(kLedPin, LOW);

        bool leftSwitchState = !digitalRead(kDirectionSwitchLeftPin);
        bool rightSwitchState = !digitalRead(kDirectionSwitchRightPin);

        if (leftSwitchState && !rightSwitchState)
        {
            moveLeft(currentSpeed);
        }
        else if (!leftSwitchState && rightSwitchState)
        {
            moveRight(currentSpeed);
        }
        else
        {
            stopMotors();
        }

        if (webControlSerial.available() > 0)
        {
            char command = webControlSerial.read();
            Serial.println(command);

            if (command == 'L')
            {
                moveLeft(currentSpeed);
            }
            else if (command == 'R')
            {
                moveRight(currentSpeed);
            }
            else if (command == 'S')
            {
                stopMotors();
            }
            else if (command >= '0' && command <= '9')
            {
                uint8_t speed = map(command - '0', 0, 9, 0, 255);
                setSpeed(speed);
            }
        }
    }

    delay(100);
}

void moveLeft(uint8_t speed)
{
    analogWrite(kLeftMotorEnablePin, speed);
    digitalWrite(kLeftMotorForwardPin, LOW);
    digitalWrite(kLeftMotorBackwardPin, HIGH);
    digitalWrite(kRightMotorForwardPin, LOW);
    digitalWrite(kRightMotorBackwardPin, HIGH);
}

void moveRight(uint8_t speed)
{
    analogWrite(kRightMotorEnablePin, speed);
    digitalWrite(kLeftMotorForwardPin, HIGH);
    digitalWrite(kLeftMotorBackwardPin, LOW);
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
    analogWrite(kLeftMotorEnablePin, speed);
    analogWrite(kRightMotorEnablePin, speed);
}
