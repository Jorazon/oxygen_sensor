/**
 * @author  Oskari Pahkala
 * @version V1.0
 * @date    2025-02-25
 * @url     https://github.com/Jorazon/EOxygenSensor
 * Based on https://github.com/DFRobot/DFRobot_EOxygenSensor
 */

#include "EOxygenSensor.h"
#include "delay.h"

/**
 * @brief Get oxygen concentration unit vol
 * @return concentration
 */
float readOxygenConcentration(int fd) {
    static float oldVol = 0.0;
    float vol;
    uint8_t buf[10] = {0x00};
    readData(fd, OXYGEN_DATA, buf, 3);
    vol = (float)buf[0] + ((float)buf[1])/10.0 + ((float)buf[2])/100.0;
    if(vol >= 0.00001 && vol <= -0.00001){
        return oldVol;
    }else{
        oldVol = vol;
        return vol;
    }
}

/**
 * @brief Check calibration status
 * @return state
 */
uint8_t readCalibrationState(int fd) {
    uint8_t buf[10] = {0x00};
    readData(fd, CALIBRATION_STATE, buf, 1);
    return buf[0];
}

/**
 * @brief Calibration in air with an O2 concentration of 20.9% Vol
 * @return Calibration success
 */
bool calibration_20_9(int fd) {
    uint8_t state = 0, data = CALIBRATION_20_9;
    writeData(fd, CALIBRATION_SENSOR, &data, 1);
    delay(2000);
    state = readCalibrationState(fd);
    if(state & CALIBRATION_20_9) return true;
    return false;
}

/**
 * @brief Calibration in air with an O2 concentration of 99.5% Vol
 * @return Calibration success
 */
bool calibration_99_5(int fd) {
    uint8_t state = 0, data = CALIBRATION_99_5;
    writeData(fd, CALIBRATION_SENSOR, &data, 1);
    delay(2000);
    state = readCalibrationState(fd);
    if(state & CALIBRATION_99_5)  return true;
    return false;
}

/**
 * @brief Clear calibration data
 * @return Clear success
 */
bool clearCalibration(int fd) {
    uint8_t state = 0, data = CALIBRATION_CLEAR;
    writeData(fd, CALIBRATION_SENSOR, &data, 1);
    delay(2000);
    state = readCalibrationState(fd);
    if(state == 0) return true;
    return false;
}

/**
 * @brief Read calibration parameters
 */
void readKB(int fd) {
    uint8_t buf[10] = {0x00};
    readData(fd, CALIBRATION_KB, buf, 6);
    printf("k: %f b: %f k0 %f\n",
        (float)buf[0] + (float)buf[1]/100.0f, /* slope, set to default on clear */
        (float)buf[2] + (float)buf[3]/100.0f, /* bias, set to 0 on clear */
        (float)buf[4] + (float)buf[5]/100.0f /* factory default slope (1.66) */
    );
}

/**
 * @brief Read maximum of 32 bytes at a time from device
 * @return The number of written bytes
 * @cite @misc{smbus-protocol, title = "SMBus Protocol Documentation", url = "https://www.kernel.org/doc/Documentation/i2c/smbus-protocol", note = "[Online; Accessed: 2025-02-25]"}
 */
int writeData(int fd, uint8_t reg, uint8_t *data, uint8_t len) {
    return i2c_smbus_write_i2c_block_data(fd, reg, len, data);
}

/**
 * @brief Write maximum of 32 bytes at a time to device
 * @return The number of read bytes
 * @cite @misc{smbus-protocol, title = "SMBus Protocol Documentation", url = "https://www.kernel.org/doc/Documentation/i2c/smbus-protocol", note = "[Online; Accessed: 2025-02-25]"}
 */
int readData (int fd, uint8_t reg, uint8_t *data, uint8_t len) {
    return i2c_smbus_read_i2c_block_data(fd, reg, len, data);
}
