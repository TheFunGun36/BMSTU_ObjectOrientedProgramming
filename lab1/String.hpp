#pragma once
#include "Exit.hpp"
#include "Vector.hpp"

struct String;

Exit strInitialize(String *&str, const char *src);
void strFree(String *&str);

Exit strAppend(String *str, const char *other);
Exit strIsEndl(bool &result, const String *str);
Exit strIsFirstWord(bool &result, const String *str, const char *word);
Exit strCutUntil(String *str, char until);
Exit strNextWord(String *str);
Exit strTrim(String *str);
Exit strToNumber(double &result, const String *str);
Exit strToNumber(int &result, const String *str);
Exit strDuplicate(String *&newStr, const String *src);
Exit strIsEmpty(bool &empty, const String *str);
