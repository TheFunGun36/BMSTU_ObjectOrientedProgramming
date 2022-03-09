#include "String.hpp"
#include <cstring>
#include <cstdlib>

struct String {
    size_t allocated;
    Char *memory;
    Char *current;
    Char *end; // указывает на \0
};

static inline size_t strlenImpl(const Char *str) {
#ifdef WCHAR
    return wcslen(str);
#else
    return strlen(str);
#endif
}

static inline double strtodImpl(const Char *str, Char **endPtr) {
#ifdef WCHAR
    return wcstod(str, endPtr);
#else
    return strtod(str, endPtr);
#endif
}

static inline long strtolImpl(const Char *str, Char **endPtr, int radix) {
#ifdef WCHAR
    return wcstol(str, endPtr, radix);
#else
    return strtol(str, endPtr, radix);
#endif
}

static inline bool isSpace(Char c) {
#ifdef WCHAR
    return wcschr(TEXT(" \t\v\n\r\f"), c);
#else
    return strchr(TEXT(" \t\v\n\r\f"), c);
#endif
}

Exit strInitialize(String *&str, const Char *src) {
    Exit ec = str ? Exit::strInitialized : Exit::success;

    size_t length = 0;
    if (!src) {
        ec = Exit::strEmpty;
    }
    else if (isOk(ec)) {
        length = strlenImpl(src) + 1;
        ec = allocImpl(str);
    }

    if (isOk(ec)) {
        ec = allocImpl(str->memory, length);
    }

    if (isOk(ec)) {
        str->allocated = length;
        str->current = str->memory;
        str->end = str->current + length - 1;
        memcpy(str->current, src, length * sizeof(Char));
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
    size_t otherLength = 0;

    if (!other) {
        ec = Exit::strEmpty;
    }
    else if (isOk(ec)) {
        otherLength = strlenImpl(other);
        oldMemory = str->memory;
        ec = reallocImpl(str->memory, str->allocated + otherLength);
    }

    if (isOk(ec)) {
        size_t ptrDiff = str->memory - oldMemory;
        str->current += ptrDiff;
        str->end += ptrDiff;

        str->allocated += otherLength;
        memcpy(str->end, other, (otherLength + 1) * sizeof(Char));

        str->end += otherLength;
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
        while (p <= str->end && *w != '\0') {
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

        str->current = p;
    }

    return ec;
}

Exit strTrim(String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if(isOk(ec)) {
        while (str->current < str->end && isSpace(*str->current))
            str->current++;
        while (str->end >= str->current && isSpace(*str->end))
            str->end--;
        *(++str->end) = '\0';
    }

    return ec;
}

Exit strToNumber(Real &result, const String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;
    
    if (isOk(ec)) {
        Char *end = nullptr;
        result = strtodImpl(str->current, &end);
        ec = (end == str->current) ? Exit::strNAN : Exit::success;
    }

    return ec;
}

Exit strToNumber(int &result, const String *str) {
    Exit ec = str ? Exit::success : Exit::strUninitialized;

    if (isOk(ec)) {
        Char *end = nullptr;
        result = strtolImpl(str->current, &end, 10);
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
