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
#include <atscppapi/PluginInit.h>
#include <atscppapi/utils.h>

using namespace atscppapi;

using std::cout;
using std::endl;
using std::list;
using std::string;

class ServerResponsePlugin : public GlobalPlugin {
public:
  ServerResponsePlugin() {
    registerHook(HOOK_SEND_REQUEST_HEADERS);
    registerHook(HOOK_READ_RESPONSE_HEADERS);
    registerHook(HOOK_SEND_RESPONSE_HEADERS);
  }

  void handleSendRequestHeaders(Transaction &transaction) {
    // Here we can decide to abort the request to the origin (we can do this earlier too)
    // and just send the user an error page.
    if(transaction.getClientRequest().getUrl().getQuery().find("error=1") != string::npos) {
      // Give this user an error page and don't make a request to an origin.
      cout << "Sending this request an error page" << endl;
      transaction.error("This is the error response, but the response code is 500."
                        "In this example no request was made to the orgin.");
      // HTTP/1.1 500 INKApi Error
    } else {
      transaction.resume();
    }
    cout << "Server request headers are" << endl;
    printHeaders(transaction.getServerRequest().getHeaders());
  }

  void handleReadResponseHeaders(Transaction &transaction) {
    cout << "Hello from handleReadResponseHeaders!" << endl;
    cout << "Server response headers are" << endl;
    Response &server_response = transaction.getServerResponse();
    cout << "Reason phrase is " << server_response.getReasonPhrase() << endl;
    printHeaders(server_response.getHeaders());
    transaction.resume();
  }

  void handleSendResponseHeaders(Transaction &transaction) {
    cout << "Hello from handleSendResponseHeaders!" << endl;
    cout << "Client response headers are" << endl;
    printHeaders(transaction.getClientResponse().getHeaders());

    //
    // If the url contains a query parameter redirect=1 we will send the
    // user to to somewhere else. Obviously this is a silly example
    // since we should technically detect this long before the origin
    // request and prevent the origin request in the first place.
    //

    if(transaction.getClientRequest().getUrl().getQuery().find("redirect=1") != string::npos) {
      cout << "Sending this guy to google." << endl;
      transaction.getClientResponse().getHeaders().set("Location", "http://www.google.com");
      transaction.getClientResponse().setStatusCode(HTTP_STATUS_MOVED_TEMPORARILY);
      transaction.getClientResponse().setReasonPhrase("Come Back Later");
      // HTTP/1.1 302 Come Back Later
    }

    transaction.resume();
  }

private:
  void printHeaders(const Headers &headers) {
    for (Headers::const_iterator header_iter = headers.begin(), header_end = headers.end();
         header_iter != header_end; ++header_iter) {
      const string &name = header_iter->first;
      const list<string> &value_list = header_iter->second;
      cout << "Header. " << name <<  ": " << endl;
      for (list<string>::const_iterator value_iter = value_list.begin(), value_end = value_list.end();
           value_iter != value_end; ++value_iter) {
        cout << "\t" << *value_iter << endl;
      }
    }
    cout << endl;
  }
};

void TSPluginInit(int argc, const char *argv[]) {
  GlobalPlugin *instance = new ServerResponsePlugin();
}
