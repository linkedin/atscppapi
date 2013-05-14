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
 * @file noncopyable.h
 * @author Brian Geffon
 * @author Manjesh Nilange
 * @brief A base class used to prevent dervied classes from being copyable, this effectively
 * eliminates the copy constructor and assignment operator.
 */

#pragma once
#ifndef ATSCPPAPI_NONCOPYABLE_H_
#define ATSCPPAPI_NONCOPYABLE_H_

namespace atscppapi {

/**
 * @brief noncopyable is a base class that will prevent derived classes from being copied.
 *
 * @private Prevent Doxygen from showing this class in the inheritance diagrams.
 *
 * To use noncopyable you only need to inherit from this class and you're derived class
 * will become uncopyable
 *
 * \code
 * class myClass : uncopyable {
 * public:
 *  int test_;
 * }
 *
 * // The following will fail:
 * myClass a;
 * myClass b(a); // fails
 * myClass c = a; // fails
 * \endcode
 */
class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:
  noncopyable(const noncopyable&);
  const noncopyable& operator=(const noncopyable&);
};

} /* atscppapi */


#endif /* ATSCPPAPI_NONCOPYABLE_H_ */
