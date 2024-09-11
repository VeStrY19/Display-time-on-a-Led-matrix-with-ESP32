#include <arduino-timer.h>


Timer timer; 

long number = 0; 
int num1 = 0;
int num2 = 0;
int num3 = 0;
int num4 = 0;
int timer_event = 0;

int D1 = 22;
int D2 = 21;
int D3 = 19;
int D4 = 4;

int latchPin = 5;
int clockPin = 18;
int dataPin = 23;

int count = 0;
int numbers[4] ;
int cathodePins[] = {22, 21, 19, 4};

byte table[10] {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};

void setup() {
  Serial.begin(115200); 
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(D4, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D1, HIGH);
  Serial.println("Enter a number between 0 and 9999");
}

void loop() {
  timer.update(); 
  if (Serial.available()) { 
    timer.stop(timer_event); 
    screenOff(); 
    String s = Serial.readString(); 
    number = (long)s.toInt(); 
    if (number > 9999) { 
      Serial.println("Enter a number between 0 and 9999");
      } else {
      separate(number);
      timer_event = timer.every(1, Display); 
    }
  }
}

void separate(long num) { 
  num1 = num / 1000;
  numbers[0] = num1;
  int num1_remove = num - (num1 * 1000);
  num2 = num1_remove / 100;
  numbers[1] = num2;
  int num2_remove = num1_remove - (num2 * 100);
  num3 = num2_remove / 10;
  numbers[2] = num3;
  num4 = num2_remove - (num3 * 10);
  numbers[3] = num4;
}

void Display() {
  screenOff(); 
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin,LSBFIRST, table[numbers[count]]); 
  digitalWrite(cathodePins[count], LOW); 
  digitalWrite(latchPin, HIGH); 
  count++; 
  if (count == 4) { 
    count = 0;
  }
}

void screenOff() { 
  digitalWrite(D4, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D1, HIGH);
}
