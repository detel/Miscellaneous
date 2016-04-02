#include<math.h>

String str = "";
String password = "1234";
int count = 0, prevcmd = -1;

void setup() {
  
    for(int i=2;i<6;i++)
      pinMode(i,INPUT);
    pinMode(6,OUTPUT);
    Serial.begin(9600);
    
}

void loop() {
  
  first:
  int b1 = analogRead(A0) >= 150 ? 1 : 0;
  int b2 = analogRead(A1) >= 150 ? 1 : 0;
  int b3 = analogRead(A2) >= 150 ? 1 : 0;
  int b4 = analogRead(A3) >= 150 ? 1 : 0;
  
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
  //Serial.println(str);
  
  if(str.length() > 4) {
    int i = str.length() - 4;
    if(str.substring(i,i+4) == password){
      Serial.println("Correct Password");
      digitalWrite(6, HIGH);
    } else {
      Serial.println(str.substring(i, i+4) + " is wrong password!!!");
      digitalWrite(6, LOW);
      count++;
    }
  }
  if(str.length() >= 100)
    str = "";
    
  if(count >= 5) {
    if(count == 5){
      Serial.println("You've entered wrong password 5 times!!!");
      Serial.println("Try after 30 seconds.....");
    }
    count++;
    if(count == 35)
      count = 0;
  }
  delay(250);
  
}
