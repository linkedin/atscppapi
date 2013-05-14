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
 * @file HttpVersion.h
 * @author Brian Geffon
 * @author Manjesh Nilange
 * @brief Contains an enumeration and printable strings for Http Versions.
 */

#pragma once
#ifndef ATSCPPAPI_HTTP_VERSION_H_
#define ATSCPPAPI_HTTP_VERSION_H_

#include <string>

namespace atscppapi {

/**
 * An enumeration of all available Http Versions.
 */
enum HttpVersion {
  HTTP_VERSION_UNKNOWN = 0,
  HTTP_VERSION_0_9,
  HTTP_VERSION_1_0,
  HTTP_VERSION_1_1,
};

/**
 * An array of printable strings representing of the HttpVersion
 * \code
 * cout << HTTP_VERSION_STRINGS[HTTP_VERSION_1_1] << endl;
 * \endcode
 */
extern const std::string HTTP_VERSION_STRINGS[];

}

#endif
