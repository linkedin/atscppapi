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
 * @file ClientRequest.cc
 * @author Brian Geffon
 * @author Manjesh Nilange
 */

#include "atscppapi/ClientRequest.h"
#include <cstdlib>
#include <ts/ts.h>
#include "atscppapi/noncopyable.h"
#include "InitializableValue.h"
#include "logging_internal.h"

using namespace atscppapi;

/**
 * @private
 */
struct atscppapi::ClientRequestState: noncopyable {
  TSHttpTxn txn_;
  TSMBuffer pristine_hdr_buf_;
  TSMLoc pristine_url_loc_;
  Url pristine_url_;
  ClientRequestState(TSHttpTxn txn) : txn_(txn), pristine_hdr_buf_(NULL), pristine_url_loc_(NULL) { }
};

atscppapi::ClientRequest::ClientRequest(void *ats_txn_handle, void *hdr_buf, void *hdr_loc) :
    Request(hdr_buf, hdr_loc) {
  state_ = new ClientRequestState(static_cast<TSHttpTxn>(ats_txn_handle));
}

atscppapi::ClientRequest::~ClientRequest() {
  if (state_->pristine_url_loc_ && state_->pristine_hdr_buf_) {
    TSMLoc null_parent_loc = NULL;
    LOG_DEBUG("Releasing pristine url loc for transaction %p; hdr_buf %p, url_loc %p", state_->txn_,
              state_->pristine_hdr_buf_, state_->pristine_url_loc_);
    TSHandleMLocRelease(state_->pristine_hdr_buf_, null_parent_loc, state_->pristine_url_loc_);
  }

  delete state_;
}

const Url &atscppapi::ClientRequest::getPristineUrl() const {
  if (!state_->pristine_url_loc_) {
    TSHttpTxnPristineUrlGet(state_->txn_, &state_->pristine_hdr_buf_, &state_->pristine_url_loc_);

    if ((state_->pristine_hdr_buf_ != NULL) && (state_->pristine_url_loc_ != NULL)) {
      state_->pristine_url_.init(state_->pristine_hdr_buf_, state_->pristine_url_loc_);
      LOG_DEBUG("Pristine URL initialized");
    } else {
      LOG_ERROR("Failed to get pristine URL for transaction %p; hdr_buf %p, url_loc %p", state_->txn_,
                state_->pristine_hdr_buf_, state_->pristine_url_loc_);
    }
  } else {
    LOG_DEBUG("Pristine URL already initialized");
  }

  return state_->pristine_url_;
}
