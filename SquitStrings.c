#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "SquitUtil.h"
#include "SquitStrings.h"

//Visual studio, could you *please* shut up about bool being invalid?
//I included the dang headers already and you compile just fine...
#ifndef bool
#define bool _Bool
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

static bool _CharBoolTable[UCHAR_MAX + -SCHAR_MIN];
static bool *const CharBoolTable = &_CharBoolTable[-SCHAR_MIN];
inline static void __fastcall SetCharBoolTable(const char* cset, bool value) {
	const char* ScratchC = cset;
	char temp;
	while ((temp = *(ScratchC++)) != '\0') {
		CharBoolTable[temp] = value;
	}
}

char* StringDupe(const char* StringSource) {
	size_t Size = strlen(StringSource) + 1;
	char* Temp = mallocNonNull(Size);
	return memcpy(Temp, StringSource, Size);
}
void* MemoryDupe(const void* MemorySource, size_t MemorySize) {
	void* Temp = mallocNonNull(MemorySize);
	return memcpy(Temp, MemorySource, MemorySize);;
}
char* StringDupe_S(const char* StringSource, size_t BufferSize) {
	size_t TrueSize = (char*)memchr(StringSource, '\0', BufferSize) - StringSource;
	char* Temp = mallocNonNull(BufferSize + 1);
	if (BufferSize < TrueSize) TrueSize = BufferSize;
	memcpy(Temp, StringSource, TrueSize);
	Temp[TrueSize] = '\0';
	return Temp;
}
void* MemoryDupe_S(const void* MemorySource, size_t MemorySize, size_t BufferSize) {
	size_t TrueSize = MemorySize < BufferSize ? MemorySize : BufferSize;
	void* Temp = mallocNonNull(BufferSize);
	return memcpy(Temp, MemorySource, TrueSize);
}

char* __fastcall StringCStrip(char* String, char c) {
	char* ScratchString = String;
	if (ScratchString != NULL || *ScratchString != '\0') {
		while (*(++ScratchString) != '\0');
		char* EndString = ++ScratchString;
		ScratchString = String;
		do {
			if (*ScratchString != c) {
				++ScratchString;
				continue;
			}
			char* TempString = ScratchString;
			while (*(++ScratchString) == c);
			ptrdiff_t ScratchDelta = EndString - --ScratchString;
			do *(TempString++) = *(++ScratchString);
			while (ScratchString != EndString);
			EndString -= ScratchString - TempString;
			ScratchString = TempString - ScratchDelta;
		} while (ScratchString != EndString);
		*EndString = '\0';
	}
	return String;
}

char* __fastcall StringCStripReplace(char* String, char c, char d) {
	char* ScratchString = String;
	if (ScratchString != NULL && *ScratchString != '\0') {
		while (*(++ScratchString) != '\0');
		char* EndString = ++ScratchString;
		ScratchString = String;
		do {
			if (*ScratchString != c) {
				++ScratchString;
				continue;
			}
			*(ScratchString++) = d;
			char* TempString = ScratchString;
			while (*(ScratchString) == c) ++ScratchString;
			if (ScratchString == TempString) continue;
			ptrdiff_t ScratchDelta = EndString - --ScratchString;
			do *(TempString++) = *(++ScratchString);
			while (ScratchString != EndString);
			EndString -= ScratchString - TempString;
			ScratchString = TempString - ScratchDelta;
		} while (ScratchString != EndString);
		*EndString = '\0';
	}
	return String;
}

char* __fastcall StringSStrip(char* String, const char* cset) {
	char* ScratchString = String;
	const char* ScratchC = cset;
	if (ScratchString != NULL && *ScratchString != '\0' && ScratchC != NULL && *ScratchC != '\0') {
		SetCharBoolTable(ScratchC, true);
		ScratchString = String;
		while (*(++ScratchString) != '\0');
		char* EndString = ScratchString;
		ScratchString = String;
		do {
			if (!CharBoolTable[*ScratchString]) {
				++ScratchString;
				continue;
			}
			char* TempString = ScratchString;
			while (CharBoolTable[*(++ScratchString)]);
			ptrdiff_t ScratchDelta = EndString - --ScratchString;
			do *(TempString++) = *(++ScratchString);
			while (ScratchString != EndString);
			EndString -= ScratchString - TempString;
			ScratchString = TempString - ScratchDelta;
		} while (ScratchString != EndString);
		*EndString = '\0';
		SetCharBoolTable(ScratchC, false);
	}
	return String;
}

char* __fastcall StringSStripReplace(char* String, const char* cset, char d) {
	char* ScratchString = String;
	const char* ScratchC = cset;
	if (ScratchString != NULL && *ScratchString != '\0' && ScratchC != NULL && *ScratchC != '\0') {
		SetCharBoolTable(ScratchC, true);
		ScratchString = String;
		while (*(++ScratchString) != '\0');
		char* EndString = ScratchString;
		ScratchString = String;
		do {
			if (!CharBoolTable[*ScratchString]) {
				++ScratchString;
				continue;
			}
			*(ScratchString++) = d;
			char* TempString = ScratchString;
			while (CharBoolTable[*(ScratchString)]) ++ScratchString;
			if (ScratchString == TempString) continue;
			ptrdiff_t ScratchDelta = EndString - --ScratchString;
			do *(TempString++) = *(++ScratchString);
			while (ScratchString != EndString);
			EndString -= ScratchString - TempString;
			ScratchString = TempString - ScratchDelta;
		} while (ScratchString != EndString);
		*EndString = '\0';
		SetCharBoolTable(ScratchC, false);
	}
	return String;
}

#pragma region
//Old StringStripFuncs
#if 0

//char* __fastcall StringCStrip3(char* String, char c) {
//	char* ScratchString = String;
//	if (ScratchString == NULL || *ScratchString == '\0') return ScratchString;
//	//Scan to end of string
//	while (*++ScratchString != '\0');
//	//Save pointer past end of string
//	char* EndString = ScratchString + 1;
//	//Rewind to beginning of string
//	ScratchString = String;
//	do {
//		//If c is not found...
//		if (*ScratchString != c) {
//			//...increment the string and continue.
//			++ScratchString;
//			continue;
//		}
//		//If c is found, save a backup of the location...
//		char* TempString = ScratchString;
//		//...and then scan until there are no more c.
//		do ++ScratchString;
//		while (*ScratchString == c);
//		//Copy the string
//		//Calculate how much will be copied.
//		ptrdiff_t Delta = EndString - ScratchString;
//		do *TempString++ = *ScratchString++;
//		while (ScratchString != EndString);
//		//Adjust the end pointer by the amount that needed to be copied.
//		EndString -= ScratchString - TempString;
//		//Reset and offset the string pointer.
//		ScratchString = (TempString - Delta) + 1;
//	//Only exit once there's no more string to scan
//	} while (ScratchString != EndString);
//	//Readd a null terminator
//	*EndString = '\0';
//	return String;
//}

static char* StringCStripOld(char* String, char c) {
	size_t Length = strlen(String) + 1;
	size_t i = 0;
	while (i < Length && String[i] != '\0') {
		if (String[i] == c) {
			memmove(String + i, String + i + 1, Length - i);
			continue;
		}
		++i;
		continue;
	}
	return String;

}
static char* StringCStrip2(char* String, char c) {
	char* temp = String;
	while ((temp = strchr(temp, c))) {
		*temp = '\0';
		strcat(temp, temp + 1);
	}
	return String;
}

static char* __fastcall StringSStripFast(char* String, const char* cset) {
	char* ScratchString = String;
	const char* ScratchC = cset;
	if (ScratchString != NULL && *ScratchString != '\0' && ScratchC != NULL && *ScratchC != '\0') {
		ScratchString = String;
		while (*(++ScratchString) != '\0');
		char* EndString = ScratchString;
		ScratchString = String;
		do {
			ScratchC = cset;
			char temp = *ScratchString;
			char c = *(ScratchC++);
			do {
				if (temp == c) {
					goto StringSStripReplaceFastLoop1;
				}
				c = *(ScratchC++);
			} while (c != '\0');
			++ScratchString;
			continue;
StringSStripReplaceFastLoop1:;
			char* TempString = ScratchString;
			temp = *++ScratchString;
			ScratchC = cset;
			do {
				c = *(ScratchC++);
				if (temp == c) {
					ScratchC = cset;
					temp = *(++ScratchString);
					continue;
				}
			} while (c != '\0');
			ptrdiff_t ScratchDelta = EndString - --ScratchString;
			do *(TempString++) = *(++ScratchString);
			while (ScratchString != EndString);
			EndString -= ScratchString - TempString;
			ScratchString = TempString - ScratchDelta;
		} while (ScratchString != EndString);
		*EndString = '\0';
	}
	return String;
}

static char* __fastcall StringSStripReplaceFast(char* String, const char* cset, char d) {
	char* ScratchString = String;
	const char* ScratchC = cset;
	if (ScratchString != NULL && *ScratchString != '\0' && ScratchC != NULL && *ScratchC != '\0') {
		ScratchString = String;
		while (*(++ScratchString) != '\0');
		char* EndString = ScratchString;
		ScratchString = String;
		do {
			ScratchC = cset;
			char temp = *ScratchString;
			char c = *(ScratchC++);
			do {
				if (temp == c) {
					goto StringSStripReplaceFastLoop1;
				}
				c = *(ScratchC++);
			} while (c != '\0');
			++ScratchString;
			continue;
StringSStripReplaceFastLoop1:
			*(ScratchString++) = d;
			char* TempString = ScratchString;
			temp = *ScratchString;
			ScratchC = cset;
			do {
				c = *(ScratchC++);
				if (temp == c) {
					ScratchC = cset;
					temp = *(++ScratchString);
					continue;
				}
			} while (c != '\0');
			if (ScratchString == TempString) continue;
			ptrdiff_t ScratchDelta = EndString - --ScratchString;
			do *(TempString++) = *(++ScratchString);
			while (ScratchString != EndString);
			EndString -= ScratchString - TempString;
			ScratchString = TempString - ScratchDelta;
		} while (ScratchString != EndString);
		*EndString = '\0';
	}
	return String;
}
#endif
#pragma endregion