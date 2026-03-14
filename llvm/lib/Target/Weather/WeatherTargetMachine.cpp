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
#include "Weather.h"
#include "WeatherSubtarget.h"
#include "WeatherTargetTransformInfo.h"
#include "TargetInfo/WeatherTargetInfo.h" // For getTheWeatherTarget.
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"     // For RegisterTargetMachine.
#include "llvm/PassRegistry.h"
#include "llvm/Support/Compiler.h"      // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/CodeGen.h"       // For CodeGenOptLevel.
#include <memory>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeWeatherTarget() {
    // Register the target so that external tools can instantiate it.
    RegisterTargetMachine<WeatherTargetMachine> X(getTheWeatherTarget());

    PassRegistry &PR = *PassRegistry::getPassRegistry();

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
                               CM ? *CM : CodeModel::Small, OL) {
  initAsmInfo();
}

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

TargetTransformInfo
WeatherTargetMachine::getTargetTransformInfo(const Function &F) const {
  return TargetTransformInfo(std::make_unique<WeatherTTIImpl>(this, F));
}

TargetPassConfig *WeatherTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new WeatherPassConfig(*this, PM);
}

WeatherPassConfig::WeatherPassConfig(TargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

bool WeatherPassConfig::addInstSelector() {
  // TODO: We need to hook up the DAG Selector Here.
  return false; 
}

void WeatherPassConfig::addIRPasses() {
  // Add the regular IR Passes before putting our passes
  TargetPassConfig::addIRPasses();
  if (getOptLevel() != CodeGenOptLevel::None) {
    return; // here should add some optimization passes, but for now we just return.
  }
}
