//Author: Leonardo La Rocca
#include "Melopero_VL53L1X.h"
#include "Wire.h"

Melopero_VL53L1X::Melopero_VL53L1X(uint8_t i2cAddr){
    device.I2cDevAddr = i2cAddr;
    Wire.begin();
}

//Device initialization functions
VL53L1_Error Melopero_VL53L1X::setDeviceAddress(uint8_t newAddress){
    return VL53L1_SetDeviceAddress(device, newAddress);
}

VL53L1_Error Melopero_VL53L1X::dataInit(){
    return VL53L1_DataInit(device);
}

VL53L1_Error Melopero_VL53L1X::staticInit(){
    return VL53L1_StaticInit(device);
}

VL53L1_Error Melopero_VL53L1X::waitDeviceBooted(){
    return VL53L1_WaitDeviceBooted(device);
}

//Parameters
VL53L1_Error Melopero_VL53L1X::setDistanceMode(VL53L1_DistanceModes newDistanceMode){
    return VL53L1_SetDistanceMode(device, newDistanceMode);
}

VL53L1_Error Melopero_VL53L1X::getDistanceMode(){
    return VL53L1_GetDistanceMode(device, &distanceMode);
}

VL53L1_Error Melopero_VL53L1X::setMeasurementTimingBudgetMicroSeconds(uint32_t measurementTimingBudgetMicroSeconds){
    return VL53L1_SetMeasurementTimingBudgetMicroSeconds(device, measurementTimingBudgetMicroSeconds);
}

VL53L1_Error Melopero_VL53L1X::getMeasurementTimingBudgetMicroSeconds(){
    return VL53L1_GetMeasurementTimingBudgetMicroSeconds(device, &measurementTimingBudgetMicros);
}

VL53L1_Error Melopero_VL53L1X::setInterMeasurementPeriodMilliSeconds (uint32_t interMeasurementPeriodMilliSeconds){
    return VL53L1_SetInterMeasurementPeriodMilliSeconds(device, interMeasurementPeriodMilliSeconds);
}

VL53L1_Error Melopero_VL53L1X::getInterMeasurementPeriodMilliSeconds(){
    return VL53L1_GetInterMeasurementPeriodMilliSeconds(device, &interMeasurementPeriodMillis);
}

VL53L1_Error Melopero_VL53L1X::setUserROI(uint8_t topLeftX, uint8_t topLeftY, uint8_t botRightX, uint8_t botRightY){
    userROI.TopLeftX = topLeftX;
    userROI.TopLeftY = topLeftY;
    userROI.BotRightX = botRightX;
    userROI.BotRightY = botRightY;
    return VL53L1_SetUserROI(device, &userROI);
}

VL53L1_Error Melopero_VL53L1X::getUserROI(){
    return VL53L1_GetUserROI(device, &userROI);
}

//Ranging functions
VL53L1_Error Melopero_VL53L1X::startMeasurement(){
    return VL53L1_StartMeasurement(device);
}

VL53L1_Error Melopero_VL53L1X::stopMeasurement(){
    return VL53L1_StopMeasurement(device);
}

VL53L1_Error Melopero_VL53L1X::clearInterruptAndStartMeasurement(){
    return VL53L1_ClearInterruptAndStartMeasurement(device);
}

VL53L1_Error Melopero_VL53L1X::getMeasurementDataReady(){
    uint8_t isDataReady;
    VL53L1_Error status = VL53L1_GetMeasurementDataReady(device, &isDataReady);
    dataReady = isDataReady == 0? false : true;
    return status;
}

VL53L1_Error Melopero_VL53L1X::waitMeasurementDataReady(){
    return VL53L1_WaitMeasurementDataReady(device);
}

VL53L1_Error Melopero_VL53L1X::getRangingMeasurementData(){
    return VL53L1_GetRangingMeasurementData(device, &measurementData);
}

//Interrupt functions
VL53L1_Error Melopero_VL53L1X::enableInterruptOnDataReady(bool enable = true);
VL53L1_Error Melopero_VL53L1X::enableInterruptOnDistance(bool enable = true);
VL53L1_Error Melopero_VL53L1X::setDistanceInterruptConfig(VL53L1_ThresholdMode mode, uint16_t high, uint16_t low);
VL53L1_Error Melopero_VL53L1X::getDistanceInterruptConfig();

VL53L1_Error Melopero_VL53L1X::getErrorDescription(VL53L1_Error error){
    return VL53L1_GetPalErrorString(error, errorString);
}
