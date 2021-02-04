
#include "Song_PiratesOfTheCarribean.h"
Song_PiratesOfTheCarribean::Song_PiratesOfTheCarribean(uint8_t pinBuzzer, float songSpeed) {
    this->_buzzerPin = pinBuzzer;
    this->_songSpeed = songSpeed;
    this->_notes = Song_PiratesOfTheCarribean_Notes;
    this->_durations = Song_PiratesOfTheCarribean_Durations;
}

void Song_PiratesOfTheCarribean::Play() {
    for (int i = 0; i < this->_numNotes; i++) {              
        int wait = this->_durations[i] * this->_songSpeed;
        tone(this->_buzzerPin, _notes[i], wait);
        delay(wait);
    }   
}