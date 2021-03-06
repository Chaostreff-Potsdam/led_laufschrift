// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)

void onHighlightColumnChange();
void onUptimeChange();

int highlightColumn;
int uptime;

void initProperties(){

  ArduinoCloud.addProperty(highlightColumn, READWRITE, ON_CHANGE, onHighlightColumnChange);
  ArduinoCloud.addProperty(uptime, READWRITE, ON_CHANGE, onUptimeChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

