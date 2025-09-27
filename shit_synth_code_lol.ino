/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.

    Demonstrates the use of Oscil to play a wavetable.

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.io/Mozzi/

    Mozzi documentation/API
    https://sensorium.github.io/Mozzi/doc/html/index.html

    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Copyright 2012-2024 Tim Barrass and the Mozzi Team

    Mozzi is licensed under the GNU Lesser General Public Licence (LGPL) Version 2.1 or later.
*/

#define MOZZI_CONTROL_RATE 64    // Hz, powers of 2 are most reliable; 64 Hz is actually the default, but shown here, for clarity

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <Line.h> // for envelope
#include <mozzi_midi.h>
#include <ADSR.h>
#include <mozzi_fixmath.h>
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/saw2048_int8.h> // saw table for oscillator
#include <tables/triangle2048_int8.h> // triangle table for oscillator
#include <tables/smoothsquare8192_int8.h> // square table for oscillator


#define CONTROL_RATE 128 // powers of 2 please

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin1(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin2(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin3(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin4(SIN2048_DATA);
int freq = 0;

int numset;
int i;
int j;
int O = 0;
int Cref = 261;
int inputs[25];

int note1 = 0;
int note2 = 0;
int note3 = 0;
int note4 = 0;
int column = 2;

int notes[25] = {142,166,190,214,237,261,285,309,333,356,380,404,428,457,475,499,523,547,570,595,618,642,665,683,702}; 





void setup(){
  startMozzi(); // :)

  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  Serial.begin(9600);

  
}


void updateControl(){
  // put changing controls in here
  
  digitalWrite(7,0);          
    inputs[0] = !digitalRead(2);
    inputs[5] = !digitalRead(3);
    inputs[10] = !digitalRead(4);
    inputs[15] = !digitalRead(5);
    inputs[20] = !digitalRead(6);
    digitalWrite(7,1);  

    digitalWrite(8,0);          
    inputs[1] = !digitalRead(2);
    inputs[6] = !digitalRead(3);
    inputs[11] = !digitalRead(4);
    inputs[16] = !digitalRead(5);
    inputs[21] = !digitalRead(6);
    digitalWrite(8,1);     

    digitalWrite(10,0);          
    inputs[2] = !digitalRead(2);
    inputs[7] = !digitalRead(3);
    inputs[12] = !digitalRead(4);
    inputs[17] = !digitalRead(5);
    inputs[22] = !digitalRead(6);
    digitalWrite(10,1);      

    digitalWrite(11,0);          
    inputs[3] = !digitalRead(2);
    inputs[8] = !digitalRead(3);
    inputs[13] = !digitalRead(4);
    inputs[18] = !digitalRead(5);
    inputs[23] = !digitalRead(6);
    digitalWrite(11,1);      

    digitalWrite(12,0);          
    inputs[4] = !digitalRead(2);
    inputs[9] = !digitalRead(3);
    inputs[14] = !digitalRead(4);
    inputs[19] = !digitalRead(5);
    inputs[24] = !digitalRead(6);
    digitalWrite(12,1);     

  numset = 1;
  note1 = 0;
  note2 = 0;
  note3 = 0;
  note4 = 0;

  for (j = 0;j<24;j++){
   freq = Cref * 2^((j/12)+O);
   if (inputs[j]==1){
    switch (numset) {
      case 1:
        note1 = notes[25-j];      
        numset++;
      case 2:
        note2 = notes[25-j]; 
        numset++;
      case 3:
        note3 = notes[25-j]; 
        numset++;
      case 4:
        note4 = notes[25-j]; 
        numset++;
      case 5:
        break;
      
    }
    
   }
  }
  



  // jacks audio code
  aSin1.setFreq(note1);
  aSin2.setFreq(note2);
  aSin3.setFreq(note3);
  aSin4.setFreq(note4);
}


int updateAudio(){
  return (int) (aSin1.next() + aSin2.next() + aSin3.next()  + aSin4.next()) >> 2;
   
  
}


void loop(){
  audioHook(); // required here
  
}
