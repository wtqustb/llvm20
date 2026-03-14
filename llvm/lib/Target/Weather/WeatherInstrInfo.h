//===-- WeatherInstrInfo.h - Weather Instruction Information --------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Weather implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Weather_WeatherINSTRINFO_H
#define LLVM_LIB_TARGET_Weather_WeatherINSTRINFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "WeatherGenInstrInfo.inc"

namespace llvm {

class WeatherInstrInfo : public WeatherGenInstrInfo {
public:
  WeatherInstrInfo();
};
} // namespace llvm

#endif