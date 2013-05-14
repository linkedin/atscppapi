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
 * @file Response.h
 * @author Brian Geffon
 * @author Manjesh Nilange
 */

#pragma once
#ifndef ATSCPPAPI_RESPONSE_H_
#define ATSCPPAPI_RESPONSE_H_

#include <atscppapi/Headers.h>
#include <atscppapi/HttpVersion.h>
#include <atscppapi/HttpStatus.h>

namespace atscppapi {

// forward declarations
struct ResponseState;
namespace utils { class internal; }

/**
 * @brief Encapsulates a response.
 */
class Response: noncopyable {
public:
  Response();

  /** @return HTTP version of the response */
  HttpVersion getVersion() const;

  /** @return Status code of the response */
  HttpStatus getStatusCode() const;

  /** @param New status code to set */
  void setStatusCode(HttpStatus);

  /** @return Reason phrase of the response */
  const std::string &getReasonPhrase() const;

  /** @param New reason phrase to set */
  void setReasonPhrase(const std::string &);

  /** @return Headers of the response */
  Headers &getHeaders() const;

  ~Response();
private:
  ResponseState *state_;
  void init(void *hdr_buf, void *hdr_loc);
  friend class Transaction;
  friend class utils::internal;
};

}

#endif
