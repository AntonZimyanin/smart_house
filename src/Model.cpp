#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <assert.h>

CModel::CModel() :
            m_Objects(),
            m_MusicContext()
{
}

CModel::~CModel()
{
	DestroyAll();
}

// удалить все объекты
void CModel::DestroyAll()
{
    for (vector<CBaseObject*>::iterator p = m_Objects.begin(); p != m_Objects.end(); ++p)
		delete *p;
	m_Objects.clear();
	m_MusicContext.Stop();
}

// перерисовать весь набор объектов и вывести приглашение для ввода следующей команды
bool CModel::DrawAll(CConsoleManip& console)
{
	if (!console.ReinitConsoleSize()) // пользователь мог изменить настройки окна вручную - переполучить новые размеры окна
		return false;
    console.ClearDrawSpace();
    for (vector<CBaseObject*>::iterator p = m_Objects.begin(); p != m_Objects.end(); ++p)
		(*p)->Draw(console);
	return true;
}

const char g_sContextFileID[] = "SmartHouseSchema"; // строка по которой будем идентифицировать свои файлы сохранения:
													// если первая строка в файле совпадает с этим образцом, то будем считать,
													// что он создан в нашей программе и имеет смысл его пытаться загружать
													// Если первая строка не совпадает, значит даже пытаться не стоит
bool CModel::Store(IStorer* pStorer)
{
	if (!pStorer->Store(g_sContextFileID))
		return false;
	if (!m_MusicContext.Store(pStorer))
		return false;
	if (!pStorer->Store(static_cast<int>(m_Objects.size())))
		return false;
	for (vector<CBaseObject*>::iterator pIter = m_Objects.begin(); pIter != m_Objects.end(); ++pIter)
		if (!(*pIter)->Store(pStorer))
			return false;
	return true;
}

bool CModel::Load(ILoader* pLoader, CObjectFactory* pFactory)
{
	DestroyAll();
	string id;
	if (!pLoader->Load(OUT id) ||
		g_sContextFileID != id)
		return false; // неверный идентификатор файла схемы объектов
	// при запуске проигрывания музыки выводится ошибка (где-то в исходниках SDL)
	// выведем её красным если она всё ещё выводится
	bool bLoadMusic = m_MusicContext.Load(pLoader);
	if (!bLoadMusic)
		return false;

	int cnt = 0;
	if (!pLoader->Load(cnt))
		return false;
	string str;
	for (int i = 0; i < cnt; i++)
	{
		if (!pLoader->Load(str))
			return false;
		CBaseObject* pObj = pFactory->CreateObject(str.c_str());
		if (!pObj)
			return false;
		if (!pObj->Load(pLoader))
		{
			delete pObj;
			return false;
		}
		if (!AddObject(pObj))
		{
			assert(false); // файл повреждён - содержит два объекта с одинаковыми именами
			delete pObj;
			return false;
		}
	}
	return true;
}

// найти объект по его имени (если нет такого - вернёт nullptr)
CBaseObject* CModel::FindObject(const char* psName)
{
	for (vector<CBaseObject*>::iterator pIter = m_Objects.begin(); pIter != m_Objects.end(); ++pIter)
	{
		if ((*pIter)->m_Name == psName)
			return *pIter;
	}
	return nullptr; // такой объект не найден
}

// найти все объекты указанного типа
// возвращает количество найденных объектов и заполняет найденными объектами контейнер
size_t CModel::GetObjectsByType(const char* psTypeName, OUT vector<CBaseObject*>& pvFoundObjects)
{
	pvFoundObjects.clear();
	for (vector<CBaseObject*>::iterator pIter = m_Objects.begin(); pIter != m_Objects.end(); ++pIter)
	{
		if (strcmp((*pIter)->Type(), psTypeName) == 0)
			pvFoundObjects.push_back(*pIter);
	}
	return pvFoundObjects.size();
}

// удалить объект с указанным именем
// возвращает: true - Объект удалён
//             false - такого объекта не было
bool CModel::DeleteObject(const char* psName)
{
	for (vector<CBaseObject*>::iterator pIter = m_Objects.begin(); pIter != m_Objects.end(); ++pIter)
	{
		if ((*pIter)->m_Name == psName)
		{
			delete *pIter;
			m_Objects.erase(pIter);
			return true;
		}
	}
	return false; // такой объект не найден
}
// добавляет объект в контекст
// возвращает: true - объект добавлен
//             false - объект с таким именем уже существует
bool CModel::AddObject(CBaseObject* pObj)
{
	for (vector<CBaseObject*>::iterator pIter = m_Objects.begin(); pIter != m_Objects.end(); ++pIter)
	{
		if ((*pIter)->m_Name == pObj->m_Name)
			return false; // такой объект уже существует
	}
	m_Objects.push_back(pObj);
	return true;
}

// вывести на экран список объектов
void CModel::PrintListOfObjects(CConsoleManip& console) const
{
    // выравниваем вывод, чтобы все имена начинались с одного и того же отступа
    unsigned int maxleng = 0; // максимальная длина имени команды
    for (vector<CBaseObject*>::const_iterator p = m_Objects.begin(); p != m_Objects.end(); ++p)
    {
        unsigned int curLeng = strlen((*p)->Type());
        maxleng = max(maxleng, curLeng);
    }
    for (vector<CBaseObject*>::const_iterator p = m_Objects.begin(); p != m_Objects.end(); ++p)
        console << "   "
                << setw(maxleng) << resetiosflags(ios::adjustfield) << setiosflags(ios::left)
                << (*p)->Type() << "   " << (*p)->m_Name << endl;
}
