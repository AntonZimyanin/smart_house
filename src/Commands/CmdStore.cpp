#include "../stdafx.h"
#include "CmdStore.h"
#include <iostream>
#include <memory>
#include "../Context.h"
#include "../Storage/BinStorer.h"
#include "../Storage/TxtStorer.h"
using namespace std;

bool CCmdStore::Execute(CContext* pContext, vector<stringEx>& vParameters)
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
    unique_ptr<IStorer> pStorer;

    if (vParameters[0] == "bin")
        pStorer.reset(new CBinStorer(vParameters[1].c_str()));
    else
        pStorer.reset(new CTxtStorer(vParameters[1].c_str()));
    if (!*pStorer)
    {
        pContext->m_Console << "Указанный файл не найден" << endl;
        return false;
    }
    if (!pContext->m_ActiveModel.Store(pStorer.get()))
    {
        pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        pContext->m_Console << "Не удалось загрузить описание объектов из указанного файла" << endl <<
                               "Он повреждён или сохранён в другом формате" << endl <<
                               "Внимание: при загрузке текущая схема расположения объектов была очищена" << endl;
        pContext->m_ActiveModel.DestroyAll(); // удаляем частично загруженную схему расположения объектов
        return false;
    }
    pContext->m_Console << "Файл успешно сохранён" << endl;
    return true;
}