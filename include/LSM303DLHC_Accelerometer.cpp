#include "LSM303DLHC_Accelerometer.h"

LSM303DLHC_Accelerometer::LSM303DLHC_Accelerometer(const char * i2cDeviceFilePath) : i2cObject(i2cDeviceFilePath) {
  i2cObject.addressSet(LSM303DLHC_ACC_I2C_ADDRESS);
}

void LSM303DLHC_Accelerometer::begin(void) {
  i2cObject.writeByte(LSM303DLHC_CTRL_REG1, LSM303DLHC_CTRL_REG1_VALUE);
  i2cObject.writeByte(LSM303DLHC_CTRL_REG4, LSM303DLHC_CTRL_REG4_VALUE);
}

void LSM303DLHC_Accelerometer::read(void) {
  uint8_t block[6];
  i2cObject.readBlock(0x80 | LSM303DLHC_OUT_X_L_A, sizeof(block), block);
  raw.x = (int16_t)(block[0] | block[1] << 8);
  raw.y = (int16_t)(block[2] | block[3] << 8);
  raw.z = (int16_t)(block[4] | block[5] << 8);
}

bool LSM303DLHC_Accelerometer::verifyConnection(void) {
  uint8_t ctrlReg1AValue = i2cObject.readByte(LSM303DLHC_CTRL_REG1);

  if (ctrlReg1AValue == LSM303DLHC_CTRL_REG1_VALUE) {
    return true;
  }
  return false;
}

