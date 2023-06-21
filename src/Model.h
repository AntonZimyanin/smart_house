#pragma once
#include "Utils/ConsoleManip.h"
#include "Utils/MusicContext.h"
#include "SmartObjects/_BaseObject.h"
#include "SmartObjects/_ObjectFactory.h"
using namespace std;


// хранит все "умные" датчики расположенные в данный момент на схеме

class CModel
{
private:
	vector<CBaseObject*> m_Objects; // объекты в порядке создания (должны отрисовываться в таком порядке)
public:
	// CMusicContext m_MusicContext;

	CModel();
	virtual ~CModel(); // virtual - на случай возможного дальнейшего расширения программы, в данный момент не используется, поскольку наследников этого класса нет

	// удалить все объекты
	void DestroyAll();
	// вывести схему расположения объектов на консоль
	bool DrawAll(CConsoleManip& console);

	bool Store(IStorer* pStorer);
	bool Load(ILoader* pLoader, CObjectFactory* pFactory);
	// найти объект по его имени (если нет такого - вернёт nullptr)
	CBaseObject* FindObject(const char* psName);
	// найти все объекты указанного типа
	// возвращает количество найденных объектов и заполняет найденными объектами контейнер
	size_t GetObjectsByType(const char* psTypeName, OUT vector<CBaseObject*>& pvFoundObjects);
	// найти все объекты поддерживающие указанный интерфейс
	// возвращает количество найденных объектов и заполняет найденными объектами контейнер
	template<class INTERFACE_TO_SEARCH>
	size_t GetObjectsByType(OUT vector<INTERFACE_TO_SEARCH*>& pvFoundObjects)
    {
        pvFoundObjects.clear();
        for (vector<CBaseObject*>::iterator pIter = m_Objects.begin(); pIter != m_Objects.end(); ++pIter)
        {
            INTERFACE_TO_SEARCH* pObj = dynamic_cast<INTERFACE_TO_SEARCH*>(*pIter);
            if (pObj)
                pvFoundObjects.push_back(pObj);
        }
        return pvFoundObjects.size();
    }

	// удалить объект с указанным именем
	// возвращает: true - Объект удалён
	//             false - такого объекта не было
	bool DeleteObject(const char* psName);
	// добавляет объект в контекст
	// возвращает: true - объект добавлен
	//             false - объект с таким именем уже существует
	bool AddObject(CBaseObject* pObj);

	// вывести на экран список объектов
	void PrintListOfObjects(CConsoleManip& console) const;
};

