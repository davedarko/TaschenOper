#define MIDI_OUT_CHANNEL 1
#define MIDI_IN_CHANNEL 1

#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// MIDI
Adafruit_USBD_MIDI usbdMidi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usbdMidi, MIDI);


void setup() {
  // put your setup code here, to run once:

  // Initialise MIDI
  MIDI.begin(MIDI_IN_CHANNEL);
  MIDI.setHandleNoteOn(noteOnHandler);
  MIDI.setHandleNoteOff(noteOffHandler);

  // Wait until the device is mounted
  while (!TinyUSBDevice.mounted()) {
    delay(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // processMIDI();

  // note, velocity, midi channel
  MIDI.sendNoteOn(36, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  
  MIDI.sendNoteOff(36, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);

  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);

  MIDI.sendNoteOn(38, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  MIDI.sendNoteOff(38, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);

  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);

  MIDI.sendNoteOn(36, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  MIDI.sendNoteOff(36, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);

  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);

  MIDI.sendNoteOn(38, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  MIDI.sendNoteOff(38, 100, MIDI_OUT_CHANNEL);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);

  MIDI.sendNoteOn(42, 100, MIDI_OUT_CHANNEL);
  delay(100);
  MIDI.sendNoteOff(42, 100, MIDI_OUT_CHANNEL);
  delay(200);
}



void noteOnHandler(byte channel, byte note, byte velocity) {
  if(channel == MIDI_IN_CHANNEL) {
    // externalNoteStates[note] = true;
  }
}

void noteOffHandler(byte channel, byte note, byte velocity) {
  if(channel == MIDI_IN_CHANNEL) {
    // externalNoteStates[note] = false;
  }
}
