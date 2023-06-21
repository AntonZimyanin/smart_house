#pragma once

#include <string.h>

using namespace std;
#define OUT

class stringEx : public string
{
public:
    stringEx()
    {}
    stringEx(const stringEx& str) : string(str)
    {}
    using string::string; // импортируем из родительского класса конструкторы из const char* и из const string&
    stringEx(string&& str) : string(str)
    {}
    stringEx(stringEx&& str) noexcept : string(str)
    {}
    using string::operator=;
    stringEx& operator=(const stringEx& str)
    {
        this->string::operator=(str);
        return *this;
    }
    // разбить строку psText на слова
    // psSeparators - список разделителей
    // skipEmpty - не сохранять пустые строчки
    vector<stringEx> Split(const char* psSeparators, bool skipEmpty = true);
    // изменить регистр всех букв на нижний
    stringEx& strlwr();
    // изменить регистр всех букв на верхний
    stringEx& strupr();

    // сконвертировать строку из кодировки cp1251 (используем в IDE при наборе исходников)
    // в cp866 (кодировку консоли)
    stringEx& ConvertToDos();
    // сконвертировать строку из кодировки cp866 (кодировки консоли)
    // в cp1251(используем в IDE при наборе исходников)
    stringEx& ConvertToWin();
};
