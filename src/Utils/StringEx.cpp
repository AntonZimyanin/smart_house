#include "../stdafx.h"
#include "StringEx.h"
// #include <windows.h>
#include <ctype.h>

// разбить строку psText на слова
// psSeparators - список разделителей
// skipEmpty - не сохранять пустые строчки
// возвращает количество полученных слов
vector<stringEx> stringEx::Split(const char* psSeparators, bool skipEmpty /*= true*/)
{
    vector<stringEx> res;
    if (!length())
        return res;
    stringEx str; // не перевыделяем буфер для строки каждый раз - используем один и тот же(перевыделение происходит только если новая строка не помещается в выделенный ранее буфер)
    const char* psText = c_str();
    while (*psText)
    {
        const char* psNext = strpbrk(psText, psSeparators);
        if (!psNext)
        { // больше разделителей в строке нет, кроме того последнее слово точно не пустое, иначе бы не зашли в очередную итерацию цикла
            res.push_back(psText);  // сам определит длину строки
            break;
        }
        if (!skipEmpty || psNext - psText)
        {
            str.assign(psText, psNext - psText);
            res.push_back(str);
        }
        psText = psNext + 1;
    }
    return res;
}

// изменить регистр всех букв на нижний
stringEx& stringEx::strlwr()
{
    // функция strlwr - делает все буквы в строке прописными
    // не является частью стандарта С++, поэтому отсутствует в компиляторе GCC, а значит и в CodeBlocks
    // поэтому под CodeBlocks реализуем её вручную
    // на Microsoft VisualStudio есть реализация этой функции с модификацией: проверкой на длину буфера - поэтому там можно использовать эту библиотечную функцию

    // работает с русским языком только если выбрана соответсвующая локаль

    if (!length())
        return *this;
    char* psStr = &(*this)[0];// буфер, где лежат символы строки
    #ifdef _MSC_VER
        // microsoft VC
        _strlwr_s(psStr, length() + 1); // этой функции надо передавать размер буфера с концевым нулём
    #else
        // CodeBlocks + GCC
        while (*psStr)
        {
            *psStr = tolower(*psStr);
            psStr++;
        }
    #endif
    return *this;
}
// изменить регистр всех букв на верхний
stringEx& stringEx::strupr()
{
    // работает с русским языком только если выбрана соответсвующая локаль
    if (!length())
        return *this;
    char* psStr = &(*this)[0];// буфер, где лежат символы строки
    #ifdef _MSC_VER
        // microsoft VC
        _strupr_s(psStr, length() + 1); // этой функции надо передавать размер буфера с концевым нулём
    #else
        // CodeBlocks + GCC
        while (*psStr)
        {
            *psStr = toupper(*psStr);
            psStr++;
        }
    #endif
    return *this;
}

// сконвертировать строку из кодировки cp1251 (используем в IDE при наборе исходников)
// в cp866 (кодировку консоли)
stringEx& stringEx::ConvertToDos()
{
    if (!length())
        return *this;
    char* psStr = &(*this)[0];// буфер, где лежат символы строки
    // ::AnsiToOem(psStr, OUT psStr);
    return *this;
}
// сконвертировать строку из кодировки cp866 (кодировки консоли)
// в cp1251(используем в IDE при наборе исходников)
stringEx& stringEx::ConvertToWin()
{
    if (!length())
        return *this;;
    char* psStr = &(*this)[0];// буфер, где лежат символы строки
    // ::OemToAnsi(psStr, OUT psStr);
    return *this;
}
