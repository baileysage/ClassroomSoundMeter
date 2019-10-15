#include <Arduino.h>
#include "SoundIO.h"

/*
Heavily borrowed from Elegoo Super Starter Kit code
*/

// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7
//                Mapping to      a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[10] = {
    B11111100, // = 0
    B01100000, // = 1
    B11011010, // = 2
    B11110010, // = 3
    B01100110, // = 4
    B10110110, // = 5
    B10111110, // = 6
    B11100000, // = 7
    B11111110, // = 8
    B11100110  // = 9
};

#define DATA_PIN_YELLOW   2 // data for Yellow counter
#define LATCH_PIN_YELLOW  3 // write enable for Yellow counter
#define CLOCK_PIN         4 // clock pins for counters (shared)
#define DATA_PIN_RED      5 // data for Red counter
#define LATCH_PIN_RED     6 // write enable for Red counter
#define RESET_YELLOW_PIN  8 
#define RESET_RED_PIN     9

SoundIO soundController;

void setup()
{
  // Set latchPin, clockPin, dataPin as output
  pinMode(DATA_PIN_YELLOW, OUTPUT);
  pinMode(LATCH_PIN_YELLOW, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN_RED, OUTPUT);
  pinMode(LATCH_PIN_RED, OUTPUT);

  pinMode(RESET_YELLOW_PIN,  INPUT_PULLUP);
  pinMode(RESET_RED_PIN, INPUT_PULLUP);

  soundController = SoundIO();
}

// display a number on the digital segment display
void sevenSegWrite(byte digit, int dataPin, int latchPin)
{
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);

  // the original data (bit pattern)
  shiftOut(dataPin, CLOCK_PIN, LSBFIRST, seven_seg_digits[digit]);

  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}

void loop()
{
  // count from 9 to 0
  for (byte digit = 10; digit > 0; --digit)
  {
    delay(500);
    sevenSegWrite(digit - 1, DATA_PIN_YELLOW, LATCH_PIN_YELLOW);
    delay(500);
    sevenSegWrite(digit - 1, DATA_PIN_RED, LATCH_PIN_RED);
    if (digit == 0)
      soundController.playWarning();
  }

  // suspend 4 seconds
  delay(3000);
}
