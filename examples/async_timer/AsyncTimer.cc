/*
 * Copyright (c) 2013 LinkedIn Corp. All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of the license at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the
 * License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 */

#include <atscppapi/Logger.h>
#include <atscppapi/PluginInit.h>
#include <atscppapi/AsyncTimer.h>
#include <atscppapi/GlobalPlugin.h>

using namespace atscppapi;
using std::string;

#define TAG "async_timer"

class TimerEventReceiver : public AsyncReceiver<AsyncTimer> {
public:
  TimerEventReceiver(AsyncTimer::Type type, int period_in_ms, int initial_period_in_ms = 0, int max_instances = 0)
    : max_instances_(max_instances), instance_count_(0), type_(type) {
    timer_ = new AsyncTimer(type, period_in_ms, initial_period_in_ms);
    Async::execute<AsyncTimer>(this, timer_, shared_ptr<Mutex>()); // letting the system create the mutex
  }

  void handleAsyncComplete(AsyncTimer &timer) {
    TS_DEBUG(TAG, "Got timer event in object %p!", this);
    if ((type_ == AsyncTimer::TYPE_ONE_OFF) || (max_instances_ && (++instance_count_ == max_instances_))) {
      TS_DEBUG(TAG, "Stopping timer in object %p!", this);
      delete this;
    }
  }

  ~TimerEventReceiver() {
    delete timer_;
  }

private:
  int max_instances_;
  int instance_count_;
  AsyncTimer::Type type_;
  AsyncTimer *timer_;
};

void TSPluginInit(int argc, const char *argv[]) {
  int period_in_ms = 1000;
  TimerEventReceiver *timer1 = new TimerEventReceiver(AsyncTimer::TYPE_PERIODIC, period_in_ms);
  TS_DEBUG(TAG, "Created periodic timer %p with initial period 0, regular period %d and max instances 0", timer1,
           period_in_ms);
  int initial_period_in_ms = 100;
  TimerEventReceiver *timer2 = new TimerEventReceiver(AsyncTimer::TYPE_PERIODIC, period_in_ms,
                                                      initial_period_in_ms);
  TS_DEBUG(TAG, "Created periodic timer %p with initial period %d, regular period %d and max instances 0", timer2,
           initial_period_in_ms, period_in_ms);
  initial_period_in_ms = 200;
  int max_instances = 10;
  TimerEventReceiver *timer3 = new TimerEventReceiver(AsyncTimer::TYPE_PERIODIC, period_in_ms, initial_period_in_ms,
                                                      max_instances);
  TS_DEBUG(TAG, "Created periodic timer %p with initial period %d, regular period %d and max instances %d", timer3,
           initial_period_in_ms, period_in_ms, max_instances);

  TimerEventReceiver *timer4 = new TimerEventReceiver(AsyncTimer::TYPE_ONE_OFF, period_in_ms);
  TS_DEBUG(TAG, "Created one-off timer %p with period %d", timer4, period_in_ms);
}
