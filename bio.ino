/*
  Biometric Sensing and Responsive Therapeutics System

  Current version:
  reads raw sensor values from the FSR, potentiometer, and tilt switch
  and prints them to the Serial Monitor.
*/

const int PRESSURE_PIN = A0;
const int BIOSIGNAL_PIN = A1;
const int MOTION_PIN = 2;

void setup() {
  Serial.begin(115200);
  pinMode(MOTION_PIN, INPUT);

  Serial.println("Biometric Sensing System");
  Serial.println("fsr,potentiometer,tilt");
}

void loop() {
  int pressureValue = analogRead(PRESSURE_PIN);
  int bioSignalValue = analogRead(BIOSIGNAL_PIN);
  int motionValue = digitalRead(MOTION_PIN);

  Serial.print(pressureValue);
  Serial.print(",");
  Serial.print(bioSignalValue);
  Serial.print(",");
  Serial.println(motionValue);

  delay(100);
}
