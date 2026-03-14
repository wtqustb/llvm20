//===-- WeatherMCTargetDesc.h - Weather Target Descriptions ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
/// Provides Weather specific target descriptions.
//
//===----------------------------------------------------------------------===//
//

#ifndef LLVM_LIB_TARGET_WEATHER_MCTARGETDESC_WEATHERMCTARGETDESC_H
#define LLVM_LIB_TARGET_WEATHER_MCTARGETDESC_WEATHERMCTARGETDESC_H

#include "llvm/MC/MCInstrInfo.h"
#include <cstdint> // For int16_t and so on used in the .inc files.
namespace llvm {
class MCContext;
class MCCodeEmitter;
MCCodeEmitter *createWeatherMCCodeEmitter(const MCInstrInfo &MCII,
                                        MCContext &Ctx);
} // end namespace llvm.

#define GET_REGINFO_ENUM
#include "WeatherGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "WeatherGenSubtargetInfo.inc"

#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "WeatherGenInstrInfo.inc"

#endif