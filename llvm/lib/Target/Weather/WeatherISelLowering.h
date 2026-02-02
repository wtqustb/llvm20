//===-- WeatherISelLowering.h - Weather DAG Lowering Interface --*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Weather uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WEATHER_WEATHERISELLOWERING_H
#define LLVM_LIB_TARGET_WEATHER_WEATHERISELLOWERING_H

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class WeatherSubtarget;
class WeatherTargetMachine;

class WeatherTargetLowering : public TargetLowering {
public:
    explicit WeatherTargetLowering(const TargetMachine &TM, const TargetSubtargetInfo &STI);

};

} // end namespace llvm

#endif