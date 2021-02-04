#define PIR_PIN             3

#define ANIMATION_DURATION  60000
#define LIFECYCLE_DURATION  120000

void setup() {
  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);  
}

void loop() {

  if (digitalRead(PIR_PIN)) {
    Serial.println("MOTION");
  }else{
    Serial.println("NO MOTION");
  }

  delay(500);
}
