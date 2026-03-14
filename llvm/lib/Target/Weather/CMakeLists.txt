add_llvm_component_group(Weather)

set(LLVM_TARGET_DEFINITIONS Weather.td)

tablegen(LLVM WeatherGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM WeatherGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM WeatherGenInstrInfo.inc -gen-instr-info)

add_public_tablegen_target(WeatherCommonTableGen)

add_llvm_target(WeatherCodeGen
  WeatherISelLowering.cpp
  WeatherSubtarget.cpp
  WeatherTargetMachine.cpp
  WeatherTargetObjectFile.cpp
  WeatherTargetTransformInfo.cpp


  LINK_COMPONENTS
  WeatherDesc
  WeatherInfo

  Analysis
  CodeGen
  Core
  MC
  SelectionDAG
  Support
  Target
  TargetParser
  TransformUtils


  ADD_TO_COMPONENT
  Weather
)


add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)