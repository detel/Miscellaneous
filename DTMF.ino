#include <math.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

LiquidCrystal lcd(8,9,10,11,12,13);

static int current_state = 0,p=0; 
String str = "";
String password = "1234";
int i = -1, count = 0, prevcmd = -1;
boolean first = true, open = false, done = false, reset = false;
boolean alreadyOpen = false, alreadyClose = false;
const int stepsPerRevolution = 20;

Stepper myStepper(stepsPerRevolution, 3, 4, 6, 7);      // IC - Arduino 2-7, 7-6, 10-4, 15-3

void setup() {
  
    pinMode(A2,INPUT);
    pinMode(A3,INPUT);
    pinMode(A4,INPUT);
    pinMode(A5,INPUT);
    pinMode(2 ,OUTPUT);
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
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  
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

  if(reset) {
    Serial.println("inside reset");
    lcd.clear();
    lcd.print("type new");
    lcd.setCursor(0, 1);
    lcd.print("password...");
    if(str.length() == 4) {
      password = str;
      reset = false;
      lcd.clear();
      lcd.print("new password");
      lcd.setCursor(0, 1);
      lcd.print(password);
      delay(2000);
      str = "";
    }
    goto first;
  }
  
  if(done) {
     if(command == 11)
      openDoor();
      else if(command == 12)
        closeDoor();
      else if(command == 0) {
        lcd.clear();
        lcd.print("type new");
        lcd.setCursor(0, 1);
        lcd.print("password...");
        reset = true;
      } else {
        lcd.clear();
        lcd.print("wrong option");
        lcd.setCursor(0, 1);
        lcd.print("selected");
        delay(500);
        lcd.clear();
        lcd.print("type pswd");
        lcd.setCursor(0, 1);
        lcd.print("again");
      }
     done = false;
     str = "";
     goto first;  
  }
  
  if((str.length() == 5 && first) || (str.length() == 4 && !first)) {
    int i = first? 1: 0;
    first = false;
    lcd.clear();
    if(str.substring(i,i+4) == password){
      Serial.println("Correct Password");
      lcd.print("Correct pswd");
      delay(500);
      done = true;
      lcd.clear();
      lcd.print("CHOOSE *:Open");
      lcd.setCursor(0, 1);
      lcd.print("#:Close  0:Reset");
     count = 0;
      //myStepper.step(stepsPerRevolution);
      //delay(500);
      //open = true;
    } else {
      Serial.println(str.substring(i, i+4) + " is wrong password!!!");
      lcd.print(str.substring(i, i+4) + "wrong pass");
      //if(open) {
        //myStepper.step(-stepsPerRevolution);
        //delay(500);
      //}
      //open = false;
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
      if(secondsLeft&1)
        digitalWrite(2 ,HIGH);
      else
        digitalWrite(2 ,LOW);
      lcd.print("Try after ");
      lcd.print(secondsLeft);
      lcd.print(" sec");
      delay(1000);
      secondsLeft--;  
    }
    digitalWrite(2 ,LOW);
    lcd.clear();
    lcd.print("Enter password");
    lcd.setCursor(0, 1);
    lcd.print("now!!");
    lcd.clear();
    first = true;
}

void openDoor() {
  if(alreadyOpen) {
    lcd.clear();
    lcd.print("door is");
    lcd.setCursor(0, 1);
    lcd.print("already opened");
    return;
  }
  myStepper.step(stepsPerRevolution);
  lcd.clear();
  lcd.print("Opening....");
  delay(2000);
  lcd.clear();
  alreadyOpen = true;
  alreadyClose = false;
}

void closeDoor() {
  if(alreadyClose) {
    lcd.clear();
    lcd.print("door is");
    lcd.setCursor(0, 1);
    lcd.print("already closed");
    return;
  }
  myStepper.step(-stepsPerRevolution);
  lcd.clear();
  lcd.print("Closing....");
  delay(2000);
  lcd.clear();
  alreadyClose = true;
  alreadyOpen = false;
}
