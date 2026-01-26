#include "WeatherTargetInfo.h"
#include "llvm/MC/TargetRegistry.h" // For RegisterTarget.
#include "llvm/Support/Compiler.h"  // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/TargetParser/Triple.h"
#include "llvm/TextAPI/Target.h"    // For Target class.


using namespace llvm;

Target &llvm::getTheWeatherTarget() {
  static Target TheWeatherTarget;
  return TheWeatherTarget;
}
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeWeatherTargetInfo() {
    RegisterTarget<Triple::weather, /*HasJIT=*/false> X(getTheWeatherTarget(), /*Name=*/"weather",
                                                    "Weather", "Weather");
}