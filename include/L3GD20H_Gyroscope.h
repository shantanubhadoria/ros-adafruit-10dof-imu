#ifndef L3GD20H_Gyroscope_h
#define L3GD20H_Gyroscope_h

#include <stdint.h>
#include "I2CBus.h"

/* Device I2C Address */
#define L3GD20H_GYRO_I2C_ADDRESS   0x6B

/* Register Addresses */
#define L3GD20H_REGISTER_WHO_AM_I  0x0F

#define L3GD20H_REGISTER_CTRL_REG1 0x20
#define L3GD20H_REGISTER_CTRL_REG4 0x23

#define L3GD20H_OUT_X_L            0x28

/* Constants */
#define L3GD20H_ID             0xD7

typedef struct l3gd20hGyroData_s {
  l3gd20hGyroData_s() : x(0), y(0), z(0) {}
  int16_t x;
  int16_t y;
  int16_t z;
} l3gd20hGyroData;

class L3GD20H_Gyroscope {
  public:
    l3gd20hGyroData raw;

    L3GD20H_Gyroscope(const char * i2cDeviceFilePath);

    void begin(void);
    void read(void);
    bool verifyConnection(void);
    bool verifyType(void);
  private:
    I2CBus i2cObject;
};

#endif

