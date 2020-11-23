#ifndef ECL_TOKENIZER_H
#define ECL_TOKENIZER_H

typedef enum ParseMode {
	Compile, Tokenize
} ParseMode;

void tokenize(char* Filename, ParseMode Mode);
#endif