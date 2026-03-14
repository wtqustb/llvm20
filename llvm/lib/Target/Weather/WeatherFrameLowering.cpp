//===-- WeatherFrameLowering.cpp - Weather Frame Information ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Weather implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "WeatherFrameLowering.h"
#include "WeatherInstrInfo.h"
#include "WeatherSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

bool WeatherFrameLowering::hasFPImpl(const MachineFunction &MF) const {
  return false;
}

void WeatherFrameLowering::emitPrologue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {}

void WeatherFrameLowering::emitEpilogue(MachineFunction &MF,
                                      MachineBasicBlock &MBB) const {}