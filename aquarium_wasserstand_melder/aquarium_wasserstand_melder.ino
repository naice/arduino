#define PIN_WATER_SENS        PIN_A5
#define PIN_BUZZER            PIN_A3
#define NUM_WATER_RECORDS     10
#define TIMEOUT_WATER_RECORD  1000 
#define MAX_WATERLEVEL_VALUE  600

#include <JTimeout.h>
#include <Song_PiratesOfTheCarribean.h>
Song_PiratesOfTheCarribean song(PIN_BUZZER, 1.3);

JTimeout waterRecordTimeout(TIMEOUT_WATER_RECORD, true);
uint16_t waterRecords[NUM_WATER_RECORDS];

bool isWaterLevelWarningTriggered = false;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_WATER_SENS, INPUT);
}
void loop() {
  if (!isWaterLevelWarningTriggered && waterRecordTimeout.CanExecute()) {
    uint16_t value = analogRead(PIN_WATER_SENS);
    Serial.println(value);
    push(waterRecords, NUM_WATER_RECORDS, value);
    if (allAbove(waterRecords, NUM_WATER_RECORDS, MAX_WATERLEVEL_VALUE)) {
      isWaterLevelWarningTriggered = true;
      Serial.println(MAX_WATERLEVEL_VALUE);
    }
    for (uint8_t i = 0; i < NUM_WATER_RECORDS; i++)
    {
      if (i>0) Serial.print(", ");
      Serial.print(waterRecords[i]);
    }
    Serial.println();
  }

  if (isWaterLevelWarningTriggered) {
    song.Play();
  }
}

void push(uint16_t * array, uint16_t len, uint16_t value) 
{
	uint16_t last = value;
	for (int i = 0; i < len; i++)
	{
		uint16_t current = array[i];
		array[i] = last;
		last = current;
	}
}

bool allAbove(uint16_t * array, uint16_t len, uint16_t value) 
{
	for (int i = 0; i < len; i++)
	{
    if (array[i] < value)
      return false;
	}

  return true;
}