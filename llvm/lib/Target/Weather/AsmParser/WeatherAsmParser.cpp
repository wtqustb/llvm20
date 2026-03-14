//==- WeatherAsmParser.cpp - Parse Weather assembly to MCInst instructions -----==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/WeatherInstPrinter.h"
#include "MCTargetDesc/WeatherMCTargetDesc.h"
#include "TargetInfo/WeatherTargetInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/ADT/Twine.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCLinkerOptimizationHint.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCParser/AsmLexer.h"
#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/MC/MCParser/MCAsmParserExtension.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TargetParser/SubtargetFeature.h"
#include <cassert>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace llvm;

namespace {

class WeatherOperand;

class WeatherAsmParser : public MCTargetAsmParser {
private:
  SMLoc getLoc() const { return getParser().getTok().getLoc(); }

  bool parseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;
  bool parseRegister(MCRegister &Reg, SMLoc &StartLoc,
                     SMLoc &EndLoc) override;
  ParseStatus tryParseRegister(MCRegister &Reg, SMLoc &StartLoc,
                               SMLoc &EndLoc) override;
  bool matchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

#define GET_ASSEMBLER_HEADER
#include "WeatherGenAsmMatcher.inc"

  ParseStatus parseImmediate(OperandVector &Operands);
  ParseStatus parseRegister(OperandVector &Operands);

public:
  WeatherAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                   const MCInstrInfo &MII, const MCTargetOptions &Options)
      : MCTargetAsmParser(Options, STI, MII) {
    MCAsmParserExtension::Initialize(Parser);
    setAvailableFeatures(ComputeAvailableFeatures(getSTI().getFeatureBits()));
  }
};

class WeatherOperand : public MCParsedAsmOperand {
private:
  SMLoc StartLoc, EndLoc;

  enum KindTy {
    k_Immediate,
    k_Register,
    k_Token,
  } Kind;

  struct TokOp {
    const char *Data;
    unsigned Length;
  };

  struct RegOp {
    unsigned RegNum;
    int ElementWidth;
  };

  struct ImmOp {
    const MCExpr *Val;
  };

  union {
    TokOp Tok;
    RegOp Reg;
    ImmOp Imm;
  };

public:
  WeatherOperand(KindTy K) : Kind(K) {}

  WeatherOperand(const WeatherOperand &O) : MCParsedAsmOperand() {
    StartLoc = O.StartLoc;
    EndLoc = O.EndLoc;
    Kind = O.Kind;
    switch (Kind) {
    case k_Token:
      Tok = O.Tok;
      break;
    case k_Immediate:
      Imm = O.Imm;
      break;
    case k_Register:
      Reg = O.Reg;
      break;
    }
  }

  void print(raw_ostream &OS, const MCAsmInfo &MAI) const override;

  static std::unique_ptr<WeatherOperand> createToken(StringRef Str, SMLoc S) {
    auto Op = std::make_unique<WeatherOperand>(k_Token);
    Op->StartLoc = S;
    Op->EndLoc = S;
    Op->Tok.Data = Str.data();
    Op->Tok.Length = Str.size();
    return Op;
  }

  static std::unique_ptr<WeatherOperand> createReg(unsigned RegNo, SMLoc S,
                                                   SMLoc E) {
    auto Op = std::make_unique<WeatherOperand>(k_Register);
    Op->Reg.RegNum = RegNo;
    Op->Reg.ElementWidth = 0;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  static std::unique_ptr<WeatherOperand> createImm(const MCExpr *Val, SMLoc S,
                                                   SMLoc E) {
    auto Op = std::make_unique<WeatherOperand>(k_Immediate);
    Op->Imm.Val = Val;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }

  void addRegOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands");
    Inst.addOperand(MCOperand::createReg(getReg()));
  }

  void addImmOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands");
    if (const auto *CE = dyn_cast<MCConstantExpr>(getImm()))
      Inst.addOperand(MCOperand::createImm(CE->getValue()));
    else
      Inst.addOperand(MCOperand::createExpr(getImm()));
  }

  StringRef getToken() const {
    assert(Kind == k_Token && "Invalid access");
    return StringRef(Tok.Data, Tok.Length);
  }

  SMLoc getStartLoc() const override { return StartLoc; }
  SMLoc getEndLoc() const override { return EndLoc; }

  bool isToken() const override { return Kind == k_Token; }
  bool isImm() const override { return Kind == k_Immediate; }
  bool isMem() const override { return false; }
  bool isReg() const override { return Kind == k_Register; }

  MCRegister getReg() const override {
    assert(Kind == k_Register && "Invalid access");
    return Reg.RegNum;
  }

  const MCExpr *getImm() const {
    assert(Kind == k_Immediate && "Invalid access");
    return Imm.Val;
  }
};

} // end anonymous namespace

#define GET_REGISTER_MATCHER
#define GET_MATCHER_IMPLEMENTATION
#include "WeatherGenAsmMatcher.inc"

void WeatherOperand::print(raw_ostream &OS, const MCAsmInfo &MAI) const {
  switch (Kind) {
  case k_Immediate:
    MAI.printExpr(OS, *getImm());
    break;
  case k_Token:
    OS << "'" << getToken() << "'";
    break;
  case k_Register:
    OS << "<register " << getReg() << ">";
    break;
  }
}

ParseStatus WeatherAsmParser::parseImmediate(OperandVector &Operands) {
  switch (getLexer().getKind()) {
  default:
    return ParseStatus::NoMatch;
  case AsmToken::LParen:
  case AsmToken::Minus:
  case AsmToken::Plus:
  case AsmToken::Integer:
  case AsmToken::String:
  case AsmToken::Identifier:
    break;
  }

  const MCExpr *Expr = nullptr;
  SMLoc S = getLoc();
  SMLoc E;

  if (getParser().parseExpression(Expr, E))
    return ParseStatus::Failure;

  Operands.push_back(WeatherOperand::createImm(Expr, S, E));
  return ParseStatus::Success;
}

ParseStatus WeatherAsmParser::parseRegister(OperandVector &Operands) {
  const AsmToken &Tok = getParser().getTok();
  if (!Tok.is(AsmToken::Identifier))
    return ParseStatus::NoMatch;

  StringRef Name = Tok.getIdentifier();
  unsigned RegNo = MatchRegisterName(Name);
  if (RegNo == 0)
    return ParseStatus::NoMatch;

  SMLoc S = Tok.getLoc();
  SMLoc E = Tok.getEndLoc();
  getParser().Lex();

  Operands.push_back(WeatherOperand::createReg(RegNo, S, E));
  return ParseStatus::Success;
}

bool WeatherAsmParser::parseInstruction(ParseInstructionInfo &Info,
                                        StringRef Name, SMLoc NameLoc,
                                        OperandVector &Operands) {
  Operands.push_back(WeatherOperand::createToken(Name, NameLoc));

  while (!getLexer().is(AsmToken::EndOfStatement)) {
    if (parseRegister(Operands).isSuccess())
      continue;

    if (getLexer().is(AsmToken::Comma)) {
      getLexer().Lex();
      continue;
    }

    if (parseImmediate(Operands).isSuccess())
      continue;

    return Error(getLexer().getLoc(), "unexpected token");
  }

  getParser().Lex(); // Eat EndOfStatement.
  return false;
}

bool WeatherAsmParser::parseRegister(MCRegister &Reg, SMLoc &StartLoc,
                                     SMLoc &EndLoc) {
  ParseStatus Res = tryParseRegister(Reg, StartLoc, EndLoc);
  if (!Res.isSuccess())
    return Error(StartLoc, "invalid register name");
  return false;
}

ParseStatus WeatherAsmParser::tryParseRegister(MCRegister &Reg,
                                               SMLoc &StartLoc,
                                               SMLoc &EndLoc) {
  const AsmToken &Tok = getParser().getTok();
  if (!Tok.is(AsmToken::Identifier))
    return ParseStatus::NoMatch;

  StartLoc = Tok.getLoc();
  EndLoc = Tok.getEndLoc();

  StringRef Name = Tok.getIdentifier();
  unsigned RegNo = MatchRegisterName(Name);
  if (RegNo == 0)
    return ParseStatus::NoMatch;

  Reg = RegNo;
  getParser().Lex(); // Eat identifier.
  return ParseStatus::Success;
}

bool WeatherAsmParser::matchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                                               OperandVector &Operands,
                                               MCStreamer &Out,
                                               uint64_t &ErrorInfo,
                                               bool MatchingInlineAsm) {
  MCInst Inst;
  SMLoc ErrorLoc;

  switch (MatchInstructionImpl(Operands, Inst, ErrorInfo, MatchingInlineAsm)) {
  default:
    break;
  case Match_Success:
    Inst.setLoc(IDLoc);
    Out.emitInstruction(Inst, getSTI());
    return false;
  case Match_MissingFeature:
    return Error(IDLoc, "instruction use requires an option to be enabled");
  case Match_MnemonicFail:
    return Error(IDLoc, "unrecognized instruction mnemonic");
  case Match_InvalidOperand:
    ErrorLoc = IDLoc;

    if (ErrorInfo != ~0U) {
      if (ErrorInfo >= Operands.size())
        return Error(ErrorLoc, "too few operands for instruction");

      ErrorLoc = static_cast<WeatherOperand &>(*Operands[ErrorInfo]).getStartLoc();
      if (ErrorLoc == SMLoc())
        ErrorLoc = IDLoc;
    }

    return Error(ErrorLoc, "invalid operand for instruction");
  }

  llvm_unreachable("Unknown match type detected");
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeWeatherAsmParser() {
  RegisterMCAsmParser<WeatherAsmParser> X(getTheWeatherTarget());
}