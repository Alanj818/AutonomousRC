#include "IMU.h"

IMU::IMU() {}

void IMU::begin(){
  //here we will initialize I2C stuff
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}

void IMU::update(){
  Serial.println("IMU Data: ");
  Serial.println(data_converted.accel_x);
  Serial.println(data_converted.accel_y);
  Serial.println(data_converted.accel_z);
  Serial.println(data_converted.temp);
  Serial.println(data_converted.gyro_x);
  Serial.println(data_converted.gyro_y);
  Serial.println(data_converted.gyro_z);
}

void IMU::fillData(){
  Wire.beginTransmission(0x68); // START Condition and ADDRESS + WRITE bit 0
  Wire.write(0x3B); //REGISTER ADRESS
  Wire.endTransmission(false); //NEW START Condition 

  //Sequence for Reading is: Master(START, ADRESSS+WRITE), Slave(Acknowledge), Master(Register Address), Slave(Acknowledge), Master(Start again, Address+Read), Slave(Acknowledge + Data from Register Address), Master(NotAcknowledge + Stop condition);

  if(Wire.requestFrom(0x68, 14) == 14){  //ADDRESS + READ bit 1, 14 bytes of reading from i2c address from register address 
    //acceleration data, HIGHBYTE | LOWBYTE
    data.accel_x = (Wire.read() << 8) | Wire.read();
    data.accel_y = (Wire.read() << 8) | Wire.read();
    data.accel_z = (Wire.read() << 8) | Wire.read();

    //Temp data, HIGHBYTE | LOWBYTE
    data.temp = (Wire.read() << 8) | Wire.read();

    //Gyro Dat, HIGHBYTE | LOWBYTE
    data.gyro_x = (Wire.read() << 8) | Wire.read();
    data.gyro_y = (Wire.read() << 8) | Wire.read();
    data.gyro_z = (Wire.read() << 8) | Wire.read();
  } else {
    Serial.println(Wire.requestFrom(0x68, 14));
  }
}

IMU_DATA IMU::getData() const{
  return data;
}

void IMU::handleDataConversion(){
  data_converted.accel_x = data.accel_x / 16384.0f;
  data_converted.accel_y = data.accel_y / 16384.0f;
  data_converted.accel_z = data.accel_z / 16384.0f;

  data_converted.temp = data.temp / 340.0f + 36.53f;

  data_converted.gyro_x = data.gyro_x / 131.0f;
  data_converted.gyro_y = data.gyro_y / 131.0f;
  data_converted.gyro_z = data.gyro_z / 131.0f;
}