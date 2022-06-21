// Initialize pin for Button
#define buttonPin 6

// Initialize pin for Buzzer
#define buzzerPin 2

// Initialize pin for each LED
#define ledOne 3
#define ledTwo 4
#define ledThree 5
#define workingLed 7

// Counter
int timerValue = 10;

// HIGH and LOW
int H = HIGH;
int L = LOW;

// State for button
bool buttonState = false;
bool stopTimer = true;

void setup()
{
  // Baud speed for 9600
  Serial.begin(9600);
  
  // Button pin for input
  pinMode(buttonPin, INPUT);
    
  // Buzzer pin for output
  pinMode(buzzerPin, OUTPUT);
  
  // Each LED pin for output
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(workingLed, OUTPUT);
  
  timerActive();
}

// For timer active running LED effect
void timerActive() {
  digitalWrite(ledOne, H);
  delay(150);
  digitalWrite(ledTwo, H);
  delay(150);
  digitalWrite(ledThree, H);
  delay(150);
  digitalWrite(ledOne, L);
  delay(150);
  digitalWrite(ledTwo, L);
  delay(150);
  digitalWrite(ledThree, L);
  delay(150);
}

// For timer is up
void timerIsUp() {
  delay(500);
  digitalWrite(ledOne, L);
  digitalWrite(ledTwo, L);
  digitalWrite(ledThree, L);
  delay(500);

  for (int i = 0; i < 5; i++) {
    tone(buzzerPin, 900, 500);

    digitalWrite(ledOne, H);
    digitalWrite(ledTwo, H);
    digitalWrite(ledThree, H);

    delay(500);

    digitalWrite(ledOne, L);
    digitalWrite(ledTwo, L);
    digitalWrite(ledThree, L);

    delay(500);
  }

  // Reset timer to initial state
  timerValue = 10;

  // Reset button state
  buttonState = false;
  
  // Stop the timer
  stopTimer = true;
}

// For button while pressed
void buttonPress() {
  // Read the state of Button
  buttonState = digitalRead(buttonPin);

  if (buttonState == true) {
    Serial.println("Button pressed.\nTimer Active!");
    stopTimer = false;
    timerActive();
    timerActive();
    timerActive();
  }
}

// LED progress ready for time up
void getReady() {
	// If close to time up each LED turned on one by one
  if (timerValue == 7) {
  	digitalWrite(ledOne, H);
  } else if (timerValue == 4) {
    digitalWrite(ledTwo, H);
  } else if (timerValue == 1) {
    digitalWrite(ledThree, H);
  }
}

void workingTime() {
// One second delay with blinking LED
  delay(100);
  digitalWrite(workingLed, H);
  delay(100);
  digitalWrite(workingLed, L);
  delay(800);
}

void monitorStatus() {
  Serial.print("Now is: ");
  Serial.println(timerValue);
}

void loop()
{ 
  // Timer for Push Button
  while (buttonState == false && stopTimer == true) {    
    buttonPress();
    delay(2);
  }
  
  getReady();
  
  timerValue--;
  
  // Monitoring
  monitorStatus();
  
  // If time is up turn tone the Buzzer and LED
  if (timerValue == 0) {
    timerIsUp();
  }
  
  // Max delay 1 second with blinking LED
  workingTime();
}
