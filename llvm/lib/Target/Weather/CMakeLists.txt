add_llvm_component_group(Weather)

add_llvm_target(WeatherCodeGen
  WeatherTargetMachine.cpp


  LINK_COMPONENTS
  WeatherDesc
  WeatherInfo

  CodeGen
  Core
  Support
  Target

  ADD_TO_COMPONENT
  Weather
)


add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)