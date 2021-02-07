



unsigned long lastDebounceTimeA = 0;  // the last time the output pin was toggled
unsigned long debounceDelayA = 50;    // the debounce time; increase if the output flickers
unsigned long lastDebounceTimeB = 0;
unsigned long debounceDelayB = 50;

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

void TestLedAandB_on_red_on() {
    if (ledStateA == HIGH && ledStateB == HIGH) {
        digitalWrite(ledPinC, HIGH);
        }
    else
        digitalWrite(ledPinC, LOW);
    }
