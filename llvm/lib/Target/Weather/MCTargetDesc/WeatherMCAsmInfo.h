//===-- MCTargetDesc/WeatherMCAsmInfo.h - Weather MCAsm Interface ---*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
/// Declaration of the Weather MCAsmInfos.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Weather_MCTARGETDESC_WeatherMCASMINFO_H
#define LLVM_LIB_TARGET_Weather_MCTARGETDESC_WeatherMCASMINFO_H

#include "llvm/MC/MCAsmInfoDarwin.h"
#include "llvm/MC/MCAsmInfoELF.h"
namespace llvm {

class Triple;

class WeatherMCAsmInfoELF : public MCAsmInfoELF {
public:
  explicit WeatherMCAsmInfoELF(const Triple &TT, const MCTargetOptions &Options);
};

class WeatherMCAsmInfoDarwin : public MCAsmInfoDarwin {
public:
  explicit WeatherMCAsmInfoDarwin(const Triple &TT,
                                const MCTargetOptions &Options);
};
} // namespace llvm
#endif