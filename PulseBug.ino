/*******************************************************************
  PulseBug
  http://xenbio.net/mdwiki/#!pulse_bug.md

  The Artistic License 2.0
  Copyright (c) 2014 SeungBum Kim <picxenk@gmail.com>
  license details at : http://choosealicense.com/licenses/artistic/
*******************************************************************/

const int buttonPin = 0;
const int ledPin = 1;
int fade = 20;

int brightness = 0;
int beat = 60;
int buttonPulseStep = 0;
int pulseThreshold = 1700;

long pTime = 0;
long cTime = 0;
long newPulseTime = 0;
long oldPulseTime = 0;

boolean readyToClick = false;
boolean buttonClicked = false;


void setup() {
  pinMode(buttonPin, INPUT); 
  digitalWrite(buttonPin, HIGH); //internal pull-up
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  cTime = millis();
  
  if (digitalRead(buttonPin) == LOW) readyToClick = true;
  if (readyToClick && (digitalRead(buttonPin) == HIGH)) {
    readyToClick = false;
    buttonClicked = true;
  }
  
  if (buttonClicked) {
    oldPulseTime = newPulseTime;
    newPulseTime = cTime;
    
    buttonPulseStep = newPulseTime - oldPulseTime;
    
    if (buttonPulseStep < pulseThreshold) {
      beat = int(60000 / buttonPulseStep);
    }
    buttonClicked = false;
  }
  
  beatPulse(beat);

}

void beatPulse(int beat) {  
  if (brightness == 0) {
    fade = 20;
  }
  if (brightness == 240) {
    fade = -5;
  }

  if (cTime - pTime > int(1000/beat)) {
    pTime = cTime;
    analogWrite(ledPin, brightness);
    brightness = brightness + fade;
  }
}

