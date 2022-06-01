#include <MIDI.h>  // Add Midi Library
#include <SoftwareSerial.h>

SoftwareSerial swSerial(2, 11); // RX, TX

MIDI_CREATE_INSTANCE(SoftwareSerial, swSerial, midiSw1);

#define LED 13    // Arduino Board LED is on Pin 13

void setup()
{
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output

  midiSw1.begin(MIDI_CHANNEL_OMNI);
  midiSw1.setHandleNoteOn(MyHandleNoteOn);
  midiSw1.setHandleNoteOff(MyHandleNoteOff);

  Serial.begin(115200);
}

void loop()
{
  midiSw1.read();
}

void MyHandleNoteOn(byte channel, byte pitch, byte velocity)
{
  digitalWrite(LED, HIGH); //Turn LED on
  //0x903C60
  //Serial.println(0b10010000);
  //Serial.println(0b00111100);
  //Serial.println(0b01100000);
  //Serial.write(0x90);
  //Serial.write(0x3C);
  //Serial.write(0x60);
  Serial.write(0x90);
  Serial.write(pitch);
  Serial.write(velocity);
}

void MyHandleNoteOff(byte channel, byte pitch, byte velocity)
{
  digitalWrite(LED, LOW); //Turn LED off
  //0x803C60
  //Serial.println(0b10000000);
  //Serial.println(0b00111100);
  //Serial.println(0b01100000);
  Serial.write(0x80);
  Serial.write(pitch);
  Serial.write(velocity);
}
