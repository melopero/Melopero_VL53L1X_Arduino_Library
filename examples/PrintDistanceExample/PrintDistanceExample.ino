#include <Melopero_VL53L1X.h>

Melopero_VL53L1X sensor;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  Wire.begin();

  VL53L1_Error stat = 0;
  stat = sensor.initI2C(); // use sensor.initI2C(i2c_address, Wire1); to use Wire1 instead of Wire
  Serial.println(stat);
  stat = sensor.softwareReset();
  Serial.println(stat);
  stat = sensor.waitDeviceBooted();
  Serial.println(stat);

  stat = sensor.dataInit();
  Serial.println(stat);

  stat = sensor.staticInit();
  Serial.println(stat);

  /* (1) Three important functions to use to configure the sensor in fast mode */
  /*Device preset modes:
   * VL53L1_PRESETMODE_AUTONOMOUS
   * VL53L1_PRESETMODE_LITE_RANGING
   * VL53L1_PRESETMODE_LOWPOWER_AUTONOMOUS*/
  sensor.setPresetMode(VL53L1_PRESETMODE_AUTONOMOUS);
  sensor.setDistanceMode(VL53L1_DISTANCEMODE_MEDIUM);
  sensor.setMeasurementTimingBudgetMicroSeconds(10000);
  sensor.startMeasurement();
}

void loop() {
  sensor.waitMeasurementDataReady();
  sensor.getRangingMeasurementData();
  sensor.clearInterruptAndStartMeasurement();

  Serial.print((float)sensor.measurementData.RangeMilliMeter + (float)sensor.measurementData.RangeFractionalPart/256.0);
  Serial.println(" mm");
}
