#include <Melopero_VL53L1X.h>

Melopero_VL53L1X sensor;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Starting...");
  VL53L1_Error stat = 0;
  Serial.println(stat);
  Serial.println(sensor.errorString);
  Serial.println("SR done...");
  stat = sensor.waitDeviceBooted();
  Serial.println(stat);
  //Serial.println(sensor.errorString);
  sensor.dataInit();
  Serial.println("DATA INIT done...");
  //Serial.println(sensor.errorString);
  sensor.staticInit();
  Serial.println("STATIC INIT done...");
  //Serial.println(sensor.errorString);
  Serial.println("Device Initialized...");
  
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
