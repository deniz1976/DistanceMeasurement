// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "40ebef71-b8b2-4353-a7c0-b018b445c34a";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onWaterChange();
void onAddWaterChange();
void onSystemStateChange();

float water;
bool addWater;
bool systemState;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(water, READWRITE, ON_CHANGE, onWaterChange);
  ArduinoCloud.addProperty(addWater, READWRITE, ON_CHANGE, onAddWaterChange);
  ArduinoCloud.addProperty(systemState, READWRITE, ON_CHANGE, onSystemStateChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
