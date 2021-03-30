/*
   Copyright 2020 Scott Bezek and the splitflap contributors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>

#include "config.h"

#ifdef NEOPIXEL_TURN_OFF
#include <Adafruit_NeoPixel.h>
#include <math.h>
#endif

#include "display_task.h"
#include "splitflap_task.h"

SplitflapTask splitflapTask(1);
DisplayTask displayTask(splitflapTask, 0);

#ifdef MQTT
#include "mqtt_task.h"
MQTTTask mqttTask(splitflapTask, 0);
#endif

#ifdef NEOPIXEL_TURN_OFF
int recv_buffer[NUM_MODULES];
int _NUM_MODULES = ceil(NUM_MODULES/4.0) * 4;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(_NUM_MODULES, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
#endif

void setup() {
  Serial.begin(MONITOR_SPEED);

  #ifdef NEOPIXEL_TURN_OFF
  strip.begin();
  strip.clear();
  strip.show();
  #endif

  splitflapTask.begin();

  #ifdef MQTT
  mqttTask.begin();
  #endif
  displayTask.begin();

  // Delete the default Arduino loopTask to free up Core 1
  vTaskDelete(NULL);
}


void loop() {
  assert(false);
}
