add_llvm_component_library(LLVMWeatherDesc
  WeatherMCAsmInfo.cpp
  WeatherMCTargetDesc.cpp
  WeatherInstPrinter.cpp
  WeatherMCCodeEmitter.cpp

  LINK_COMPONENTS
  Support
  WeatherInfo
  MC


  ADD_TO_COMPONENT
  Weather
)