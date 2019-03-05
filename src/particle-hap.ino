/*
 * Project particle-hap
 * Description:
 * Author:
 * Date:
 */

#include "homekit/HKServer.h"

#include "LightBulbAccessory.h"
#include "WindowsShutterAccessory.h"
#include "LightSensorAccessory.h"
#include "MotionSensorAccessory.h"
#include "HomekitBridgeAccessory.h"

HKServer *hkServer = NULL;

//HAPAccessoryDescriptor *acc = new WindowsShutterAccessory();
//HAPAccessoryDescriptor *acc = new LightBulbAccessory();
//HAPAccessoryDescriptor *acc = new LightSensorAccessory();
HomekitBridgeAccessory *acc = new HomekitBridgeAccessory();
void progress(Progress_t progress) {
    Serial.printf("PROGRESS: %d\n",progress);
}

STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

// setup() runs once, when the device is first turned on.
void setup() {

	randomSeed(Time.now());//we need to somehow init random seed, so device identity will be unique
  Serial.begin();

  //HKPersistor().resetAll();

  //BEGIN MYHOME
  acc->descriptors.push_back(new WindowsShutterAccessory(14678913,14678916));
  acc->descriptors.push_back(new WindowsShutterAccessory(4102033,4102036));
  acc->descriptors.push_back(new WindowsShutterAccessory(4102034,4102040));
  acc->descriptors.push_back(new LightBulbAccessory());
  acc->descriptors.push_back(new MotionSensorAccessory());
  //END MYHOME

  acc->initAccessorySet();

  hkServer = new HKServer(acc->getDeviceType(),"Kit","523-12-643",progress);

  hkServer->setup();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  hkServer->handle();
  acc->handle();
}
