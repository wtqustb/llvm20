//===-- WeatherRegisterInfo.cpp - Weather Register Information ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains the Weather implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "WeatherRegisterInfo.h"
#include "WeatherFrameLowering.h"
#include "MCTargetDesc/WeatherMCTargetDesc.h" // For the enum of the regclasses.
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_REGINFO_TARGET_DESC
#include "WeatherGenRegisterInfo.inc"
using namespace llvm;

WeatherRegisterInfo::WeatherRegisterInfo() : WeatherGenRegisterInfo(Weather::R0) {}

const MCPhysReg *
WeatherRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SaveList;
}

BitVector WeatherRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  return Reserved;
}
bool WeatherRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  return false;
}

Register WeatherRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Register();
}