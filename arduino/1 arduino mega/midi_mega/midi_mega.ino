#include <MIDI.h>  // Add Midi Library

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

int LED = 13;
int pot_last_1 = 0;
int pot_new_1 = 0;
unsigned long step_time = 1000;
unsigned long prev_time = 0;
unsigned long new_time = 0;

void setup()
{
  
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  
  Serial.begin(115200); // para enviar señal midi por puerto usb
  Serial1.begin(31250); // para lectura de señal midi del teclado
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(MyHandleNoteOn);
  MIDI.setHandleNoteOff(MyHandleNoteOff);
  MIDI.setHandlePitchBend(MyHandlePitchBend);
  MIDI.setHandleAfterTouchChannel(MyHandleAfterTouchChannel);

}

void loop()
{
  MIDI.read();

  new_time = millis();
  if(new_time - prev_time >= step_time){
    prev_time = new_time;
    pot_new_1 = analogRead(0) >> 3;
    if(pot_new_1 != pot_last_1)
    {
      pot_last_1 = pot_new_1;
      Serial.write(0xb0);
      Serial.write(0x01);
      Serial.write(pot_new_1);
    }
  }

}

void MyHandleNoteOn(byte channel, byte pitch, byte velocity)
{
  digitalWrite(LED, HIGH); //Turn LED on
  Serial.write(0x90); // se envia byte de comando "note on" en canal 0
  Serial.write(pitch); // se envia byte de pitch
  Serial.write(velocity); // se envia byte de velocity
}

void MyHandleNoteOff(byte channel, byte pitch, byte velocity)
{
  digitalWrite(LED, LOW); //Turn LED off
  Serial.write(0x80); // se envia byte de comando "note on" en canal 0
  Serial.write(pitch); // se envia byte de pitch
  Serial.write(velocity); // se envia byte de velocity
}

void MyHandlePitchBend(byte channel, int bend)
{
  digitalWrite(LED, HIGH); //Turn LED on
  // bend es un int de 16bits con un valor de 14bits
  unsigned int val = (bend  + 8192) << 1;
  byte lsb = lowByte(val); // 8 lsb de val (16bits)
  byte msb = highByte(val); // 8 msb de val (16bits)
  lsb = lsb >> 1;

  Serial.write(0xE0); // se envia byte de comando "PitchBend" en canal 0
  Serial.write(lsb); // se envia byte de lsb
  Serial.write(msb); // se envia byte de msb
  digitalWrite(LED, LOW); //Turn LED off
}

void MyHandleAfterTouchChannel(byte channel, byte pressure)
{
  digitalWrite(LED, HIGH); //Turn LED on
  Serial.write(0xD0); // se envia byte de comando "AfterTouchChannel" en canal 0
  Serial.write(pressure); // se envia byte de pressure
  digitalWrite(LED, LOW); //Turn LED off
}
