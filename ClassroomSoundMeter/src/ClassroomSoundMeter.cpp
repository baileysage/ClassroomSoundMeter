#include <Arduino.h>
#include "Microphone.h"

/*
Heavily borrowed from Elegoo Super Starter Kit code
*/


// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7 
//                Mapping to      a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
 
// data for Yellow counter
int dataPinYellow = 2;
// write enable for Yellow counter
int latchPinYellow = 3;
// clock pins for counters (shared)
int clockPin = 4;
// data for Red counter
int dataPinRed = 5;
// write enable for Red counter
int latchPinRed = 6;
 
void setup() {
  // Set latchPin, clockPin, dataPin as output
  pinMode(dataPinYellow, OUTPUT);
  pinMode(latchPinYellow, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPinRed, OUTPUT);
  pinMode(latchPinRed, OUTPUT);
  analogReference(EXTERNAL);
  Microphone microphone();
}
 
// display a number on the digital segment display
void sevenSegWrite(byte digit, int dataPin, int latchPin) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}
 
void loop() {       
  // count from 9 to 0
  for (byte digit = 10; digit > 0; --digit) {
    delay(500);
    sevenSegWrite(digit - 1, dataPinYellow, latchPinYellow); 
    delay(500);
    sevenSegWrite(digit - 1, dataPinRed, latchPinRed); 
  }
   
  // suspend 4 seconds
  delay(3000);
}
