#ifndef INCLUDE_FIRESTARTER_ENVIRONMENT_X86_X86ENVIRONMENT_HPP
#define INCLUDE_FIRESTARTER_ENVIRONMENT_X86_X86ENVIRONMENT_HPP

#include <firestarter/Environment/Environment.hpp>

#include <firestarter/Environment/X86/Platform/X86PlatformConfig.hpp>
#include <firestarter/Environment/X86/Platform/KnightsLandingConfig.hpp>
#include <firestarter/Environment/X86/Platform/SkylakeConfig.hpp>
#include <firestarter/Environment/X86/Platform/SkylakeSPConfig.hpp>
#include <firestarter/Environment/X86/Platform/HaswellConfig.hpp>
#include <firestarter/Environment/X86/Platform/HaswellEPConfig.hpp>
#include <firestarter/Environment/X86/Platform/SandyBridgeConfig.hpp>
#include <firestarter/Environment/X86/Platform/SandyBridgeEPConfig.hpp>
#include <firestarter/Environment/X86/Platform/NehalemConfig.hpp>
#include <firestarter/Environment/X86/Platform/NehalemEPConfig.hpp>
#include <firestarter/Environment/X86/Platform/BulldozerConfig.hpp>

#include <asmjit/asmjit.h>

#include <functional>

extern "C" {
#include <firestarter/Compat/util.h>
}

#define REGISTER(NAME) \
	[](llvm::StringMap<bool> *supportedFeatures, unsigned family, unsigned model, unsigned threads) -> \
		platform::X86PlatformConfig * { return new platform::NAME(supportedFeatures, family, model, threads); }

namespace firestarter::environment::x86 {

	class X86Environment : public Environment {
		public:
			X86Environment() : Environment(), cpuInfo(asmjit::CpuInfo::host()) {};
			~X86Environment() {};

			void evaluateFunctions(void) override;
			int selectFunction(unsigned functionId) override;
			void printFunctionSummary(void) override;

		private:
			asmjit::CpuInfo cpuInfo;

			int getCpuClockrate(void) override;

			std::string getModel(void) override {
				std::stringstream ss;
				ss << "Family " << cpuInfo.familyId() << ", Model " << cpuInfo.modelId() << ", Stepping " << cpuInfo.stepping();
				return ss.str();
			}

			// The available function IDs are generated by iterating through this list of PlatformConfig
			// Add new PlatformConfig at the bottom to maintain stable IDs.
			const std::list<std::function<platform::X86PlatformConfig *(llvm::StringMap<bool> *, unsigned, unsigned, unsigned)>> platformConfigsCtor = {
				REGISTER(KnightsLandingConfig),
				REGISTER(SkylakeConfig),
				REGISTER(SkylakeSPConfig),
				REGISTER(HaswellConfig),
				REGISTER(HaswellEPConfig),
				REGISTER(SandyBridgeConfig),
				REGISTER(SandyBridgeEPConfig),
				REGISTER(NehalemConfig),
				REGISTER(NehalemEPConfig),
				REGISTER(BulldozerConfig),
			};

			std::list<platform::X86PlatformConfig *> platformConfigs;
	};

}

#endif
