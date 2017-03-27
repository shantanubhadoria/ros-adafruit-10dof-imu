#ifndef LSM303DLHC_Accelerometer_h
#define LSM303DLHC_Accelerometer_h

#include <stdint.h>
#include "I2CBus.h"

/* Device I2C Address */
#define LSM303DLHC_ACC_I2C_ADDRESS 0x19

/* Register Addresses */
#define LSM303DLHC_CTRL_REG1       0x20
#define LSM303DLHC_CTRL_REG1_VALUE 0x47 
#define LSM303DLHC_CTRL_REG4       0x23
#define LSM303DLHC_CTRL_REG4_VALUE 0x28

#define LSM303DLHC_OUT_X_L_A         0x28

typedef struct lsm303DLHCAccelData_s {
  lsm303DLHCAccelData_s() : x(0), y(0), z(0) {}
  int16_t x;
  int16_t y;
  int16_t z;
} lsm303DLHCAccelData;

class LSM303DLHC_Accelerometer {
  public:
    lsm303DLHCAccelData raw;

    LSM303DLHC_Accelerometer(const char * i2cDeviceFilePath);

    void begin(void);
    void read(void);
    bool verifyConnection(void);
  private:
    I2CBus i2cObject;
};

#endif

