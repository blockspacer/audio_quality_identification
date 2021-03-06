// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/test/thread_test_helper.h"

namespace base {

ThreadTestHelper::ThreadTestHelper(MessageLoopProxy* target_thread)
    : test_result_(false),
      target_thread_(target_thread),
      done_event_(false, false) {
}

bool ThreadTestHelper::Run() {
  if (!target_thread_->PostTask(FROM_HERE, NewRunnableMethod(
          this, &ThreadTestHelper::RunInThread))) {
    return false;
  }
  done_event_.Wait();
  return test_result_;
}

void ThreadTestHelper::RunTest() { set_test_result(true); }

ThreadTestHelper::~ThreadTestHelper() {}

void ThreadTestHelper::RunInThread() {
  RunTest();
  done_event_.Signal();
}

}  // namespace base
