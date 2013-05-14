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
 * @file GzipInflateTransformation.h
 * @author Brian Geffon
 * @author Manjesh Nilange
 * @brief Gzip Inflate Transformation can be used to decompress gzipped content.
 */

#pragma once
#ifndef ATSCPPAPI_GZIPINFLATETRANSFORMATION_H_
#define ATSCPPAPI_GZIPINFLATETRANSFORMATION_H_

#include <string>
#include "atscppapi/TransformationPlugin.h"

namespace atscppapi {

namespace transformations {

/**
 * Internal state for Inflate Transformations
 * @private
 */
class GzipInflateTransformationState;

/**
 * @brief A TransformationPlugin to easily add gzip inflate to your TransformationPlugin chain.
 *
 * The GzipInflateTransformation is a helper transformation that can be used
 * to easily decompress gzipped content. For a full example of GzipInflateTransformation
 * and GzipDeflateTransformation see examples/gzip_transformation/.
 *
 * @note GzipDeflateTransformation DOES NOT set or check Content-Encoding headers, it is the
 * users responsibility to set any applicable headers and check that the content is acctually
 * gzipped by checking the Content-Encoding header before creating a GzipInflateTransformation,
 * see examples/gzip_transformation/ for a full example.
 *
 * @see GzipDeflateTransformation
 */
class GzipInflateTransformation : public TransformationPlugin {
public:
  /**
   * A full example of how to use GzipInflateTransformation and GzipDeflateTransformation is available
   * in examples/gzip_tranformation/
   *
   * @param transaction As with any TransformationPlugin you must pass in the transaction
   * @param type because the GzipInflateTransformation can be used with both requests and responses
   *  you must specify the Type.
   *
   * @see TransformationPlugin::Type
   */
  GzipInflateTransformation(Transaction &transaction, TransformationPlugin::Type type);

  /**
   * Any TransformationPlugin must implement consume(), this method will take content
   * from the transformation chain and gzip decompress it.
   *
   * @param data the input data to decompress
   */
  void consume(const std::string &);

  /**
   * Any TransformationPlugin must implement handleInputComplete(), this method will
   * finalize the gzip decompression.
   */
  void handleInputComplete();

  virtual ~GzipInflateTransformation();
private:
  GzipInflateTransformationState *state_; /** Internal state for Gzip Deflate Transformations */
};

} /* transformations */

} /* atscppapi */

#endif /* ATSCPPAPI_GZIPINFLATETRANSFORMATION_H_ */
