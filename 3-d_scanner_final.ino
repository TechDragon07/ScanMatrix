#define z_step 6
#define z_dir 7
#define tt_step 2
#define tt_dir 3

#define sensorPin A1

const int zStepsPerMM = 100; // 1mm = 100 steps (half revolution for 2mm pitch)
const int totalSlices = 8200 / zStepsPerMM; // length of the object, recommended to change for time effectiveness
const int stepsPerSlice = 100; // 1 mm/slice
const int turntableSteps = 200; // 360° / 1.8° = 200 steps

#include <SPI.h>
#include <SD.h>

#define CS_PIN 10 

File dataFile;

void setup() {

  pinMode(z_step, OUTPUT);
  pinMode(z_dir, OUTPUT);
  pinMode(tt_step, OUTPUT);
  pinMode(tt_dir, OUTPUT);

  digitalWrite(z_dir, HIGH); // Move Z up initially
  digitalWrite(tt_dir, HIGH); // Rotate turntable in one direction

  Serial.begin(9600);

  Serial.print("Initializing SD card... ");
  if (!SD.begin(CS_PIN))
  {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization success!");

  // Open file for writing
  dataFile = SD.open("scan1.txt", FILE_WRITE);
  if (dataFile) {

  } 
  else {
    Serial.println("Error opening scan1.txt!");
  }
}

void loop() {
  for (int slice = 0; slice < totalSlices; slice++) {
    for (int angleStep = 0; angleStep < turntableSteps; angleStep++) {
      long sum = 0;
      delay(50);
      for (int i = 0; i < 20; i++) {
        sum += analogRead(sensorPin);
        delay(10); // wait 10 ms
      }

      double senseDistance = sum / 20;
      senseDistance = mapDouble(senseDistance, 0.0, 1023.0, 0.0, 5.0); // Convert analog pin reading to voltage
      senseDistance = -5.40274 * pow(senseDistance, 3) + 28.4823 * pow(senseDistance, 2) - 49.7115 * senseDistance + 31.3444; // Convert voltage to distance in cm

      // Write senseDistance to SD file
      dataFile = SD.open("scan1.txt", FILE_WRITE);
      if (dataFile) {
        dataFile.println(senseDistance);
        dataFile.close();
      }

      stepMotor(tt_step, 1, 1000); // 1 step = 1.8 degrees
    }

    // Move Z up by 1 mm (100 steps)
    stepMotor(z_step, zStepsPerMM, 1000);
    
      // Write senseDistance to SD file
    dataFile = SD.open("scan1.txt", FILE_WRITE);
    if (dataFile) {
      dataFile.println(999);
      dataFile.close();
      }

  }

  // Move Z all the way back down
  digitalWrite(z_dir, LOW);
  stepMotor(z_step, totalSlices * zStepsPerMM, 1000);

  while (true);
}

void stepMotor(int stepPin, int steps, int delayMicros) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayMicros);
  }
}

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
