#ifndef LSM303DLHC_Magnetometer_h
#define LSM303DLHC_Magnetometer_h

#include <stdint.h>
#include "I2CBus.h"

/* Device I2C Address */
#define LSM303DLHC_MAG_I2C_ADDRESS 0x1E

/* Register Addresses */
#define LSM303DLHC_CRA_REG_M       0x00
#define LSM303DLHC_CRA_REG_M_VALUE 0x0C

#define LSM303DLHC_CRB_REG_M       0x01
#define LSM303DLHC_CRB_REG_M_VALUE 0x20

#define LSM303DLHC_MR_REG_M        0x02
#define LSM303DLHC_MR_REG_M_VALUE  0x00

#define LSM303DLHC_OUT_X_H_M       0x03
#define LSM303DLHC_OUT_X_L_M       0x04
#define LSM303DLHC_OUT_Z_H_M       0x05
#define LSM303DLHC_OUT_Z_L_M       0x06
#define LSM303DLHC_OUT_Y_H_M       0x07
#define LSM303DLHC_OUT_Y_L_M       0x08

typedef struct lsm303DLHCMagData_s {
  lsm303DLHCMagData_s() : x(0), y(0), z(0) {}
  int16_t x;
  int16_t y;
  int16_t z;
} lsm303DLHCMagData;

class LSM303DLHC_Magnetometer {
  public:
    lsm303DLHCMagData raw;

    LSM303DLHC_Magnetometer(const char * i2cDeviceFilePath);

    void begin(void);
    void read(void);
    void setMagRate(void);
    void setMagGain(void);
    bool verifyConnection(void);
  private:
    I2CBus i2cObject;
};

#endif

