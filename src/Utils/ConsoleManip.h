#pragma once

#include "StringEx.h"
#include "Colors.h"
#include <functional>

struct COORD {
    int X;
    int Y;
};

class CConsoleManip
{
private:
    COORD size;
    // вывести единственную строку текста в указанной позиции
    // если строка выходит за пределы области рисования - вывести урезанную строку
    bool DrawText(short x, short y,
                  const char* sText, uint length = 1'000'000'000 /*- use strlen*/,
                  Color crBackColor = enmColors::black,
                  Color crForeColor = enmColors::white);

    CConsoleManip(const CConsoleManip&) = delete;
    void operator=(const CConsoleManip&) = delete;
public:
    CConsoleManip();
    ~CConsoleManip();
    // проинициализировать размеры окна консоли (развернуть консоль по максимуму на экран)
    bool InitConsole();
    // получить размеры консольного окна и положения точки рисования и курсора ввода команд
    bool ReinitConsoleSize();
    // вывести строку в указанной позиции области рисования
    // строка может содержать несколько строк текста
    // если строка выходит за область рисования - будет выведена урезанная строка
    bool DrawTextMultiline(short x, short y,
                           stringEx sText,
                           Color crBackColor = enmColors::black,
                           Color crForeColor = enmColors::white);
    bool SetConsolePos(short x, short y);
    bool SetConsolePos(const COORD& pos);
    COORD GetConsolePos() const;
    bool SetTextColor(Color crBackColor = enmColors::black,
                      Color crForeColor = enmColors::light_gray);
    COORD DrawSpaceSize() const; // размер пространства для рисования
    COORD DrawSpacePos() const; // вернуть позицию где отображается схема
    void ClearDrawSpace(); // очистить область отображения схемы

    COORD CommandLogOutputPos() const; // позиция на экране, в которой находится командная строка

    CConsoleManip& operator>>(int& val);
    template <class T>
    CConsoleManip& operator<<(T val)
    {
        cout << val;
        return *this;
    }
    // Все действия в программе осуществляем в кодировке cp1251
    // при вводе все строки конвертируются в неё, а при выводе конвертируются в DOS кодировку cp866
    CConsoleManip& operator<<(const char* str);

    // конструктор перемещения позволяет сэкономить на создании лишней копии строки при выводе
    CConsoleManip& operator<<(stringEx&& str);

    // разрешаем передавать в этот класс манипуляторы для cout
    CConsoleManip& operator<<(ostream& (*manipulyator)(ostream&))
    {
        cout << manipulyator;
        return *this;
    }

    // разрешаем передавать в этот класс манипуляторы для cin
    CConsoleManip& operator>>(istream& (*manipulyator)(istream&))
    {
        cin >> manipulyator;
        return *this;
    }
    // сбросить флаг ошибки ввода
    // и очистить буфер ввода
    void ClearErrorFlag();

    // проверка на ошибки ввода
    explicit operator bool() const
    {
        return (bool)cin;
    }
};

// Все действия в программе осуществляем в кодировке cp1251
// при вводе все строки конвертируются в неё, а при выводе конвертируются в DOS кодировку cp866
CConsoleManip& getline(CConsoleManip& console, OUT stringEx& str);
