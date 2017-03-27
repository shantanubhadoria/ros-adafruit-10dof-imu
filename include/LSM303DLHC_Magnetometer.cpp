#include "LSM303DLHC_Magnetometer.h"

LSM303DLHC_Magnetometer::LSM303DLHC_Magnetometer(const char * i2cDeviceFilePath) : i2cObject(i2cDeviceFilePath) {
  i2cObject.addressSet(LSM303DLHC_MAG_I2C_ADDRESS);
}

void LSM303DLHC_Magnetometer::begin(void) {
  i2cObject.writeByte(LSM303DLHC_MR_REG_M, LSM303DLHC_MR_REG_M_VALUE);

  setMagRate();
}

void LSM303DLHC_Magnetometer::read(void) {
  uint8_t block[6];
  i2cObject.readBlock(0x80 | LSM303DLHC_OUT_X_H_M, sizeof(block), block);
  raw.x = (int16_t)(block[1] | block[0] << 8);
  raw.y = (int16_t)(block[5] | block[4] << 8);
  raw.z = (int16_t)(block[3] | block[2] << 8);
}

void LSM303DLHC_Magnetometer::setMagRate(void) {
  i2cObject.writeByte(LSM303DLHC_CRA_REG_M, LSM303DLHC_CRA_REG_M_VALUE);
}

void LSM303DLHC_Magnetometer::setMagGain(void) {
  i2cObject.writeByte(LSM303DLHC_CRB_REG_M, LSM303DLHC_CRB_REG_M_VALUE);
}

bool LSM303DLHC_Magnetometer::verifyConnection(void) {
  /* write default val to CRA REG and read to ensure we are connected */
  uint8_t craRegMValue = i2cObject.readByte(LSM303DLHC_CRA_REG_M);

  if (craRegMValue  == LSM303DLHC_CRA_REG_M_VALUE) {
    return true;
  }
  return false;
}


