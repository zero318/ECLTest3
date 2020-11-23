#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include "SquitUtil.h"

void* callocNonNull(size_t _Count, size_t _Size) {
	void* temp = calloc(_Count, _Size);
	if (temp != NULL) return temp;
	exit(EXIT_FAILURE);
}

void* mallocNonNull(size_t _Size) {
	void* temp = malloc(_Size);
	if (temp != NULL) return temp;
	exit(EXIT_FAILURE);
}

FILE* fopenWrapper(const char* _Filename, const char* _Mode) {
	FILE* temp = fopen(_Filename, _Mode);
	if (temp != NULL) return temp;
	exit(EXIT_FAILURE);
}

//char* StringDupe(const char* StringSource) {
//	size_t Size = strlen(StringSource) + 1;
//	char* Temp = mallocNonNull(Size);
//	return memcpy(Temp, StringSource, Size);
//}
//char* StringSizeDupe(const char* StringSource, size_t _StringSize) {
//	char* Temp = mallocNonNull(_StringSize);
//	return memcpy(Temp, StringSource, _StringSize);
//}
//char* StringDupeToSize(const char* StringSource, size_t _BufferSize) {
//	size_t TrueSize = (char*)memchr(StringSource, '\0', _BufferSize) - StringSource;
//	char* Temp = mallocNonNull(_BufferSize);
//	return memcpy(Temp, StringSource, TrueSize > _BufferSize ? _BufferSize : TrueSize);
//}
//char* StringSizeDupeToSize(const char* StringSource, size_t _StringSize, size_t _BufferSize) {
//	size_t TrueSize = (char*)memchr(StringSource, '\0', _BufferSize) - StringSource;
//	if (_StringSize < TrueSize) TrueSize = _StringSize;
//	char* Temp = mallocNonNull(_BufferSize);
//	return memcpy(Temp, StringSource, TrueSize > _BufferSize ? _BufferSize : TrueSize);
//}

char* StringDupe(const char* StringSource) {
	size_t Size = strlen(StringSource) + 1;
#if CHAR_BIT != 8
	Size *= sizeof(char);
#endif
	char* Temp = mallocNonNull(Size);
	return memcpy(Temp, StringSource, Size);
}
//char* StringDupeToSize(const char* StringSource, size_t _BufferSize) {
//	char* Temp = mallocNonNull(_BufferSize);
//	memcpy(Temp, StringSource, _BufferSize);
//	Temp[_BufferSize] = '\0';
//	return Temp;
//}
char* StringSizeDupe(const char* StringSource, size_t _StringSize) {
#if CHAR_BIT != 8
	_StringSize *= sizeof(char);
#endif
	char* Temp = mallocNonNull(_StringSize + 1);
	memcpy(Temp, StringSource, _StringSize);
	Temp[_StringSize] = '\0';
	return Temp;
}
char* StringDupeToSize(const char* StringSource, size_t _BufferSize) {
	size_t TrueSize = (char*)memchr(StringSource, '\0', _BufferSize) - StringSource;
#if CHAR_BIT != 8
	TrueSize /= sizeof(char);
	TrueSize *= sizeof(char);
	_BufferSize *= sizeof(char);
#endif
	char* Temp = mallocNonNull(_BufferSize + 1);
	if (_BufferSize < TrueSize) TrueSize = _BufferSize;
	memcpy(Temp, StringSource, TrueSize);
	//strncpy(Temp, StringSource, TrueSize);
	Temp[TrueSize] = '\0';
	return Temp;
}
char* StringSizeDupeToSize(const char* StringSource, size_t _StringSize, size_t _BufferSize) {
	size_t TrueSize = (char*)memchr(StringSource, '\0', _BufferSize) - StringSource;
#if CHAR_BIT != 8
	TrueSize /= sizeof(char);
	TrueSize *= sizeof(char);
	_StringSize *= sizeof(char);
	_BufferSize *= sizeof(char);
#endif
	if (_StringSize < TrueSize) TrueSize = _StringSize;
	if (_BufferSize < TrueSize) TrueSize = _BufferSize;
	char* Temp = mallocNonNull(_BufferSize + 1);
	memcpy(Temp, StringSource, TrueSize);
	Temp[TrueSize] = '\0';
	return Temp;
}


//void intentional_crash() {
//	//whatever you did to get here, you now get to crash and burn
//	void* yeet = NULL;
//	*yeet;
//}

void ExitWithError(const char* ErrorMessageFormat, ...) {
	va_list args = NULL;
	va_start(args, ErrorMessageFormat);
	vfprintf(stderr, ErrorMessageFormat, args);
	exit(1);
}

//void ThreeWayCompare(void* A, void* B) {
//
//}