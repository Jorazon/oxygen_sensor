/**
 * @author  Oskari Pahkala
 * @version V1.0
 * @date    2025-02-25
 * @url     https://github.com/Jorazon/EOxygenSensor
 * Based on https://github.com/DFRobot/DFRobot_EOxygenSensor
 */

#ifndef __LINUX_I2C_DFRobot_EOxygenSensor__
#define __LINUX_I2C_DFRobot_EOxygenSensor__ 1

#include <stdint.h>
#include <stdbool.h>

#define I2C_PORT           0x01

#define E_OXYGEN_ADDRESS_0 0x70 /* A0=0, A1=0 */
#define E_OXYGEN_ADDRESS_1 0x71 /* A0=1, A1=0 */
#define E_OXYGEN_ADDRESS_2 0x72 /* A0=0, A1=1 */
#define E_OXYGEN_ADDRESS_3 0x73 /* A0=1, A1=1 */

#define OXYGEN_DATA        0x10
#define CALIBRATION_STATE  0x13
#define CALIBRATION_SENSOR 0x18
#define CALIBRATION_KB     0x19

#define CALIBRATION_20_9   0x01
#define CALIBRATION_99_5   0x02
#define CALIBRATION_CLEAR  0x03

float   readOxygenConcentration(int fd);
uint8_t readCalibrationState(int fd);
bool    calibration_20_9(int fd);
bool    calibration_99_5(int fd);
bool    clearCalibration(int fd);

void    readKB(int fd);

void    dumpROM(int fd);

int     readData (int fd, uint8_t reg, uint8_t *data, uint8_t len);
int     writeData(int fd, uint8_t reg, uint8_t *data, uint8_t len);

#endif /* __LINUX_I2C_DFRobot_EOxygenSensor__ */
