add_llvm_component_library(LLVMWeatherDesc
  WeatherMCTargetDesc.cpp

  LINK_COMPONENTS
  Support


  ADD_TO_COMPONENT
  Weather
)