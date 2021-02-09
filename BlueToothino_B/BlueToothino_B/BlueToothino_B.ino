/*
 Name:		BlueToothino_B.ino
 Created:	1/19/2021 11:28:51 PM
 Author:	lamri
*/

//  SerialIn_SerialOut_HM-10_01
//
//  Uses hardware serial to talk to the host computer and AltSoftSerial for communication with the bluetooth module
//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//  Does not send line endings to the HM-10
//
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  Arduino D8 (SS RX) - BT TX no need voltage divider 
//  Arduino D9 (SS TX) - BT RX through a voltage divider (5v to 3.3v)
//
//#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
const int buttonPinA = 3;
const int buttonPinB = 5;

const int ledPinA = 2; //yellow
const int ledPinB = 4; //green
const int ledPinC = 13; //red
int readingA;
int readingB;

int ledStateA = HIGH;
int ledStateB = HIGH;
int ledStateC = LOW;
int buttonStateA;
int buttonStateB;
int lastButtonStateA = LOW;
int lastButtonStateB = LOW;


int potPin_lr = A0;
int potPin_ud = A1;
//SoftwareSerial mySerial(0, 1); // RX, TX
AltSoftSerial mySerial;
char c = ' ';
boolean NL = true;

void setup() {
    setupALtSoftSerial();
    pinMode(buttonPinA, INPUT);
    pinMode(buttonPinB, INPUT);
    pinMode(ledPinA, OUTPUT);
    pinMode(ledPinB, OUTPUT);
    pinMode(ledPinC, OUTPUT);
    pinMode(potPin_lr, INPUT);
    pinMode(potPin_ud, INPUT);

   // set initial LED state
    digitalWrite(ledPinA, ledStateA);
    digitalWrite(ledPinB, ledStateB);

    readingA = digitalRead(buttonPinA);
    readingB = digitalRead(buttonPinB);
    }

void setupRgularSerial() {
    Serial.begin(19200);
    mySerial.begin(9600);
    }
void setupALtSoftSerial()
    {
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");

    mySerial.begin(9600);
    Serial.println("BTserial started at 9600");
    }

void loop() {
    ButtonALedA();
    ButtonBLedB();
    loopAltSoft();
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

    int ldr_val = analogRead(potPin_ud);
    ldr_val = map(ldr_val, 0, 1023, 0, 255);

    mySerial.println(ldr_val);
    delay(10);
    }

void loopAltSoft()
    {
     // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (mySerial.available())
        {
        c = mySerial.read();
        Serial.write(c);
        }


        // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
        {
        c = Serial.read();

        // do not send line end characters to the HM-10
        if (c != 10 & c != 13)
            {
            mySerial.write(c);
            }

            // Echo the user input to the main window. 
            // If there is a new line print the ">" character.
        if (NL) { Serial.print("\r\n>");  NL = false; }
        Serial.write(c);
        if (c == 10) { NL = true; }
        }
    }