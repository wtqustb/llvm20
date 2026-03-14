//===-- WeatherMCTargetDesc.cpp - Weather Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Weather specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "WeatherMCTargetDesc.h"
#include "WeatherInstPrinter.h"
#include "WeatherMCAsmInfo.h"
#include "TargetInfo/WeatherTargetInfo.h" // For getTheWeatherTarget.
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"  // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/Support/ErrorHandling.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

#define GET_SUBTARGETINFO_ENUM
#include "WeatherGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "WeatherGenRegisterInfo.inc"

#define GET_INSTRINFO_MC_DESC
#define GET_INSTRINFO_MC_HELPER
#include "WeatherGenInstrInfo.inc"


static MCRegisterInfo *createWeatherMCRegisterInfo(const Triple &Triple) {
    MCRegisterInfo *X = new MCRegisterInfo();
    InitWeatherMCRegisterInfo(X, Weather::R7);
    return X;
}

static MCInstrInfo *createWeatherMCInstrInfo() {
    MCInstrInfo *X = new MCInstrInfo();
    InitWeatherMCInstrInfo(X);
    return X;
}

static llvm::MCSubtargetInfo *
createWeatherMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createWeatherMCSubtargetInfo(TT, CPU, FS);
}

static MCAsmInfo *createWeatherMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TheTriple, const MCTargetOptions &Options) {
    MCAsmInfo *MAI;
    if (TheTriple.isOSBinFormatMachO())
        MAI = new WeatherMCAsmInfoDarwin(TheTriple, Options);
    else if (TheTriple.isOSBinFormatELF())
        MAI = new WeatherMCAsmInfoELF(TheTriple, Options);
    else
        llvm_unreachable("Unsupported binary format");
    return MAI;
}

static MCInstPrinter *createWeatherMCInstPrinter(const Triple &T, unsigned SyntaxVariant,
                                           const MCAsmInfo &MAI, const MCInstrInfo &MII,
                                           const MCRegisterInfo &MRI) {
    if (SyntaxVariant == 0)
        return new WeatherInstPrinter(MAI, MII, MRI);
    return nullptr;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeWeatherTargetMC() {
  Target &TheTarget = getTheWeatherTarget();

  // Register the MC asm info.
  RegisterMCAsmInfoFn X(TheTarget, createWeatherMCAsmInfo);

  // Register the MCRegisterInfo.
  TargetRegistry::RegisterMCRegInfo(TheTarget, createWeatherMCRegisterInfo);
  // Register the MCInstrInfo.
  TargetRegistry::RegisterMCInstrInfo(TheTarget, createWeatherMCInstrInfo);
  // Register the MCSubtargetInfo.
  TargetRegistry::RegisterMCSubtargetInfo(getTheWeatherTarget(),
                                          createWeatherMCSubtargetInfo);
  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(TheTarget, createWeatherMCInstPrinter);
  // Register the MC code emitter.
  TargetRegistry::RegisterMCCodeEmitter(getTheWeatherTarget(),
                                        createWeatherMCCodeEmitter);                                  
}