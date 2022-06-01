Arduino MIDI Interface 
Keyboard to PC

3 options:

1)  1 arduino mega using 2 uarts (keyboard --midi--> arduino --usb--> pc)
2)  2 arduinos connected by i2c using 1 uart each (keyboard --midi--> arduino1 --i2c--> arduino2 --usb--> pc)
3)  1 arduino connected with softserial to keyboard (slow and error prone),and uart for usb (keyboard --midi--> arduino --usb--> pc)



