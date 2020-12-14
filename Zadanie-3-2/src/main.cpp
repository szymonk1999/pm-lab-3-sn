#include <Arduino.h>
#include <Wire.h>

#define ADXL345_ADDR 0x53
#define ID_REG 0x00
#define POWER_CTL_REG 0x2D
#define DATA_FORMAT_REG 0x31

int16_t aX = 0, aY = 0, aZ = 0;
double dX = 0, dY = 0, dZ = 0;

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(4000);

  Wire.begin();

  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(ID_REG);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345_ADDR, (uint8_t)0x01, (uint8_t)1);

  Serial.print("Device ID: ");
  Serial.println(Wire.read());

  Wire.begin();
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(POWER_CTL_REG);
  Wire.write(0x08);
  Wire.endTransmission();

  delay(10);
}

void loop()
{
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(0x32);
  Wire.endTransmission();
  Wire.requestFrom(ADXL345_ADDR, (uint8_t)0x06, (uint8_t)1);

  aX = (Wire.read() | Wire.read() << 8);
  aY = (Wire.read() | Wire.read() << 8);
  aZ = (Wire.read() | Wire.read() << 8);

  dX = aX/255.0; dY = aY/255.0; dZ = aZ/255.0;

  Serial.print(" X: ");
  Serial.print(dX);
  Serial.print("Y:");
  Serial.print(dY);
  Serial.print(" Z: ");
  Serial.println(dZ);

  delay(2000);
}