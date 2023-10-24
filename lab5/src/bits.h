#ifndef BITS_H
#define BITS_H

#include "tree.h"

void WriteBit(FILE *, char *, char *, char);

void WriteByte(FILE *, char *, char *, char);

void WriteInt(FILE *, char *, char *, unsigned int);

void WriteBitTree(FILE *, Node_t *, char *, char *);

char ReadBit(FILE *, char *, char *);

char ReadByte(FILE *, char *, char *);

int ReadInt(FILE *, char *, char *);

Node_t * ReadBitTree(FILE *, char *, char *);

#endif
