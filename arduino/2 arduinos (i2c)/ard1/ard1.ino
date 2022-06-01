#include <MIDI.h>  // Add Midi Library
#include <Wire.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13    // Arduino Board LED is on Pin 13

void setup()
{

  Wire.begin(); // join i2c bus (address optional for master)
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
  MIDI.setHandlePitchBend(MyHandlePitchBend);
  MIDI.setHandleAfterTouchChannel(MyHandleAfterTouchChannel);

  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  
}

void loop()
{
  MIDI.read();
}

void MyHandleNoteOn(byte channel, byte pitch, byte velocity)
{
  digitalWrite(LED, HIGH); //Turn LED on
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(0x90); // se envia byte de comando "note on" en canal 0
  Wire.write(pitch); // se envia byte de pitch
  Wire.write(velocity); // se envia byte de velocity
  Wire.endTransmission();    // stop transmitting
}

void MyHandleNoteOff(byte channel, byte pitch, byte velocity)
{
  digitalWrite(LED, LOW); //Turn LED off
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(0x80); // se envia byte de comando "note on" en canal 0
  Wire.write(pitch); // se envia byte de pitch
  Wire.write(velocity); // se envia byte de velocity
  Wire.endTransmission();    // stop transmitting
}

void MyHandlePitchBend(byte channel, int bend)
{
  digitalWrite(LED, HIGH); //Turn LED on
  // bend es un int de 16bits con un valor de 14bits
  unsigned int val = (bend  + 8192) << 1;
  byte lsb = lowByte(val); // 8 lsb de val (16bits)
  byte msb = highByte(val); // 8 msb de val (16bits)
  lsb = lsb >> 1;
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(0xE0); // se envia byte de comando "PitchBend" en canal 0
  Wire.write(lsb); // se envia byte de lsb
  Wire.write(msb); // se envia byte de msb
  Wire.endTransmission();    // stop transmitting
  digitalWrite(LED, LOW); //Turn LED off
}

void MyHandleAfterTouchChannel(byte channel, byte pressure)
{
  digitalWrite(LED, HIGH); //Turn LED on
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(0xD0); // se envia byte de comando "AfterTouchChannel" en canal 0
  Wire.write(pressure); // se envia byte de pressure
  Wire.endTransmission();    // stop transmitting
  digitalWrite(LED, LOW); //Turn LED off
}


//void pitchbend (byte channel, int bend) { // the pitchbend is done in the arduino Midi library. "Bend" is a int value between -8192 .. 8192. "0" is the middle --> no change in pitch
//  bend_float = (float) bend;                    //Convert bend (int) to float type to get also the after zero numbers
//  float bendfactor = (1+ bend_float/8190);      // Calculate the bend factor, with wich the tone() in [hz] shall be bended. Bendfactor shall be between 0.1 and 2, if no bending is applied --> 1.
//  if ((freq*bendfactor) > 50)                 // To prevent the output from beeing in an unstable state when note is not properly ended (e.g. not "OFF" has been send
//      tone(tonePin,freq*bendfactor);              // Write pitchbended tone to the output. E.g. bend: 8192: 440Hz * 2  --> 880hz --> one Octave higher
//}
