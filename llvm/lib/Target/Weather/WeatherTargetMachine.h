//=-- WeatherTargetMachine.h - Define TargetMachine for Weather -------*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Weather specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WEATHER_WEATHERTARGETMACHINE_H
#define LLVM_LIB_TARGET_WEATHER_WEATHERTARGETMACHINE_H

#include "WeatherSubtarget.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>
#include <memory>

namespace llvm {

class WeatherTargetMachine : public CodeGenTargetMachineImpl {
  mutable std::unique_ptr<WeatherSubtarget> SubtargetSingleton;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
public:
  WeatherTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);

  ~WeatherTargetMachine() override;

  const WeatherSubtarget *getSubtargetImpl(const Function &F) const override;
  TargetTransformInfo getTargetTransformInfo(const Function &F) const override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
   }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
};

class WeatherPassConfig : public TargetPassConfig {
public:
  WeatherPassConfig(TargetMachine &TM, PassManagerBase &PM);

};

} // end namespace llvm

#endif