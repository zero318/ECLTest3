#include "StringStream.h"

inline char AdvanceStringStream(StringStream* StringStream) {
	return *StringStream->CurrentPos++;
}