#include "../stdafx.h"
#include "CmdLoad.h"
#include <iostream>
#include <memory>
#include "../Context.h"
#include "../Storage/BinLoader.h"
#include "../Storage/TxtLoader.h"
using namespace std;

bool CCmdLoad::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0 ||
        (vParameters[0] != "bin" && vParameters[0] != "txt"))
    {
        pContext->m_Console << "Не указан формат файла: bin - бинарный или txt - текстовый" << endl;
        return false;
    }
    if (vParameters.size() == 1)
    {
        pContext->m_Console << "Не указано имя файла" << endl;
        return false;
    }
    if (vParameters.size() > 2)
    {
        pContext->m_Console << "Неподдерживаемый параметр команды" << endl;
        return false;
    }

    // используем умный указатель, чтобы не контролировать вручную время жизни, чтобы delete вызвался автоматически
    unique_ptr<ILoader> pLoader;
    
    if (vParameters[0] == "bin")
        pLoader.reset(new CBinLoader(vParameters[1].c_str()));
    else
        pLoader.reset(new CTxtLoader(vParameters[1].c_str()));
    if (!*pLoader)
    {
        pContext->m_Console << "Указанный файл не найден" << endl;
        return false;
    }
	// Костыль: в глубине библиотеки SDL при запуске мелодии на воспроизведение может выдаваться ошибка
	// отобразим её красным, на воспроизведение она не влияет
	// учитывая что CModel не должен ничего выдавать на экран при воспроизведении (поскольку не взаимодействует с консолью, а только возвращает ошибку)
	// то изменение цвета выводимого текста тут будет влиять только на вывод ошибки в SDL
	pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
	bool bOk = pContext->m_ActiveModel.Load(pLoader.get(), &pContext->m_ObjFactory);
	pContext->m_Console.SetTextColor(); // цвет текста по умолчанию
    if (!bOk)
    {
        pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        pContext->m_Console << "Не удалось загрузить описание объектов из указанного файла" << endl <<
                               "Он повреждён или сохранён в другом формате" << endl <<
                               "Внимание: при загрузке текущая схема расположения объектов была очищена" << endl;
        pContext->m_ActiveModel.DestroyAll(); // удаляем частично загруженную схему расположения объектов
        return false;
    }
    pContext->m_Console << "Файл успешно загружен" << endl;
    return true;
}