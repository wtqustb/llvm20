//===-- MCTargetDesc/WeatherMCAsmInfo.cpp - Assembly Info ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
/// \file
//===----------------------------------------------------------------------===//

#include "WeatherMCAsmInfo.h"

using namespace llvm;

WeatherMCAsmInfoELF::WeatherMCAsmInfoELF(const Triple &TT,
                                     const MCTargetOptions &Options) {}

WeatherMCAsmInfoDarwin::WeatherMCAsmInfoDarwin(const Triple &TT,
                                           const MCTargetOptions &Options) {}