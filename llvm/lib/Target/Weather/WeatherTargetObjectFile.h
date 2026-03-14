//===-- WeatherTargetObjectFile.h - Weather Object Info -------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Weather_WeatherTARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_Weather_WeatherTARGETOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

/// This implementation is used for Weather ELF targets (Linux in particular).
class Weather_ELFTargetObjectFile : public TargetLoweringObjectFileELF {
public:
  Weather_ELFTargetObjectFile();
};

/// This TLOF implementation is used for Darwin.
class Weather_MachoTargetObjectFile : public TargetLoweringObjectFileMachO {
public:
  Weather_MachoTargetObjectFile();
};

} // end namespace llvm

#endif