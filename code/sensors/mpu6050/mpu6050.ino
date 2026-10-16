#include <Wire.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Wire.begin(21, 22);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();
}

int16_t readWord(uint8_t reg) {
  Wire.beginTransmission(0x68);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, (uint8_t)2);
  int16_t val = Wire.read() << 8 | Wire.read();
  return val;
}

void loop() {
  float ax = readWord(0x3B) / 16384.0;
  float ay = readWord(0x3D) / 16384.0;
  float az = readWord(0x3F) / 16384.0;
  float gx = readWord(0x43) / 131.0;
  float gy = readWord(0x45) / 131.0;
  float gz = readWord(0x47) / 131.0;

  Serial.print(ax); Serial.print(",");
  Serial.print(ay); Serial.print(",");
  Serial.print(az); Serial.print(",");
  Serial.print(gx); Serial.print(",");
  Serial.print(gy); Serial.print(",");
  Serial.println(gz);

  delay(1000);
}
