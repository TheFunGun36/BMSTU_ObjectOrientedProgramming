#include "String.hpp"
#include <cstring>
#include <cstdlib>

struct String {
    size_t allocated;
    Char *memory;
    Char *current;
    Char *end; // указывает на \0
};

static inline bool isSpace(Char c) {
    return strchr(" \t\v\n\r\f", c);
}

Exit strInitialize(String *&str, const Char *src) {
    Exit ec = str ? Exit::strInitialized : Exit::success;

    size_t sz = 0;
    if (!src) {
        ec = Exit::strEmpty;
    }
    else if (isOk(ec)) {
        sz = strlen(src) + 1;
        ec = allocImpl(str);
    }

    if (isOk(ec)) {
        ec = allocImpl(str->memory, sz);
    }

    if (isOk(ec)) {
        str->allocated = sz;
        str->current = str->memory;
        str->end = str->current + sz - 1;
        memcpy(str->current, src, sz * sizeof(Char));
    }
    else {
        free(str);
        str = nullptr;
    }

    return ec;
}

void strFree(String *&str) {
    if (str)
        free(str->memory);
    free(str);
    str = nullptr;
}

Exit strAppend(String *str, const Char *other) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    Char *oldMemory = nullptr;
    size_t otherLen = 0;

    if (!other) {
        ec = Exit::strEmpty;
    }
    else if (isOk(ec)) {
        otherLen = strlen(other);
        oldMemory = str->memory;
        ec = reallocImpl(str->memory, str->allocated + otherLen);
    }

    if (isOk(ec)) {
        size_t ptrDiff = str->memory - oldMemory;
        str->current += ptrDiff;
        str->end += ptrDiff;

        str->allocated += otherLen;
        memcpy(str->end, other, (otherLen + 1) * sizeof(Char));

        str->end += otherLen;
    }

    return ec;
}

Exit strIsEndl(bool &result, const String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if (isOk(ec)) {
        Char *end = str->end - 1;
        result = end >= str->current && *end == '\n';
    }

    return ec;
}

Exit strIsFirstWord(bool &result, const String *str, const Char *word) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if (isOk(ec))
        ec = word ? Exit::success : Exit::strEmpty;

    if (isOk(ec)) {
        result = true;

        const Char *p = str->current;
        const Char *w = word;
        while (p < str->end && *w != '\0') {
            result = *p == *w;

            p++;
            w++;
        }

        
        result = result && isSpace(*p);
    }

    return ec;
}

Exit strCutUntil(String *str, Char until) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if (isOk(ec)) {
        Char *p = str->current;
        while (p < str->end && *p != until)
            p++;

        if (*p == until) {
            *p = '\0';
            str->end = p;
        }
    }

    return ec;
}

Exit strNextWord(String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if (isOk(ec)) {
        Char *p = str->current;

        while (p < str->end && !isSpace(*p))
            p++;
        while (p < str->end && isSpace(*p))
            p++;
    }

    return ec;
}

Exit strTrim(String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if(isOk(ec)) {
        while (str->current < str->end && isSpace(*str->current))
            str->current++;
        while (str->end > str->current && isSpace(*str->end))
            str->end--;
        *str->end = '\0';
    }

    return ec;
}

Exit strToNumber(Real &result, const String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;
    
    if (isOk(ec)) {
        Char *end = nullptr;
        result = strtod(str->current, &end);
        ec = (end == str->current) ? Exit::strNAN : Exit::success;
    }

    return ec;
}

Exit strToNumber(int &result, const String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if (isOk(ec)) {
        Char *end = nullptr;
        result = strtol(str->current, &end, 10);
        ec = (end == str->current) ? Exit::strNAN : Exit::success;
    }

    return ec;
}

Exit strDuplicate(String *&newStr, const String *src) {
    Exit ec = src ? Exit::success : Exit::strUninitialized;

    if (isOk(ec))
        ec = newStr ? Exit::strInitialized : Exit::success;

    if (isOk(ec))
        ec = strInitialize(newStr, src->current);

    return ec;
}

Exit strIsEmpty(bool &empty, const String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if (isOk(ec))
        empty = str->current == str->end;

    return ec;
}
