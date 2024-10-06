// Little fun LED and latching-momemtary button tests by mortellys on Oct 5, 2024.
// Easily changeable pins for IO
const int btnPin = 2;
const int greenLED1 = 3;
const int redLED1 = 4;
const int redLED2 = 5;

int switchState = 0;
int state = 0, loadState = 0;
int launched = 0;
int initCode = 0;

int incomingByte = 0;

void setup() {
  pinMode(greenLED1, OUTPUT);
  pinMode(redLED1, OUTPUT);
  pinMode(redLED2, OUTPUT);
  pinMode(btnPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  switchState = digitalRead(btnPin);

  // This small bit of code just sort of simulate a machine booting-up.
  // (The full second delay in the FOR loop also helps in avoiding garbage in the serializer.)
  if (initCode == 0) {
    for (int i = 0; i < 5; i++){
      delay(100);
      digitalWrite(greenLED1, HIGH);
      digitalWrite(redLED1, HIGH);
      digitalWrite(redLED2, HIGH);
      delay(100);
      digitalWrite(greenLED1, LOW);
      digitalWrite(redLED1, LOW);
      digitalWrite(redLED2, LOW);
    }
    Serial.println("Initializing...");
    for (int i = 0; i < 3; i++){
      delay(250);
      digitalWrite(redLED1, LOW);
      digitalWrite(redLED2, HIGH);
      delay(250);
      digitalWrite(redLED1, HIGH);
      digitalWrite(redLED2, LOW);
    }
    digitalWrite(redLED1, HIGH);
    initCode = 1;
    Serial.println("Ready");
  }

  // This basically transforms a momentary button into a latching one, mainly thanks to the loadState variable to handle the real code loop further below.
  if ((state == 0 && switchState == HIGH)){ 
    state = 1;
    loadState = !loadState;
    delay(50);
  } else if (state == 1 && switchState == LOW) {
    state = 0;
    delay(50);
  }

  if ((loadState == HIGH && launched == 0)) {      
      digitalWrite(greenLED1, LOW);
      digitalWrite(redLED1, LOW);
      digitalWrite(redLED2, LOW);
      Serial.println("Launch sequence initiated...");

      delay(1000);
      digitalWrite(redLED2, HIGH);
      Serial.println("Booting...");

      delay(1000);
      digitalWrite(redLED1, HIGH);
      Serial.println("Prepping engines...");

      delay(2000);
      digitalWrite(greenLED1, HIGH);

      launched = 1;
      Serial.println("Launched!");

  } else if ((loadState == LOW && launched == 1)) {
    Serial.println("Coming back to ground.");

    for (int i = 0; i <= 25; i++){
      delay(100);
      digitalWrite(greenLED1, LOW);
      delay(100);
      digitalWrite(redLED1, LOW);
      delay(100);
      digitalWrite(redLED2, LOW);
      delay(100);
      digitalWrite(greenLED1, HIGH);
      delay(100);
      digitalWrite(redLED1, HIGH);
      delay(100);
      digitalWrite(redLED2, HIGH);
      delay(100);
    }

    digitalWrite(greenLED1, LOW);
    digitalWrite(redLED1, HIGH);
    digitalWrite(redLED2, LOW);
    Serial.println("Landed back on ground zero. Awaiting next mission.");
    launched = 0;
  }
}
