#ifndef SQUIT_UTIL_H
#define SQUIT_UTIL_H

#include <stdlib.h>
#include <stdio.h>

//The compiler will optimize away the empty loop
//since it'll always terminate immediately, but it
//still forces use of a semicolon for other macros.
#define RequireSemicolon(Yeetus) do {Yeetus} while (0)

//This is used to simplify declaring structs with pointers to the same struct type.
#define DeclareStruct(Type) typedef struct Type Type

#define DeclareUnion(Type) typedef union Type Type

#ifndef SQUIT_UTIL_NO_TRASH_OBJECTS

#define DeclareConstructor(ConstructorType) ConstructorType* New ## ConstructorType()

#define DefineConstructorName(ConstructorType) New ## ConstructorType
#define DefineConstructor(ConstructorType, ...) \
ConstructorType* DefineConstructorName(ConstructorType)() {\
	ConstructorType* temp = mallocNonNull(sizeof(ConstructorType));\
	*temp = (ConstructorType){__VA_ARGS__};\
	return temp;\
}

#define DefineConstructorNoInit(ConstructorType) \
ConstructorType* DefineConstructorName(ConstructorType)() {\
	return mallocNonNull(sizeof(ConstructorType));\
}
#endif

typedef unsigned char flag;

void* callocNonNull(size_t _Count, size_t _Size);
void* mallocNonNull(size_t _Size);
FILE* fopenWrapper(const char* _Filename, const char* _Mode);
char* StringDupe(const char* StringSource);
char* StringSizeDupe(const char* StringSource, size_t _StringSize);
char* StringDupeToSize(const char* StringSource, size_t _BufferSize);
char* StringSizeDupeToSize(const char* StringSource, size_t _StringSize, size_t _BufferSize);
void ExitWithError(const char* ErrorMessageFormat, ...);

#undef RequireSemicolon

#endif