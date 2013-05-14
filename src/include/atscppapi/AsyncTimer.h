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

/**
 * @file AsyncTimer.h
 * @author Brian Geffon
 * @author Manjesh Nilange
 */

#pragma once
#ifndef ATSCPPAPI_ASYNCTIMER_H_
#define ATSCPPAPI_ASYNCTIMER_H_

#include <string>
#include <atscppapi/shared_ptr.h>
#include <atscppapi/Async.h>
#include <atscppapi/Request.h>
#include <atscppapi/Response.h>

namespace atscppapi {

// forward declarations
class AsyncTimerState;

/**
 * @brief This class provides an implementation of AsyncProvider that
 * acts as a timer. It sends events at the set frequency. Calling the
 * destructor will stop the events.
 *
 * See example async_timer for sample usage.
 */
class AsyncTimer : public AsyncProvider {
public:
  /**
   * Constructor.
   * 
   * @param period_in_ms The receiver will receive an event every this many milliseconds.
   * @param initial_period_in_ms The first event will arrive after this many milliseconds. Subsequent
   *                             events will have "regular" cadence. This is useful if the timer is
   *                             set for a long period of time (1hr etc.), but an initial event is
   *                             required. Value of 0 (default) indicates no initial event is desired.
   */
  AsyncTimer(int period_in_ms, int initial_period_in_ms = 0);

  ~AsyncTimer();

  /**
   * Starts the timer.
   */  
  void run(shared_ptr<AsyncDispatchControllerBase> dispatch_controller);

private:
  AsyncTimerState *state_;
};

} /* atscppapi */

#endif /* ATSCPPAPI_ASYNCTIMER_H_ */
