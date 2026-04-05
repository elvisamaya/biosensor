/*
  Biometric Sensing and Responsive Therapeutics System

  Current version:
  reads sensor values from the FSR, potentiometer, and tilt switch,
  smooths the analog signals, and flags unusual conditions.
*/

const int PRESSURE_PIN = A0;
const int BIOSIGNAL_PIN = A1;
const int MOTION_PIN = 2;

const int WINDOW_SIZE = 10;

int pressureWindow[WINDOW_SIZE];
int bioWindow[WINDOW_SIZE];
int sampleIndex = 0;
bool buffersFilled = false;

const int PRESSURE_HIGH_THRESHOLD = 700;
const int PRESSURE_LOW_THRESHOLD = 300;
const int BIO_HIGH_THRESHOLD = 680;
const int BIO_LOW_THRESHOLD = 320;

void setup() {
  Serial.begin(115200);
  pinMode(MOTION_PIN, INPUT);

  initializeBuffers();

  Serial.println("Biometric Sensing System");
  Serial.println("avg_fsr,avg_potentiometer,tilt,pressure_alert,bio_alert,motion_alert");
}

void loop() {
  int pressureValue = analogRead(PRESSURE_PIN);
  int bioSignalValue = analogRead(BIOSIGNAL_PIN);
  int motionValue = digitalRead(MOTION_PIN);

  pressureWindow[sampleIndex] = pressureValue;
  bioWindow[sampleIndex] = bioSignalValue;

  sampleIndex++;
  if (sampleIndex >= WINDOW_SIZE) {
    sampleIndex = 0;
    buffersFilled = true;
  }

  int averagedPressure = computeAverage(pressureWindow);
  int averagedBio = computeAverage(bioWindow);

  bool pressureAlert =
    averagedPressure > PRESSURE_HIGH_THRESHOLD ||
    averagedPressure < PRESSURE_LOW_THRESHOLD;

  bool bioAlert =
    averagedBio > BIO_HIGH_THRESHOLD ||
    averagedBio < BIO_LOW_THRESHOLD;

  bool motionAlert = (motionValue == HIGH);

  Serial.print(averagedPressure);
  Serial.print(",");
  Serial.print(averagedBio);
  Serial.print(",");
  Serial.print(motionValue);
  Serial.print(",");
  Serial.print(pressureAlert ? "YES" : "NO");
  Serial.print(",");
  Serial.print(bioAlert ? "YES" : "NO");
  Serial.print(",");
  Serial.println(motionAlert ? "YES" : "NO");

  delay(100);
}

void initializeBuffers() {
  for (int i = 0; i < WINDOW_SIZE; i++) {
    pressureWindow[i] = 0;
    bioWindow[i] = 0;
  }
}

int computeAverage(int values[]) {
  long total = 0;

  for (int i = 0; i < WINDOW_SIZE; i++) {
    total += values[i];
  }

  return total / WINDOW_SIZE;
}
