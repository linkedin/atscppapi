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

#include <iostream>
#include <atscppapi/GlobalPlugin.h>
#include <atscppapi/TransactionPlugin.h>
#include <atscppapi/TransformationPlugin.h>
#include <atscppapi/PluginInit.h>

using namespace atscppapi;
using std::cerr;
using std::endl;
using std::string;

class PostBufferTransformationPlugin : public TransformationPlugin {
public:
  PostBufferTransformationPlugin(Transaction &transaction)
    : TransformationPlugin(transaction, REQUEST_TRANSFORMATION), transaction_(transaction) {
    buffer_.reserve(1024); // not required, this is an optimization to start the buffer at a slightly higher value.
  }

  void consume(const string &data) {
    buffer_.append(data);
  }

  void handleInputComplete() {
    produce(buffer_);
    setOutputComplete();
  }

  virtual ~PostBufferTransformationPlugin() { }

private:
  Transaction &transaction_;
  string buffer_;
};

class GlobalHookPlugin : public GlobalPlugin {
public:
  GlobalHookPlugin() {
    registerHook(HOOK_READ_REQUEST_HEADERS_POST_REMAP);
  }

  virtual void handleReadRequestHeadersPostRemap(Transaction &transaction) {
    cerr << "Read Request Headers Post Remap" << endl;
    cerr << "Path: " << transaction.getClientRequest().getUrl().getPath() << endl;
    cerr << "Method: " << HTTP_METHOD_STRINGS[transaction.getClientRequest().getMethod()] << endl;
    if (transaction.getClientRequest().getMethod() == HTTP_METHOD_POST) {
      transaction.addPlugin(new PostBufferTransformationPlugin(transaction));
    }

    transaction.resume();
  }
};

void TSPluginInit(int argc, const char *argv[]) {
  GlobalPlugin *instance = new GlobalHookPlugin();
}

