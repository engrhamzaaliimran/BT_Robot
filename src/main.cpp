#include <Arduino.h>

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int received;      // received value will be stored in this variable
char receivedChar; // received value will be stored as CHAR in this variable

const char moveForward = 'a';
const char moveBackward = 'b';
const char moveRight = 'c';
const char moveLeft = 'd';

const int HBridge1_pos = 5;
const int HBridge1_neg = 18;
const int HBridge2_pos = 19;
const int HBridge2_neg = 21;

void stop()
{
  Serial.println("Stop");
  digitalWrite(HBridge1_pos, LOW);
  digitalWrite(HBridge1_neg, LOW);
  digitalWrite(HBridge2_pos, LOW);
  digitalWrite(HBridge2_neg, LOW);
}

void forward()
{
  Serial.println("forward");
  digitalWrite(HBridge1_pos, HIGH);
  digitalWrite(HBridge1_neg, LOW);
  digitalWrite(HBridge2_pos, HIGH);
  digitalWrite(HBridge2_neg, LOW);
  delay(100);
}

void backward()
{
  Serial.println("backward");
  digitalWrite(HBridge1_pos, LOW);
  digitalWrite(HBridge1_neg, HIGH);
  digitalWrite(HBridge2_pos, LOW);
  digitalWrite(HBridge2_neg, HIGH);
  delay(100);
}

void right()
{
  Serial.println("right");
  digitalWrite(HBridge1_pos, HIGH);
  digitalWrite(HBridge1_neg, LOW);
  digitalWrite(HBridge2_pos, LOW);
  digitalWrite(HBridge2_neg, HIGH);
  delay(100);
}

void left()
{
  Serial.println("right");
  digitalWrite(HBridge1_pos, LOW);
  digitalWrite(HBridge1_neg, HIGH);
  digitalWrite(HBridge2_pos, LOW);
  digitalWrite(HBridge2_neg, HIGH);
  delay(100);
}

void setup()
{
  Serial.begin(9600);
  SerialBT.begin("ESP32_Robot"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(HBridge1_pos, OUTPUT);
  pinMode(HBridge1_neg, OUTPUT);
  pinMode(HBridge2_pos, OUTPUT);
  pinMode(HBridge2_neg, OUTPUT);
  stop();
}

void loop()
{
  receivedChar = (char)SerialBT.read();

  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {

    SerialBT.print("Received:");    // write on BT app
    SerialBT.println(receivedChar); // write on BT app
    Serial.print("Received:");      // print on serial monitor
    Serial.println(receivedChar);   // print on serial monitor

    if (receivedChar == moveForward)
    {
      forward();
    }

    if (receivedChar == moveBackward)
    {
      backward();
    }

    if (receivedChar == moveRight)
    {
      right();
    }

    if (receivedChar == moveLeft)
    {
      left();
    }
  }
}