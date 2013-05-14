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
 * @file InitializableValue.cc
 * @author Brian Geffon
 * @author Manjesh Nilange
 */

#include "InitializableValue.h"

#ifdef DISABLE_TRANSACTION_DATA_CACHING
bool atscppapi::transaction_data_caching_enabled = false;
#else
bool atscppapi::transaction_data_caching_enabled = true;
#endif
