//===- WeatherSubtarget.cpp - Weather Subtarget Information ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the Weather specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "WeatherSubtarget.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

void WeatherSubtarget::anchor() {}

WeatherSubtarget::WeatherSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                                   const TargetMachine &TM, const TargetSubtargetInfo &STI)
    : TargetSubtargetInfo(TT, CPU, /*TuneCPU=*/"", FS, /*PN=*/{}, /*PF=*/{},
                          /*PD=*/{},
                          /*WPR=*/nullptr,
                          /*WL=*/nullptr,
                          /*RA=*/nullptr, /*IS=*/nullptr,
                          /*OC=*/nullptr, /*FP=*/nullptr),
      TLInfo(TM, STI) {}