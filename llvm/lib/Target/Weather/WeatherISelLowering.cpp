//===-- WeatherISelLowering.cpp - Weather DAG Lowering Implementation -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the interfaces that Weather uses to lower LLVM code
// into a selection DAG.
//
//===----------------------------------------------------------------------===//

#include "WeatherISelLowering.h"
#include "WeatherSubtarget.h"
#include "WeatherTargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "weather-lowering"

WeatherTargetLowering::WeatherTargetLowering(const TargetMachine &TM, const TargetSubtargetInfo &STI)
    : TargetLowering(TM, STI) {}