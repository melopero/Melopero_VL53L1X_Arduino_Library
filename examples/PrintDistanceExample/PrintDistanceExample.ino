#include <Melopero_VL53L1X.h>

Melopero_VL53L1X sensor;
VL53L1_Error statusCode;

void setup() {
  Serial.begin(9600);

  statusCode = sensor.waitDeviceBooted();
  statusCode = sensor.dataInit();
  statusCode = sensor.staticInit();
  /* (1) Three important functions to use to configure the sensor in fast mode */
  /*Device preset modes:
   * VL53L1_PRESETMODE_AUTONOMOUS
   * VL53L1_PRESETMODE_LITE_RANGING
   * VL53L1_PRESETMODE_LOWPOWER_AUTONOMOUS*/
  statusCode = sensor.setPresetMode(VL53L1_PRESETMODE_LITE_RANGING);
  statusCode = sensor.setDistanceMode(VL53L1_DISTANCEMODE_SHORT);
  statusCode = sensor.setMeasurementTimingBudgetMicroSeconds(10000);
  statusCode = sensor.startMeasurement();
}

void loop() {
  statusCode = sensor.waitMeasurementDataReady();
  statusCode = sensor.getRangingMeasurementData();
  statusCode = sensor.clearInterruptAndStartMeasurement();

  Serial.print((float)sensor.measurementData.RangeMilliMeter + (float)sensor.measurementData.RangeFractionalPart/256.0);
  Serial.println(" mm");
}
