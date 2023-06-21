#include "../stdafx.h"
#include "CmdDemo.h"
#include "../Context.h"
#include "../SmartObjects/RoomObject.h"
#include "../SmartObjects/DoorObject.h"
#include "../SmartObjects/LampObject.h"

bool CCmdDemo::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() > 0)
    {
        pContext->m_Console << "Неподдерживаемый параметр команды" << endl;
        return false;
    }
    pContext->m_ActiveModel.DestroyAll();
    pContext->m_Console.ReinitConsoleSize(); // перечитаем размер консольного окна
    COORD size = pContext->m_Console.DrawSpaceSize();
    // создаём большую комнату - максимального доступного на экране размера
    CRoomObject* pBigRoom = nullptr;
    bool res = true;
    if (size.X < 10 || size.Y < 10) // если места мало - больше ничего не добавляем
    {
        pBigRoom = new CRoomObject("room", 0, 0, size.X - 1, size.Y - 1);
        return pContext->m_ActiveModel.AddObject(pBigRoom);
    }
    pBigRoom = new CRoomObject("room", 2, 2, size.X - 5, size.Y - 5); // оставляем зазоры для дверей открывающихся наружу
    res &= pContext->m_ActiveModel.AddObject(pBigRoom);
    // добавляем меньшую комнату снизу справа (если достаточно для неё места)
    CRoomObject* pSmallRoom = nullptr;
    if (pBigRoom->Width() > 23 && size.Y > 18)
    {
        pSmallRoom = new CRoomObject("roomsmall", pBigRoom->X() + pBigRoom->Width() - 19,
                                                  pBigRoom->Y() + pBigRoom->Height() - 8,
                                                  19, 8);
        res &= pContext->m_ActiveModel.AddObject(pSmallRoom);
    }

    // добавляем двери ( если достаточно для них места )
    if (pBigRoom->Height() >= 8) // левая стенка
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door1", pBigRoom->X(), pBigRoom->Y() + 5, enmDirection::left, false));

    if (pBigRoom->Width() >= 13) // верхняя стенка
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door2", pBigRoom->X() + (pBigRoom->Width() - 4) / 2, 2, enmDirection::up, false));

    if (pBigRoom->Height() - (pSmallRoom ? pSmallRoom->Height() : 0) >= 9) // правая стенка
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door3", pBigRoom->X() + pBigRoom->Width(), pBigRoom->Y() + 5, enmDirection::right, false));

    if (pSmallRoom)
    {
        // внутренняя дверь в комнату (если есть внутреняя комната)
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door4", pBigRoom->X() + pBigRoom->Width() - 6, pSmallRoom->Y(), enmDirection::up, false));
        // дверь из внутренней комнаты наружу
        res &= pContext->m_ActiveModel.AddObject(new CDoorObject("door5", pBigRoom->X() + pBigRoom->Width() - 6, pSmallRoom->Y() + pSmallRoom->Height(), enmDirection::up, false));
    }
    // светильники
    // два в большой комнате
    if (size.X >= 13)
        res &= pContext->m_ActiveModel.AddObject(new CLampObject("lamp1", pBigRoom->X() + 4, pBigRoom->Y() + 2, false));
    if (size.X >= 17)
        res &= pContext->m_ActiveModel.AddObject(new CLampObject("lamp2", pBigRoom->X() + pBigRoom->Width() - 4, pBigRoom->Y() + 2, false));
    // один в маленькой
    if (pSmallRoom)
        res &= pContext->m_ActiveModel.AddObject(new CLampObject("lamp3", pSmallRoom->X() + 4, pSmallRoom->Y() + 2, false));
    pContext->m_ActiveModel.m_MusicContext.ReloadMusicList();
    pContext->m_ActiveModel.m_MusicContext.SelectFirstFile();
    pContext->m_ActiveModel.m_MusicContext.Stop();
    pContext->m_Console << "Демонстационная схема создана" << endl;
    return res;
}