include "WeatherInstrFormats.td"


def ADDi16rr : WeatherInstruction<"addi16", "$dst, $src0, $src1",
                                /*opcode=*/0,
                                /*is32Bit*/false,
                                (outs GPR16:$dst),
                                (ins GPR16:$src0, GPR16:$src1)>;