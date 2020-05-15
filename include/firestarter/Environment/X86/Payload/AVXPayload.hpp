#ifndef INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PAYLOAD_AVXPAYLOAD_H
#define INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PAYLOAD_AVXPAYLOAD_H

#include <firestarter/Environment/X86/Payload/X86Payload.hpp>

namespace firestarter::environment::x86::payload {
	class AVXPayload : public X86Payload {
		public:
			AVXPayload(llvm::StringMap<bool> *supportedFeatures) : X86Payload(supportedFeatures, {"avx"}, "AVX") {};

			void compilePayload(llvm::StringMap<unsigned> proportion) override;
			std::list<std::string> getAvailableInstructions(void) override;
			void init(...) override;
			void highLoadFunction(...) override;
	};
}

#endif
