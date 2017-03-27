#include "L3GD20H_Gyroscope.h"

L3GD20H_Gyroscope::L3GD20H_Gyroscope(const char * i2cDeviceFilePath) : i2cObject(i2cDeviceFilePath) {
  i2cObject.addressSet(L3GD20H_GYRO_I2C_ADDRESS);
}

void L3GD20H_Gyroscope::begin(void) {
  /* Set CTRL_REG1 (0x20)
   ====================================================================
   BIT  Symbol    Description                                   Default
   ---  ------    --------------------------------------------- -------
   7-6  DR1/0     Output data rate                                   00
   5-4  BW1/0     Bandwidth selection                                00
     3  PD        0 = Power-down mode, 1 = normal/sleep mode          0
     2  ZEN       Z-axis enable (0 = disabled, 1 = enabled)           1
     1  YEN       Y-axis enable (0 = disabled, 1 = enabled)           1
     0  XEN       X-axis enable (0 = disabled, 1 = enabled)           1 */

  /* Reset then switch to normal mode and enable all three channels */
  i2cObject.writeByte(L3GD20H_REGISTER_CTRL_REG1, 0x00);
  i2cObject.writeByte(L3GD20H_REGISTER_CTRL_REG1, 0x0F);
  /* ------------------------------------------------------------------ */

  /* Set CTRL_REG4 (0x23)
   ====================================================================
   BIT  Symbol    Description                                   Default
   ---  ------    --------------------------------------------- -------
     7  BDU       Block Data Update (0=continuous, 1=LSB/MSB)         0
     6  BLE       Big/Little-Endian (0=Data LSB, 1=Data MSB)          0
   5-4  FS1/0     Full scale selection                               00
                                  00 = 250 dps
                                  01 = 500 dps
                                  10 = 2000 dps
                                  11 = 2000 dps
     0  SIM       SPI Mode (0=4-wire, 1=3-wire)                       0 */

  /* Adjust resolution if requested */
  i2cObject.writeByte(L3GD20H_REGISTER_CTRL_REG4, 0x20);
  /* ------------------------------------------------------------------ */
}

void L3GD20H_Gyroscope::read(void) {
  uint8_t block[6];
  i2cObject.readBlock(0x80 | L3GD20H_OUT_X_L, sizeof(block), block);
  raw.x = (int16_t)(block[0] | block[1] << 8);
  raw.y = (int16_t)(block[2] | block[3] << 8);
  raw.z = (int16_t)(block[4] | block[5] << 8);
}

bool L3GD20H_Gyroscope::verifyConnection(void) {
  uint8_t id = i2cObject.readByte(L3GD20H_REGISTER_WHO_AM_I);
  if (id == L3GD20H_ID) {
    return true;
  }
  return false;
}

bool L3GD20H_Gyroscope::verifyType(void) {
  uint8_t id = i2cObject.readByte(L3GD20H_REGISTER_WHO_AM_I);
  if (id == L3GD20H_ID) {
    return true;
  }
  return false;
}
