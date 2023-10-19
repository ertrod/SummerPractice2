#include "practice.h"

namespace practice
{
    BOOL DirectoryExists(const char* dirName) 
    { // проверка директории на налчие
    DWORD attribs = GetFileAttributesA(dirName);
        if (attribs == INVALID_FILE_ATTRIBUTES) {
            return false;
        }
        return (attribs & FILE_ATTRIBUTE_DIRECTORY);
    }
}