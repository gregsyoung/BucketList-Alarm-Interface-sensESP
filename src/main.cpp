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

  // Input 1 Lazzarette Bilge  Read GPIO 4 every 2 second

const uint8_t kDigitalInput1Pin = 4;
  const unsigned int kDigitalInput1Interval = 2000;

    pinMode(kDigitalInput1Pin, INPUT_PULLDOWN);
  
  auto* digital_input1 = new RepeatSensor<bool>(
      kDigitalInput1Interval,
      [kDigitalInput1Pin]() { return digitalRead(kDigitalInput1Pin); });


// ***********************

// Input 2 Engine Room Bilge Read GPIO 16 every 2 second

  const uint8_t kDigitalInput2Pin = 16;
  const unsigned int kDigitalInput2Interval = 2000;

  pinMode(kDigitalInput2Pin, INPUT_PULLDOWN);
  
  auto* digital_input2 = new RepeatSensor<bool>(
      kDigitalInput2Interval,
      [kDigitalInput2Pin]() { return digitalRead(kDigitalInput2Pin); });

// ***************

// Input 3 Forward bilge Read GPIO 17 every 2 second

  const uint8_t kDigitalInput3Pin = 17;
  const unsigned int kDigitalInput3Interval = 2000;

    pinMode(kDigitalInput3Pin, INPUT_PULLDOWN);
  
  auto* digital_input3 = new RepeatSensor<bool>(
      kDigitalInput3Interval,
      [kDigitalInput3Pin]() { return digitalRead(kDigitalInput3Pin); });


// ***********************

// Input 4 engine room high water  Read GPIO 18 every 2 second

  const uint8_t kDigitalInput4Pin = 18;
  const unsigned int kDigitalInput4Interval = 2000;

  pinMode(kDigitalInput4Pin, INPUT_PULLDOWN);
  
  auto* digital_input4 = new RepeatSensor<bool>(
      kDigitalInput4Interval,
      [kDigitalInput4Pin]() { return digitalRead(kDigitalInput4Pin); });

// *************** 

 // Connect digital input 1 Lazarette bilge  to Signal K output.
  digital_input1->connect_to(new SKOutputFloat(
      "AlarmInterface.LazzaretteBilge.state",          // Signal K path
      "/AlarmInterface/LazzaretteBilge/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "LazzaretteBilge state")  // Value description
      ));

// ************************

  // Connect digital input 2 engine room bilge  to Signal K output.
  digital_input2->connect_to(new SKOutputFloat(
      "AlarmInterface.EngineRoomBilge.state",          // Signal K path
      "/AlarmInterface/EngineRoomBilge/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "EngineRoomBilge state")  // Value description
      ));

// ************************** 

 // Connect digital input 3 forward bilge  to Signal K output.
  digital_input3->connect_to(new SKOutputFloat(
      "AlarmInterface.ForwardBilge.state",          // Signal K path
      "/AlarmInterface/ForwardBilge/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "ForwardBilge state")  // Value description
      ));

// ************************

  // Connect digital input 4 engine room high water  to Signal K output.
  digital_input4->connect_to(new SKOutputFloat(
      "AlarmInterface.EngineRoomHighWater.state",          // Signal K path
      "/AlarmInterface/EngineRoomHighWater/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "EngineRoomHighWater state")  // Value description
      ));

// ************************** 
// ***************************

  // Input 5 Navigation Lights  Read GPIO 19 every 5 second

const uint8_t kDigitalInput5Pin = 19;
  const unsigned int kDigitalInput5Interval = 5000;

    pinMode(kDigitalInput5Pin, INPUT_PULLDOWN);
  
  auto* digital_input5 = new RepeatSensor<bool>(
      kDigitalInput5Interval,
      [kDigitalInput5Pin]() { return digitalRead(kDigitalInput5Pin); });


// ***********************

// Input 6 Anchor Light  Read GPIO 21 every 5 second

  const uint8_t kDigitalInput6Pin = 21;
  const unsigned int kDigitalInput6Interval = 5000;

  pinMode(kDigitalInput6Pin, INPUT_PULLDOWN);
  
  auto* digital_input6 = new RepeatSensor<bool>(
      kDigitalInput6Interval,
      [kDigitalInput6Pin]() { return digitalRead(kDigitalInput6Pin); });

// ***************

// Input 7  Read GPIO 22 every 5 second

  const uint8_t kDigitalInput7Pin = 22;
  const unsigned int kDigitalInput7Interval = 5000;

    pinMode(kDigitalInput7Pin, INPUT_PULLDOWN);
  
  auto* digital_input7 = new RepeatSensor<bool>(
      kDigitalInput7Interval,
      [kDigitalInput7Pin]() { return digitalRead(kDigitalInput7Pin); });


// ***********************

// Input 8  Read GPIO 23 every 5 second

  const uint8_t kDigitalInput8Pin = 23;
  const unsigned int kDigitalInput8Interval = 5000;

  pinMode(kDigitalInput8Pin, INPUT_PULLDOWN);
  
  auto* digital_input8 = new RepeatSensor<bool>(
      kDigitalInput8Interval,
      [kDigitalInput8Pin]() { return digitalRead(kDigitalInput8Pin); });

// ***************

 // Connect digital input 5 Navigation Lights  to Signal K output.
  digital_input5->connect_to(new SKOutputFloat(
      "AlarmInterface.NavigationLights.state",          // Signal K path
      "/AlarmInterface/NavigationLights/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "NavigationLights state")  // Value description
      ));

// ************************

  // Connect digital input 6 Anchor Light  to Signal K output.
  digital_input6->connect_to(new SKOutputFloat(
      "AlarmInterface.AnchorLight.state",          // Signal K path
      "/AlarmInterface/AnchorLight/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "AnchorLight state")  // Value description
      ));

// ************************** 

 // Connect digital input 7 to Signal K output.
  digital_input7->connect_to(new SKOutputFloat(
      "AlarmInterface.input7.state",          // Signal K path
      "/AlarmInterface/input7/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "alarm input 7 state")  // Value description
      ));

// ************************

  // Connect digital input 8 to Signal K output.
  digital_input8->connect_to(new SKOutputFloat(
      "AlarmInterface.input8.state",          // Signal K path
      "/AlarmInterface/input8/state",         // configuration path
      new SKMetadata("",                       // No units for boolean values
                     "alarm input 8 state")  // Value description
      ));


// ************
// ************

  // Start networking, SK server connections and other SensESP internals
  sensesp_app->start();
}

void loop() { app.tick(); }