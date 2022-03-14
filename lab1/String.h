#pragma once
#include "Types.h"
#include "Exit.h"
#include "Vector.h"

struct String;

Exit strInitialize(String *&str, const Char *src);
void strFree(String *&str);

Exit strAppend(String *str, const Char *other);
Exit strIsEndl(bool &result, const String *str);
Exit strIsFirstWord(bool &result, const String *str, const Char *word);
Exit strCutUntil(String *str, Char until);
Exit strNextWord(String *str);
Exit strTrim(String *str);
Exit strToNumber(Real &result, const String *str);
Exit strToNumber(int &result, const String *str);
Exit strDuplicate(String *&newStr, const String *src);
Exit strIsEmpty(bool &empty, const String *str);
