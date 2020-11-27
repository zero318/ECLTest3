#ifndef SQUIT_STRINGS_H
#define SQUIT_STRINGS_H

char* StringDupe(const char* StringSource);
void* MemoryDupe(const void* MemorySource, size_t MemorySize);
char* StringDupe_S(const char* StringSource, size_t BufferSize);
void* MemoryDupe_S(const void* MemorySource, size_t MemorySize, size_t BufferSize);

//char* StringCStripOld(char* String, char c);
//char* StringCStrip2(char* String, char c);
//char* __fastcall StringCStrip3(char* String, char c);
char* __fastcall StringCStrip(char* String, char c);
char* __fastcall StringCStripReplace(char* String, char c, char d);
//char* __fastcall StringSStripFast(char* String, const char* cset);
char* __fastcall StringSStrip(char* String, const char* cset);
//char* __fastcall StringSStripReplaceFast(char* String, const char* cset, char d);
char* __fastcall StringSStripReplace(char* String, const char* cset, char d);

#endif