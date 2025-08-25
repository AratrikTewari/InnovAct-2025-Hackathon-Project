int tempPin = A1;   // LM35 sensor pin
int uvPin   = A2;   // OUT pin of ML8511

float temperature;
int uvValue = 0;
float uvVoltage = 0.0;
float uvIntensity = 0.0;  // in mW/cm²

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  // ---- Temperature (LM35) ----
  long sum = 0;
  int samples = 10;   // number of readings to average
  
  for (int i = 0; i < samples; i++) {
    sum += analogRead(tempPin);
    delay(10);  // short delay between readings
  }
  
  int avgValue = sum / samples;
  float voltage = avgValue * (5.0 / 1023.0);   // ADC to voltage
  temperature = voltage * 100.0;               // LM35: 10mV per °C
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // ---- UV Sensor (ML8511) ----
  uvValue = analogRead(uvPin);
  uvVoltage = uvValue * (5.0 / 1023.0);   // ADC to voltage (for 5V Arduino)
  
  // Convert voltage to UV intensity (approx)
  uvIntensity = (uvVoltage - 1.0) * 15.0;
  if (uvIntensity < 0) uvIntensity = 0;  // clamp to zero
  
  Serial.print("UV Voltage: ");
  Serial.print(uvVoltage);
  Serial.print(" V   UV Intensity: ");
  Serial.print(uvIntensity);
  Serial.println(" mW/cm^2");

  Serial.println("--------------------------");
  delay(1000);  // 1-second delay
}
