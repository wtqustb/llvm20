add_llvm_component_group(Weather)

add_llvm_target(WeatherCodeGen
  WeatherISelLowering.cpp
  WeatherTargetMachine.cpp
  WeatherSubtarget.cpp


  LINK_COMPONENTS
  WeatherDesc
  WeatherInfo

  CodeGen
  Core
  MC
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  Weather
)


add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)