//==- WeatherTargetTransformInfo.cpp - Weather specific TTI pass -*- C++ -*-==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
/// \file
/// This file implements a TargetTransformInfo analysis pass specific to the
/// H2BLB target machine. It uses the target's detailed information to provide
/// more precise answers to certain TTI queries, while letting the target
/// independent and default TTI implementations handle the rest.
///
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_WEATHER_WEATHERTARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_WEATHER_WEATHERTARGETTRANSFORMINFO_H

#include "WeatherISelLowering.h"
#include "WeatherSubtarget.h"
#include "WeatherTargetMachine.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/Support/InstructionCost.h"

namespace llvm {

class WeatherTTIImpl : public BasicTTIImplBase<WeatherTTIImpl> {
  using BaseT = BasicTTIImplBase<WeatherTTIImpl>;
  using TTI = TargetTransformInfo;

  friend BaseT;

  // Supply the minimum required APIs.
  const WeatherSubtarget &ST;
  const WeatherTargetLowering &TLI;

  const WeatherSubtarget *getST() const { return &ST; }
  const WeatherTargetLowering *getTLI() const { return &TLI; }

public:
    explicit WeatherTTIImpl(const WeatherTargetMachine *TM, const Function &F)
        : BaseT(TM, F.getDataLayout()), ST(*TM->getSubtargetImpl(F)),
          TLI(*ST.getTargetLowering()) {}

    unsigned getLoadVectorFactor(unsigned VF, unsigned LoadSize,
                                 unsigned ChainSizeInBytes, VectorType *VecTy) const;

    InstructionCost getIntrinsicInstrCost(const IntrinsicCostAttributes &ICA,
                                        TTI::TargetCostKind CostKind) const;
};
}

#endif // LLVM_LIB_TARGET_WEATHER_WEATHERTARGETTRANSFORMINFO_H