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
#include <atscppapi/PluginInit.h>

using namespace atscppapi;

using std::cout;
using std::endl;
using std::list;
using std::string;


class ClientRedirectTransactionPlugin : public atscppapi::TransactionPlugin {
public:
  ClientRedirectTransactionPlugin(Transaction &transaction, const string &location)
     : TransactionPlugin(transaction), location_(location) {

    //
    // We will set this transaction to jump to error state and then we will setup
    // the redirect on SEND_RESPONSE_HEADERS
    //
    TransactionPlugin::registerHook(HOOK_SEND_RESPONSE_HEADERS);
    transaction.error();
  }

  void handleSendResponseHeaders(Transaction &transaction) {
    transaction.getClientResponse().setStatusCode(HTTP_STATUS_MOVED_TEMPORARILY);
    transaction.getClientResponse().setReasonPhrase("Moved Temporarily");
    transaction.getClientResponse().getHeaders().set("Location", location_);
    transaction.resume();
  }

  virtual ~ClientRedirectTransactionPlugin() { }
private:
  string location_;
};


class ClientRedirectGlobalPlugin : public GlobalPlugin {
public:
  ClientRedirectGlobalPlugin() {
    registerHook(HOOK_SEND_REQUEST_HEADERS);
  }

  void handleSendRequestHeaders(Transaction &transaction) {
    if(transaction.getClientRequest().getUrl().getQuery().find("redirect=1") != string::npos) {
      transaction.addPlugin(new ClientRedirectTransactionPlugin(transaction, "http://www.linkedin.com/"));
      return;
    }
    transaction.resume();
  }

};

void TSPluginInit(int argc, const char *argv[]) {
  GlobalPlugin *instance = new ClientRedirectGlobalPlugin();
}
