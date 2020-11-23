#ifndef STRING_STREAM_H
#define STRING_STREAM_H

#include <stdlib.h>

typedef struct StringStream StringStream;
struct StringStream {
    char* String;
    char* CurrentPos;
    size_t Pos;
    size_t Size;
};

inline char AdvanceStringStream(StringStream* StringStream);

#endif