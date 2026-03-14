include "WeatherInstrFormats.td"


def ADDi16rr : WeatherBinaryInstruction<"addi16",
                                      /*opcode=*/0,
                                      /*is32Bit=*/false>;

let Uses = [R0], isReturn = 1, isTerminator = 1, isBarrier = 1 in
def RETURN : WeatherNoOperandInstruction<"ret",
                                       /*opcode=*/0b00001,
                                       /*is32Bit=*/false>;

let isPseudo = 1, isCodeGenOnly = 1, hasNoSchedulingInfo = 1 in {
  def ADJCALLSTACKDOWN : WeatherInstruction<
      "adjcallstackdown", "",
      0, 0,
      (outs),
      (ins i32imm:$amt1, i32imm:$amt2)
  >;

  def ADJCALLSTACKUP : WeatherInstruction<
      "adjcallstackup", "",
      0, 0,
      (outs),
      (ins i32imm:$amt1, i32imm:$amt2)
  >;
}