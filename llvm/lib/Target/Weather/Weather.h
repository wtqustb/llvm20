//===-- Weather.h - Weather specific passes ---------------------------*- C++ -*-=//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file hold the declarations for the Weather-specific passes for
// both the legacy and new pass managers.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WEATHER_WEATHER_H
#define LLVM_LIB_TARGET_WEATHER_WEATHER_H
#include "llvm/IR/PassManager.h"
#include "llvm/PassRegistry.h"


namespace llvm {

class Function;
class Pass;
class PassRegistry;

class WeatherSimpleConstantPropagationNewPass : public llvm::PassInfoMixin<WeatherSimpleConstantPropagationNewPass> {
public:
    llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &AM);
};


} // end namespace llvm

#endif