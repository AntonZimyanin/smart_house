#include "../stdafx.h"
#include "ConsoleManip.h"
#include <iostream>
#include <assert.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

COORD CreateLocation(short x, short y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    return pos;
}

static const COORD g_InvalidLocation = CreateLocation(0, 0); // в случае ошибки будем возвращать нулевые координаты

CConsoleManip::CConsoleManip()
{
    InitConsole();
}


CConsoleManip::~CConsoleManip()
{
}

// проинициализировать размеры окна консоли
bool CConsoleManip::InitConsole()
{
    printf("\033[2J"); // очистить консоль

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    size.X = w.ws_col;
    size.Y = w.ws_row;

    return true;
    // m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    // if (m_hStdout == INVALID_HANDLE_VALUE)
    // {
    //     cout << "GetStdHandle failed with code " << GetLastError() << endl;
    //     return false;
    // }

    // // Get the screen buffer size.
    // if (!GetConsoleScreenBufferInfo(m_hStdout, &m_csbiInfo))
    // {
    //     cout << "GetConsoleScreenBufferInfoEx failed with code " << GetLastError() << endl;
    //     return false;
    // }
    // COORD maxSize = GetLargestConsoleWindowSize(m_hStdout);
    // maxSize.X -= 4; // резервируем место на экране под рамки окна (GetLargestConsoleWindowSize даёт в притык и даже чуть чуть не хватает на рамки)
    // maxSize.Y -= 2;
    // m_csbiInfo.dwSize = maxSize;
    // m_csbiInfo.srWindow.Top = 0;
    // m_csbiInfo.srWindow.Left = 0;
    // m_csbiInfo.srWindow.Bottom = m_csbiInfo.dwSize.Y - 1;
    // m_csbiInfo.srWindow.Right = m_csbiInfo.dwSize.X - 1;

    // if (!SetConsoleScreenBufferSize(m_hStdout, m_csbiInfo.dwSize))
    // {
    //     cout << "SetConsoleScreenBufferSize failed with code " << GetLastError() << endl;
    //     return false;
    // }
    // if (!SetConsoleWindowInfo(m_hStdout, TRUE, &m_csbiInfo.srWindow))
    // {
    //     cout << "SetConsoleWindowInfo failed with code " << GetLastError() << endl;
    //     return false;
    // }
    // return SetConsolePos(CommandLogOutputPos());
}

// получить размеры консольного окна и сохранить новые значения положения точки рисования и курсора ввода команд
bool CConsoleManip::ReinitConsoleSize()
{
    return true;
    // if (m_hStdout == INVALID_HANDLE_VALUE)
    //     return false;
    // if (!GetConsoleScreenBufferInfo(m_hStdout, &m_csbiInfo))
    //     return false;
    // m_csbiInfo.dwCursorPosition = CommandLogOutputPos();
    // return true;
}

// вернуть размер пространства для рисования
COORD CConsoleManip::DrawSpaceSize() const
{
    COORD pos = DrawSpacePos();
    pos.X = size.X - pos.X;
    pos.Y = size.Y - pos.Y - 1; // оставляем последнюю строчку и всю левую половину экрана пустыми
    return pos;
}

// вернуть позицию где отображается схема
COORD CConsoleManip::DrawSpacePos() const
{
    return CreateLocation( (short)(size.X / 2),
                           (short)0 );
}

// позиция на экране, в которой находится командная строка
COORD CConsoleManip::CommandLogOutputPos() const
{
    return CreateLocation( (short)0,
                           (short)((size.Y - 1)) );
}

// очистить область отображения схемы
void CConsoleManip::ClearDrawSpace()
{
    COORD size = DrawSpaceSize();
    stringEx spaces;
    spaces.resize(size.X, ' ');
    for (int i = 0; i < size.Y; i++)
        DrawText(0, i, spaces.c_str(), spaces.length());
}

size_t len(const wchar_t *str) {
  size_t len = 0;
  while (*str != L'\0') {
    len++;
    str++;
  }
  return len;
}


// вывести единственную строку текста в указанной позиции
// если строка выходит за пределы области рисования - вывести урезанную строку
bool CConsoleManip::DrawText(short x, short y,
                             const char* sText, uint length /* = UINT_MAX - use strlen*/,
                             Color crBackColor /*= enmColors::black*/,
                             Color crForeColor /*= enmColors::white*/)
{
    COORD spacePos = DrawSpacePos();
    COORD spaceSize = DrawSpaceSize();
    if (y < 0) // выше области рисования не выводим
        return true; // это нормальное поведение - не ошибка
    if (y >= spaceSize.Y) // ниже области рисования не выводим
        return true; // это нормальное поведение - не ошибка
    if (length == 1'000'000'000)
        length = strlen(sText);
    if (x < 0) // не выводим строку левее области рисования
    {
        sText += -x;
        length -= -x;
    }
    if ((int)length + x > spaceSize.X) // выход за правый край экрана
        length = spaceSize.X - x;
    if ((int)length <= 0) // вся строка выводится за пределами экрана
        return true; // это нормальное поведение - не ошибка
    if (!SetTextColor(crBackColor, crForeColor) ||
        !SetConsolePos(x + spacePos.X, y + spacePos.Y))
        return false;
    cout.write(sText, length);
    return true;
}

// вывести строку в указанной позиции области рисования
// строка может содержать несколько строк текста
// если строка выходит за область рисования - будет выведена урезанная строка
bool CConsoleManip::DrawTextMultiline(short x, short y,
                                      stringEx sText, Color crBackColor /*= enmColors::black*/,
                                                      Color crForeColor /*= enmColors::white*/)
{
    vector<stringEx> vWords = sText.Split("\n", false);
    bool res = true;
    for (size_t i = 0; i < vWords.size(); i++)
        res &= DrawText(x, static_cast<short>(y + i), vWords[i].c_str(), vWords[i].length(), crBackColor, crForeColor);
    return res;
}

bool CConsoleManip::SetConsolePos(short x, short y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
    return true;
}

bool CConsoleManip::SetConsolePos(const COORD& pos)
{
    return SetConsolePos(pos.X, pos.Y);
}

COORD CConsoleManip::GetConsolePos() const
{
    return {10, 10};
}

bool CConsoleManip::SetTextColor(Color crBackColor /*= enmColors::black*/,
                                 Color crForeColor /*= enmColors::light_gray*/)
{
    printf("\033[48;2;%d;%d;%dm", crBackColor.r, crBackColor.g, crBackColor.b);
    printf("\033[38;2;%d;%d;%dm", crForeColor.r, crForeColor.g, crForeColor.b);
    
    return true;
}


CConsoleManip& CConsoleManip::operator>>(int& val)
{
    cin >> val;
    return *this;
}

// Все действия в программе осуществляем в кодировке cp1251
// при вводе все строки конвертируются в неё, а при выводе конвертируются в DOS кодировку cp866
CConsoleManip& CConsoleManip::operator<<(const char* str)
{
    stringEx strEx(str);
    cout << strEx.ConvertToDos();
    return *this;
}

// конструктор перемещения позволяет сэкономить на создании лишней копии строки при выводе
CConsoleManip& CConsoleManip::operator<<(stringEx&& str)
{
    cout << str.ConvertToDos();
    return *this;
}

CConsoleManip& getline(CConsoleManip& console, OUT stringEx& str)
{
    getline(cin, OUT str);
    str.ConvertToWin();
    return console;
}
// сбросить флаг ошибки ввода
// и очистить буфер ввода
void CConsoleManip::ClearErrorFlag()
{
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
}
