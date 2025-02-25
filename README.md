# DFRobot Gravity: Electrochemical 0-100%Vol Oxygen / O2 Sensor

C code to calibrate and read oxygen concentration and calibration values from AO2 CiTiceL® oxygen sensor using a Raspberry Pi's I2C interface.

## Compilation

### Install dependencies

```
apt install cmake make gcc libi2c-dev
```

### Build

```
git clone https://github.com/Jorazon/oxygen_sensor.git
cd oxygen_sensor
mkdir build
cd build
cmake ..
make
./i2coxygen
```

---

[Gravity: Electrochemical Oxygen / O2 Sensor (0-100%Vol, I2C) (dfrobot.com)](https://www.dfrobot.com/product-2569.html)  
[DFRobot_EOxygenSensor (github.com)](https://github.com/DFRobot/DFRobot_EOxygenSensor)  
[SMBus Protocol Documentation (kernel.org)](https://www.kernel.org/doc/Documentation/i2c/smbus-protocol)  
