// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#define _WIN32_WINNT _WIN32_WINNT_WIN2K
// _WIN32_WINNT_WIN7

// В новой версии компилятора от майкрософт они добавили тип std::byte, как положено по стандарту,
// но все библиотеки от них всё ещё используют их же тип, добавленный ранее byte.
// Чтобы компилятор не ругался, надо один из них отключить.
#define _HAS_STD_BYTE 0

#include <stdio.h>
#include <wchar.h>
#include <math.h>
// TODO: reference additional headers your program requires here
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Utils/StringEx.h"
#include <map>

#include <stdint.h>
#include <time.h>

using namespace std;

#define OUT
#define countof(a) (sizeof(a)/sizeof(*(a)))

