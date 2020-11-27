#ifndef REGISTER_WATCH_H
#define REGISTER_WATCH_H
#include <stdint.h>
#include <stdalign.h>

#if UINTPTR_MAX == 0xffffffff

typedef uint32_t Register32;

#define EAXStyleRegister(Letter)\
typedef union {\
	uint32_t Input;\
	union {\
		int32_t E ## Letter ## X;\
		int32_t Letter ## X : 16;\
		struct {\
			int32_t Letter ## L : 8;\
			int32_t Letter ## H : 8;\
		};\
	} Signed;\
	union {\
		uint32_t E ## Letter ## X;\
		uint32_t Letter ## X : 16;\
		struct {\
			uint32_t Letter ## L : 8;\
			uint32_t Letter ## H : 8;\
		};\
	} Unsigned;\
	struct {\
		char Letter ## L_Char;\
		char Letter ## H_Char;\
	};\
	char* str;\
	void* ptr;\
} _E ## Letter ## X;\
const _E ## Letter ## X GetE ## Letter ## X(const Register32 _E ## Letter ## XT) {\
	return (const _E ## Letter ## X){.Unsigned.E ## Letter ## X = _E ## Letter ## XT };\
}
#define ESPStyleRegister(Letters)\
typedef union {\
	union {\
		int32_t E ## Letters;\
		int32_t Letters : 16;\
		int32_t Letters ## L : 8;\
	} Signed;\
	union {\
		uint32_t E ## Letters;\
		uint32_t Letters : 16;\
		uint32_t Letters ## L : 8;\
	} Unsigned;\
	char Char;\
	char* str;\
	void* ptr;\
} E ## Letters

typedef struct _EAXTT {
	uint32_t input;
} _EAXTT;

_EAXTT eeeeeeeeee(void) {
	return (_EAXTT) {
		.input = 0
	};
}

static _EAXTT jskdbfksdbf;

EAXStyleRegister(A);
EAXStyleRegister(C);
EAXStyleRegister(D);
EAXStyleRegister(B);
ESPStyleRegister(SP);
ESPStyleRegister(BP);
ESPStyleRegister(SI);
ESPStyleRegister(DI);

#elif UINTPTR_MAX == 0xffffffffffffffff

#endif

#endif