//===-- Weather.td - Describe the Weather Target Machine ------*- tablegen -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This is the top level entry point for the Weather target.
//
//===----------------------------------------------------------------------===//

// Include the generic target definitions.
include "llvm/Target/Target.td"

include "WeatherRegisterInfo.td"

include "WeatherInstrInfo.td"

defm : RemapAllTargetPseudoPointerOperands<GPR32>;

def : ProcessorModel<"generic", NoSchedModel, /*Features=*/[]>;

def WeatherAsmParser : AsmParser;

def WeatherInstrInfo : InstrInfo;

def Weather : Target {
  let InstructionSet = WeatherInstrInfo;
  let AssemblyParsers = [WeatherAsmParser];
}