//Author: Leonardo La Rocca
#include "Melopero_VL53L1X.h"
#include "Wire.h"

Melopero_VL53L1X::Melopero_VL53L1X(uint8_t i2cAddr){
    device = &dev;
    device->I2cDevAddr = i2cAddr;
    Wire.begin();
}

//Device initialization functions
VL53L1_Error Melopero_VL53L1X::setDeviceAddress(uint8_t newAddress){
    VL53L1_Error status =  VL53L1_SetDeviceAddress(device, newAddress);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::dataInit(){
    VL53L1_Error status = VL53L1_DataInit(device);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::staticInit(){
    VL53L1_Error status = VL53L1_StaticInit(device);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::waitDeviceBooted(){
    VL53L1_Error status = VL53L1_WaitDeviceBooted(device);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::softwareReset(){
    VL53L1_Error status = VL53L1_software_reset(device);
    getErrorDescription(status);
    return status;
}

//Parameters
VL53L1_Error Melopero_VL53L1X::setPresetMode(VL53L1_PresetModes mode){
    VL53L1_Error status = VL53L1_SetPresetMode(device, mode);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getPresetMode(){
    VL53L1_Error status = VL53L1_GetPresetMode(device, &presetMode);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::setDistanceMode(VL53L1_DistanceModes newDistanceMode){
    VL53L1_Error status = VL53L1_SetDistanceMode(device, newDistanceMode);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getDistanceMode(){
    VL53L1_Error status = VL53L1_GetDistanceMode(device, &distanceMode);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::setMeasurementTimingBudgetMicroSeconds(uint32_t measurementTimingBudgetMicroSeconds){
    VL53L1_Error status = VL53L1_SetMeasurementTimingBudgetMicroSeconds(device, measurementTimingBudgetMicroSeconds);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getMeasurementTimingBudgetMicroSeconds(){
    VL53L1_Error status = VL53L1_GetMeasurementTimingBudgetMicroSeconds(device, &measurementTimingBudgetMicros);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::setInterMeasurementPeriodMilliSeconds (uint32_t interMeasurementPeriodMilliSeconds){
    VL53L1_Error status = VL53L1_SetInterMeasurementPeriodMilliSeconds(device, interMeasurementPeriodMilliSeconds);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getInterMeasurementPeriodMilliSeconds(){
    VL53L1_Error status = VL53L1_GetInterMeasurementPeriodMilliSeconds(device, &interMeasurementPeriodMillis);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::setUserROI(uint8_t topLeftX, uint8_t topLeftY, uint8_t botRightX, uint8_t botRightY){
    userROI.TopLeftX = topLeftX;
    userROI.TopLeftY = topLeftY;
    userROI.BotRightX = botRightX;
    userROI.BotRightY = botRightY;
    VL53L1_Error status = VL53L1_SetUserROI(device, &userROI);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getUserROI(){
    VL53L1_Error status = VL53L1_GetUserROI(device, &userROI);
    getErrorDescription(status);
    return status;
}

//Ranging functions
VL53L1_Error Melopero_VL53L1X::startMeasurement(){
    VL53L1_Error status = VL53L1_StartMeasurement(device);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::stopMeasurement(){
    VL53L1_Error status = VL53L1_StopMeasurement(device);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::clearInterruptAndStartMeasurement(){
    VL53L1_Error status = VL53L1_ClearInterruptAndStartMeasurement(device);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getMeasurementDataReady(){
    uint8_t isDataReady;
    VL53L1_Error status = VL53L1_GetMeasurementDataReady(device, &isDataReady);
    dataReady = isDataReady == 0? false : true;
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::waitMeasurementDataReady(){
    VL53L1_Error status = VL53L1_WaitMeasurementDataReady(device);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getRangingMeasurementData(){
    VL53L1_Error status = VL53L1_GetRangingMeasurementData(device, &measurementData);
    getErrorDescription(status);
    return status;
}

//Interrupt functions
VL53L1_Error Melopero_VL53L1X::enableInterruptOnDataReady(){
    interruptConfig.DetectionMode = VL53L1_DETECTION_NORMAL_RUN;
    VL53L1_Error status = VL53L1_SetThresholdConfig(device, &interruptConfig);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::enableInterruptOnDistance(VL53L1_ThresholdMode mode, uint16_t high, uint16_t low){
    interruptConfig.DetectionMode = VL53L1_DETECTION_DISTANCE_ONLY;
    interruptConfig.Distance.CrossMode = mode;
    interruptConfig.Distance.High = high;
    interruptConfig.Distance.Low = low;
    VL53L1_Error status = VL53L1_SetThresholdConfig(device, &interruptConfig);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getInterruptConfig(){
    VL53L1_Error status = VL53L1_GetThresholdConfig(device, &interruptConfig);
    getErrorDescription(status);
    return status;
}

VL53L1_Error Melopero_VL53L1X::getErrorDescription(VL53L1_Error error){
    return VL53L1_GetPalErrorString(error, errorString);
    //return VL53L1_ERROR_NONE;
}
