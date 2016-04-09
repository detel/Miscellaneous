#include <math.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

LiquidCrystal lcd(8,9,10,11,12,13);

static int current_state = 0,p=0; 
String str = "";
String password = "1234";
int i = -1, count = 0, prevcmd = -1;
boolean first = true, open = false;
const int stepsPerRevolution = 200;

Stepper myStepper(stepsPerRevolution, 3, 4, 6, 7);      // IC - Arduino 2-7, 7-6, 10-4, 15-3

void setup() {
  
    pinMode(A2,INPUT);
    pinMode(A3,INPUT);
    pinMode(A4,INPUT);
    pinMode(A5,INPUT);
    lcd.begin(16, 2);
    lcd.print("hello, world!");
    myStepper.setSpeed(60);
    Serial.begin(9600);
}

void loop() {
  first:
  int b1 = analogRead(A2) >= 150 ? 1 : 0;
  int b2 = analogRead(A3) >= 150 ? 1 : 0;
  int b3 = analogRead(A4) >= 150 ? 1 : 0;
  int b4 = analogRead(A5) >= 150 ? 1 : 0;
  int command = b1*8 + b2*4 + b3*2 + b4;
  
  if(command == 10)
    command = 0;  
  Serial.println(command);
  if(command == prevcmd) {  
    delay(1000);
    goto first;
  }
  prevcmd = command;
  str += String(command);
  Serial.println(str);
  if((str.length() == 5 && first) || (str.length() == 4 && !first)) {
    int i = first? 1: 0;
    first = false;
    lcd.clear();
    if(str.substring(i,i+4) == password){
      Serial.println("Correct Password");
      lcd.print("Correct Password");
      myStepper.step(stepsPerRevolution);
      delay(500);
      open = true;
      digitalWrite(2, HIGH);
    } else {
      Serial.println(str.substring(i, i+4) + " is wrong password!!!");
      lcd.print(str.substring(i, i+4) + "wrong pass");
      digitalWrite(2, LOW);
      if(open) {
        myStepper.step(-stepsPerRevolution);
        delay(500);
      }
      open = false;
      count++;
    }
    str = "";
  }
  if(str.length() >= 100)
    str = "";
  if(count >= 5) {
      wait();
      count = 0;
  }
  
  delay(1000);
}

void wait() {
    Serial.println("You've entered wrong password 5 times!!!");
    Serial.println("Try after 30 seconds.....");
    lcd.print("Entered wrong pswd 5 times");
    
    int secondsLeft = 30;
    while(secondsLeft > 0) {
      lcd.clear();
      lcd.print("Try after ");
      lcd.print(secondsLeft);
      lcd.print(" seconds");
      delay(1000);
      secondsLeft--;  
    }
    lcd.clear();
    lcd.print("Enter password now");
    first = true;
}
