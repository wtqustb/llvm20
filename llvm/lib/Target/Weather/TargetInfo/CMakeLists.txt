add_llvm_component_library(LLVMWeatherInfo
  WeatherTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  TextAPI

  ADD_TO_COMPONENT
  Weather
  )