/*
 Name:		BlueToothino_A.ino
 Created:	1/19/2021 11:23:09 PM
 Author:	lamri
*/

 
const int buttonPinA = 4;    
const int buttonPinB = 6;     
const int ledPinA = 5; 
const int ledPinB = 7;   
 
int ledStateA = HIGH; 
int ledStateB = HIGH;
int buttonStateA; 
int buttonStateB;      
int lastButtonStateA = LOW;  
int lastButtonStateB = LOW;   
int readingA;
int readingB;

unsigned long lastDebounceTimeA = 0;  // the last time the output pin was toggled
unsigned long debounceDelayA = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTimeB = 0;   
unsigned long debounceDelayB = 50;    

void setup() {
    pinMode(buttonPinA, INPUT);
    pinMode(buttonPinB, INPUT);
    pinMode(ledPinA, OUTPUT);
    pinMode(ledPinB, OUTPUT);

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

void ButtonALedA() { 
    readingA = digitalRead(buttonPinA);
     // If the switch changed, due to noise or pressing:
    if (readingA != lastButtonStateA) {
        lastDebounceTimeA = millis(); // reset the debouncing timer
        }
    if ((millis() - lastDebounceTimeA) > debounceDelayA) {
  // whatever the reading is at, it's been there for longer than the debounce
  // delay, so take it as the actual current state:

  // if the button state has changed:
        if (readingA != buttonStateA) {
            buttonStateA = readingA;

            // only toggle the LED if the new button state is HIGH
            if (buttonStateA == HIGH) {
                ledStateA = !ledStateA;
                }
            }
        }
    digitalWrite(ledPinA, ledStateA);
        // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonStateA = readingA;
    }
void ButtonBLedB() { 
    readingB = digitalRead(buttonPinB);
    if (readingB != lastButtonStateB) {
        lastDebounceTimeB = millis();
        }
    if ((millis() - lastDebounceTimeB) > debounceDelayB) {
        if (readingB != buttonStateB) {
            buttonStateB = readingB;
            if (buttonStateB == HIGH) {
                ledStateB = !ledStateB;
                }
            }
        }
    digitalWrite(ledPinB, ledStateB);
    lastButtonStateB = readingB;
    }
