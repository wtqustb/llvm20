add_llvm_component_group(Weather)

add_llvm_target(WeatherCodeGen
  WeatherISelLowering.cpp
  WeatherTargetMachine.cpp
  WeatherTargetTransformInfo.cpp
  WeatherSubtarget.cpp


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