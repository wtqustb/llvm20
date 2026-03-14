add_llvm_component_library(LLVMWeatherDesc
  WeatherMCAsmInfo.cpp
  WeatherMCTargetDesc.cpp

  LINK_COMPONENTS
  Support
  WeatherInfo
  MC


  ADD_TO_COMPONENT
  Weather
)