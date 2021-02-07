/*
 Name:		BlueToothino_A.ino
 Created:	1/19/2021 11:23:09 PM
 Author:	lamri
*/
#include <SoftwareSerial.h>
const int buttonPinA = 4;
const int buttonPinB = 6;

const int ledPinA = 5; //yellow
const int ledPinB = 7; //green
const int ledPinC = 2; //red
int readingA;
int readingB;

int ledStateA = HIGH;
int ledStateB = HIGH;
int ledStateC = LOW;
int buttonStateA;
int buttonStateB;
int lastButtonStateA = LOW;
int lastButtonStateB = LOW;
 
  
int ldr = A0;
SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {
    Serial.begin(19200);
    mySerial.begin(9600);
    pinMode(buttonPinA, INPUT);
    pinMode(buttonPinB, INPUT);
    pinMode(ledPinA, OUTPUT);
    pinMode(ledPinB, OUTPUT);
    pinMode(ledPinC, OUTPUT);
    pinMode(ldr, INPUT);

   // set initial LED state
    digitalWrite(ledPinA, ledStateA);
    digitalWrite(ledPinB, ledStateB);

    readingA = digitalRead(buttonPinA);
    readingB = digitalRead(buttonPinB);
    }



void loop() {
    ButtonALedA();
    ButtonBLedB();
  
    }

void bleloop() { // run over and over
    if (mySerial.available() > 0) {
        String data = mySerial.readStringUntil('\n');
        Serial.println(data);

        if (data.equals("toggle")) {
            ledStateC = !ledStateC;
            digitalWrite(ledPinC, ledStateC);
            }
        }

    int ldr_val = analogRead(ldr);
    ldr_val = map(ldr_val, 0, 1023, 0, 255);

    mySerial.println(ldr_val);
    delay(10);
    }


