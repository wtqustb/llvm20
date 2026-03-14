include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_component_library(LLVMWeatherAsmParser
  WeatherAsmParser.cpp

  LINK_COMPONENTS
  WeatherDesc
  WeatherInfo
  CodeGenTypes
  MC
  MCParser
  Support
  TargetParser

  ADD_TO_COMPONENT
  Weather
  )
