#include <Melopero_VL53L1X.h>

Melopero_VL53L1X sensor;

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Starting...");

  VL53L1_Error status = 0;
  status = sensor.initDevice();
  printStatus("Device initialized : ", sensor.errorString);
  
  status = sensor.setDistanceMode(VL53L1_DISTANCEMODE_MEDIUM);
  printStatus("Set distance mode : ", sensor.errorString);

  /*  Timing budget is the time required by the sensor to perform one range 
   *  measurement. The minimum and maximum timing budgets are [20 ms, 1000 ms] */
  status = sensor.setMeasurementTimingBudgetMicroSeconds(10000);
  printStatus("Set timing budget: ", sensor.errorString);

  /*  Sets the inter-measurement period (the delay between two ranging operations) in milliseconds. The minimum 
   *  inter-measurement period must be longer than the timing budget + 4 ms.*/
  status = sensor.setInterMeasurementPeriodMilliSeconds(20);
  printStatus("Set inter measurement time: ", sensor.errorString);

  //If the above constraints are not respected the status is -4: VL53L1_ERROR_INVALID_PARAMS

  sensor.startMeasurement();
}

void loop() {
  VL53L1_Error status = 0;

  status = sensor.waitMeasurementDataReady();
  if (status != VL53L1_ERROR_NONE) printStatus("Error in wait data ready: ",  sensor.errorString);

  status = sensor.getRangingMeasurementData();
  if (status != VL53L1_ERROR_NONE) printStatus("Error in get measurement data: ",  sensor.errorString);

  status = sensor.clearInterruptAndStartMeasurement();
  if (status != VL53L1_ERROR_NONE) printStatus("Error in clear interrupts: ",  sensor.errorString);

  Serial.print((float)sensor.measurementData.RangeMilliMeter + (float)sensor.measurementData.RangeFractionalPart/256.0);
  Serial.println(" mm");
}

void printStatus(String msg, String status){
  Serial.print(msg);
  Serial.println(sensor.errorString);
}
