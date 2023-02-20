// 8 input alarm interface .
//
// ESP32 DEVKIT1 with 8 x opto isolators Input active high 24V, Output Active high 3.3V )
// 
// 
// 

#include "sensesp/sensors/analog_input.h"
#include "sensesp/sensors/digital_input.h"
#include "sensesp/sensors/sensor.h"
#include "sensesp/signalk/signalk_output.h"
#include "sensesp/system/lambda_consumer.h"
#include "sensesp_app_builder.h"

using namespace sensesp;

reactesp::ReactESP app;

// The setup function performs one-time application initialization.
void setup() {
#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif

  // Construct the global SensESPApp() object
  SensESPAppBuilder builder;
  sensesp_app = (&builder)
                    // Set a custom hostname for the app.
                    ->set_hostname("sensESP Alarm interface")
                    // Optionally, hard-code the WiFi and Signal K server
                    // settings. This is normally not needed.
                    ->set_wifi("fbi", "younghomewifi")
                    ->set_sk_server("192.168.1.69", 80)
                    ->get_app();


// *************************

  // Input 1  Read GPIO 4 every second

const uint8_t kDigitalInput1Pin = 4;
  const unsigned int kDigitalInput1Interval = 1000;

    pinMode(kDigitalInput1Pin, INPUT_PULLDOWN);
  
  auto* digital_input1 = new RepeatSensor<bool>(
      kDigitalInput1Interval,
      [kDigitalInput1Pin]() { return digitalRead(kDigitalInput1Pin); });


// ***********************

// Input 2  Read GPIO 16 every second

  const uint8_t kDigitalInput2Pin = 16;
  const unsigned int kDigitalInput2Interval = 1000;

  pinMode(kDigitalInput2Pin, INPUT_PULLDOWN);
  
  auto* digital_input2 = new RepeatSensor<bool>(
      kDigitalInput2Interval,
      [kDigitalInput2Pin]() { return digitalRead(kDigitalInput2Pin); });

// ***************

 // Connect digital input 1 to Signal K output.
  digital_input1->connect_to(new SKOutputFloat(
      "AlarmInterface.input1.state",          // Signal K path
      "/AlarmInterface/input1/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "alarm input 1 state")  // Value description
      ));

// ************************

  // Connect digital input 2 to Signal K output.
  digital_input2->connect_to(new SKOutputFloat(
      "AlarmInterface.input2.state",          // Signal K path
      "/AlarmInterface/input2/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "alarm input 2 state")  // Value description
      ));

// ************************** 


  // Start networking, SK server connections and other SensESP internals
  sensesp_app->start();
}

void loop() { app.tick(); }