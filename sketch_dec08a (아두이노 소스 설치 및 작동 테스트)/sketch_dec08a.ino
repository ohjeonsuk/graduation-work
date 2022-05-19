/*
  GY-521 자이로&가속도 센서 (MPU-6050)
  예제입니다.

  UNO R3 : http://kit128.com/goods/view?no=71
  GY-521 자이로&가속도 센서 (MPU-6050) 모듈 : http://kit128.com/goods/view?no=146

  출처: http://whiteat.com/Arduino

*/

#include<Wire.h>
const int MPU = 0x68;  // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;


// 프로그램 시작 - 초기화 작업
void setup()
{
  Serial.begin(9600);     // 시리얼 통신 초기화
  Serial.println("Arduino Examples - GY-521 Gyro& Accelator (MPU-6050) Module");
  Serial.println("    http://docs.whiteat.com/?p=2662");


  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // gyro scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);  //
  Wire.write(0xF8);     //
  Wire.endTransmission(true);

  // acc scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);  //
  Wire.write(0xF8);     //
  Wire.endTransmission(true);

}

void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);  // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  /*
    Serial.print("AcX = "); Serial.print(AcX);
    Serial.print(" | AcY = "); Serial.print(AcY);
    Serial.print(" | AcZ = "); Serial.print(AcZ);
    Serial.print(" | Tmp = "); Serial.print(Tmp / 340.00 + 36.53);  //equation for temperature in degrees C from datasheet
    Serial.print(" | GyX = "); Serial.print(GyX);
    Serial.print(" | GyY = "); Serial.print(GyY);
    Serial.print(" | GyZ = "); Serial.println(GyZ);
    delay(333);
  */


  int xAxis = (AcX - 1090);
  int yAxis = (AcY - 930);
  int zAxis = (AcZ - 1000);
  
  Serial.print(xAxis);
  Serial.print(" ");
  Serial.print(yAxis);
  Serial.print(" ");
  Serial.print(zAxis);
  Serial.println(" ");

  delay(50);
}
