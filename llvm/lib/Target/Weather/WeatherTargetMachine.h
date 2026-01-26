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


#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include <optional>

namespace llvm {

class WeatherTargetMachine : public CodeGenTargetMachineImpl {
public:
  WeatherTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                       StringRef FS, const TargetOptions &Options,
                       std::optional<Reloc::Model> RM,
                       std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                       bool JIT);

  ~WeatherTargetMachine() override;
};


} // end namespace llvm

#endif