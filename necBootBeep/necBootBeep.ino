/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:

void setup() {
  // iterate over the notes of the melody:
  tone(8, 2000);
  delay(100);
  tone(8, 1000);
  delay(100);
  // stop the tone playing:
  noTone(8);  
}

void loop() {
  // no need to repeat the melody.
}
