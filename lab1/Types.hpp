#pragma once

#define WCHAR
typedef double Real;

#ifdef WCHAR
typedef wchar_t Char;
#define TEXT(t) (L##t)
#else
typedef char Char;
#define TEXT(t) (t)
#endif
