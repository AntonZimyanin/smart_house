#include "stdafx.h"
#include "Context.h"
#include <iostream>
#include <assert.h>
#include <windows.h>
#include "Utils/StringEx.h"
#include "Storage/BinLoader.h"
#include "Storage/TxtLoader.h"
#include "Storage/BinStorer.h"
#include "Storage/TxtStorer.h"
using namespace std;

CContext::CContext()
    : m_bExiting(false),
      m_ActiveModel(),
      m_Console(),
      m_ObjFactory(),
      m_Commands()
{
}

CContext::~CContext()
{}
