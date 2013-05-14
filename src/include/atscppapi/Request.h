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
 * @file Request.h
 * @author Brian Geffon
 * @author Manjesh Nilange
 */

#pragma once
#ifndef ATSCPPAPI_REQUEST_H_
#define ATSCPPAPI_REQUEST_H_

#include <atscppapi/Headers.h>
#include <atscppapi/HttpVersion.h>
#include <atscppapi/HttpMethod.h>
#include <atscppapi/Url.h>
#include <atscppapi/noncopyable.h>

namespace atscppapi {

class Transaction;
struct RequestState;

/**
 * @brief Encapsulates a request.
 */
class Request: noncopyable {
public:
  Request();

  /**
   * Constructed with an initial URL.
   */
  Request(const std::string &url, HttpMethod method = HTTP_METHOD_GET, HttpVersion version = HTTP_VERSION_1_1); 

  /** @return HTTP method of the request */
  HttpMethod getMethod() const;

  /** @return URL of the request */
  Url &getUrl();

  /** @return HTTP version of the request */
  HttpVersion getVersion() const;

  /** @return Headers of the request */
  Headers &getHeaders() const;

  ~Request();
private:
  Request(void *hdr_buf, void *hdr_loc);
  RequestState *state_;
  void init(void *hdr_buf, void *hdr_loc);
  friend class Transaction;
  friend class ClientRequest;
};

}

#endif
