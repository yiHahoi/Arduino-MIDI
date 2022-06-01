#include <MIDI.h>  // Add Midi Library
#include <Wire.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13    // Arduino Board LED is on Pin 13
int pot_last_1 = 0;
int pot_new_1 = 0;

void setup()
{
  Wire.begin(8);
  Wire.onReceive(receiveEvent); // register event

  Serial.begin(115200);
  
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output

}

void loop()
{
  pot_new_1 = analogRead(0)>>3;
  if(pot_new_1 != pot_last_1)
  {
    pot_last_1 = pot_new_1;
    Serial.write(0xb0);
    Serial.write(0x01);
    Serial.write(pot_new_1);
  }

  
  delay(10);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(Wire.available()) // mientras se reciban bytes
  {
    byte b = Wire.read(); // receive byte
    Serial.write(b);         // byte a USB Serial
  }
}
