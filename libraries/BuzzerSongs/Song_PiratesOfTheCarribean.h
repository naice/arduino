

#ifndef _Song_PiratesOfTheCarribean_h
#define _Song_PiratesOfTheCarribean_h
#include "Arduino.h"

class Song_PiratesOfTheCarribean {
public:
	Song_PiratesOfTheCarribean(uint8_t pinBuzzer, float songSpeed);
    void Play();
private:
    int _buzzerPin = 0;
    float _songSpeed = 1.5; // higher = slower.
    const int _numNotes = 203;
    int * _notes;
    int * _durations;
};

const int Song_PiratesOfTheCarribean_NOTE_E4 = 330;
const int Song_PiratesOfTheCarribean_NOTE_G4 = 392;
const int Song_PiratesOfTheCarribean_NOTE_A4 = 440;
const int Song_PiratesOfTheCarribean_NOTE_B4 = 494;
const int Song_PiratesOfTheCarribean_NOTE_C5 = 523;
const int Song_PiratesOfTheCarribean_NOTE_D5 = 587;
const int Song_PiratesOfTheCarribean_NOTE_E5 = 659;
const int Song_PiratesOfTheCarribean_NOTE_F5 = 698;
const int Song_PiratesOfTheCarribean_NOTE_G5 = 784;

const int Song_PiratesOfTheCarribean_Notes[] = {
    Song_PiratesOfTheCarribean_NOTE_E4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_A4, 0, 
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_C5, 0, 
    Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_B4, 0,
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, 0,

    Song_PiratesOfTheCarribean_NOTE_E4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_A4, 0, 
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_C5, 0, 
    Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_B4, 0,
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, 0,

    Song_PiratesOfTheCarribean_NOTE_E4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_A4, 0, 
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_D5, 0, 
    Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_F5, Song_PiratesOfTheCarribean_NOTE_F5, 0,
    Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_A4, 0,

    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_C5, 0, 
    Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_A4, 0, 
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_B4, 0,
    Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, 0,

    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_A4, 
    //Repeat of first part
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_C5, 0, 
    Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_B4, 0,
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, 0,

    Song_PiratesOfTheCarribean_NOTE_E4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_A4, 0, 
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_C5, 0, 
    Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_B4, 0,
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, 0,

    Song_PiratesOfTheCarribean_NOTE_E4, Song_PiratesOfTheCarribean_NOTE_G4, Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_A4, 0, 
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_D5, 0, 
    Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_F5, Song_PiratesOfTheCarribean_NOTE_F5, 0,
    Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_A4, 0,

    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_C5, 0, 
    Song_PiratesOfTheCarribean_NOTE_D5, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_A4, 0, 
    Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_B4, 0,
    Song_PiratesOfTheCarribean_NOTE_C5, Song_PiratesOfTheCarribean_NOTE_A4, Song_PiratesOfTheCarribean_NOTE_B4, 0,
    //End of Repeat

    Song_PiratesOfTheCarribean_NOTE_E5, 0, 0, Song_PiratesOfTheCarribean_NOTE_F5, 0, 0,
    Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_E5, 0, Song_PiratesOfTheCarribean_NOTE_G5, 0, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_D5, 0, 0,
    Song_PiratesOfTheCarribean_NOTE_D5, 0, 0, Song_PiratesOfTheCarribean_NOTE_C5, 0, 0,
    Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, 0, Song_PiratesOfTheCarribean_NOTE_B4, 0, Song_PiratesOfTheCarribean_NOTE_A4,

    Song_PiratesOfTheCarribean_NOTE_E5, 0, 0, Song_PiratesOfTheCarribean_NOTE_F5, 0, 0,
    Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_E5, 0, Song_PiratesOfTheCarribean_NOTE_G5, 0, Song_PiratesOfTheCarribean_NOTE_E5, Song_PiratesOfTheCarribean_NOTE_D5, 0, 0,
    Song_PiratesOfTheCarribean_NOTE_D5, 0, 0, Song_PiratesOfTheCarribean_NOTE_C5, 0, 0,
    Song_PiratesOfTheCarribean_NOTE_B4, Song_PiratesOfTheCarribean_NOTE_C5, 0, Song_PiratesOfTheCarribean_NOTE_B4, 0, Song_PiratesOfTheCarribean_NOTE_A4
};
const int Song_PiratesOfTheCarribean_Durations[] = {
    125, 125, 250, 125, 125, 
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125, 

    125, 125, 250, 125, 125, 
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125, 

    125, 125, 250, 125, 125, 
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125, 
    250, 125, 250, 125, 
    125, 125, 250, 125, 125,
    125, 125, 375, 375,

    250, 125,
    //Rpeat of First Part
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125, 

    125, 125, 250, 125, 125, 
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 375, 125, 

    125, 125, 250, 125, 125, 
    125, 125, 250, 125, 125,
    125, 125, 250, 125, 125,
    125, 125, 125, 250, 125,

    125, 125, 250, 125, 125, 
    250, 125, 250, 125, 
    125, 125, 250, 125, 125,
    125, 125, 375, 375,
    //End of Repeat

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500,

    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 125, 125, 125, 375,
    250, 125, 375, 250, 125, 375,
    125, 125, 125, 125, 125, 500
};

#endif // _Song_PiratesOfTheCarribean_h