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
 * @file logging_internal.h
 *
 * @author Brian Geffon
 * @author Manjesh Nilange
 *
 * @brief logging used inside the atscppapi library.
 */

#pragma once
#ifndef ATSCPPAPI_LOGGING_INTERNAL_H_
#define ATSCPPAPI_LOGGING_INTERNAL_H_

#include "atscppapi/Logger.h"

// Because we have the helper in Logger.h with the same name.
#ifdef LOG_DEBUG
#undef LOG_DEBUG
#endif

#ifdef LOG_ERROR
#undef LOG_ERROR
#endif

#define LOG_DEBUG(fmt, ...) TS_DEBUG("atscppapi", fmt, ## __VA_ARGS__)
#define LOG_ERROR(fmt, ...) TS_ERROR("atscppapi", fmt, ## __VA_ARGS__)

#endif /* ATSCPPAPI_LOGGING_INTERNAL_H_ */
