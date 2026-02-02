//===-- WeatherTargetMachine.cpp - Define TargetMachine for Weather -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Weather target spec.
//
//===----------------------------------------------------------------------===//

#include "WeatherTargetMachine.h"
#include "TargetInfo/WeatherTargetInfo.h" // For getTheWeatherTarget.
#include "llvm/MC/TargetRegistry.h"     // For RegisterTargetMachine.
#include "llvm/Support/Compiler.h"      // For LLVM_EXTERNAL_VISIBILITY.
#include <memory>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeWeatherTarget() {
    // Register the target so that external tools can instantiate it.
    RegisterTargetMachine<WeatherTargetMachine> X(getTheWeatherTarget());
}

static const char *WeatherDataLayoutStr = "e-p:16:16:16-n16:32-i32:32:32-i16:16:16-i1:8:8-f32:32:32-v32:32:32";

WeatherTargetMachine::WeatherTargetMachine(const Target &T, const Triple &TT,
                                         StringRef CPU, StringRef FS,
                                         const TargetOptions &Options,
                                         std::optional<Reloc::Model> RM,
                                         std::optional<CodeModel::Model> CM,
                                         CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, WeatherDataLayoutStr, TT, CPU, FS, Options,
                               RM ? *RM : Reloc::Model::Static,
                               CM ? *CM : CodeModel::Small, OL) {}

WeatherTargetMachine::~WeatherTargetMachine() = default;

const WeatherSubtarget *
WeatherTargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");
  
  StringRef CPU = CPUAttr.isValid() ? CPUAttr.getValueAsString() : TargetCPU;
  StringRef FS = FSAttr.isValid() ? FSAttr.getValueAsString() : TargetFS;
    if (!SubtargetSingleton) {
        return nullptr;
    }
  return SubtargetSingleton.get();
}