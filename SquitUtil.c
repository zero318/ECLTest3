#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>

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