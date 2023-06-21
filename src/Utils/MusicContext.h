#pragma once
/*
#include "../Storage/_Loader.h"
#include "../Storage/_Storer.h"
#include <vector>
using namespace std;

#define MIN_MAX_VOLUME 128

class CConsoleManip;

class CMusicContext
{
private:
    vector<string> m_vsFiles; // список доступных для воспроизведения файлов
    int m_iCurFile; // номер текущего проигрываемого файла в m_vsFiles
    void* m_pMusic; // дескриптор библиотеки SDL для текущей мелодии
    uint m_nMusicStartTime; // момент запуска мелодии, считается как количество милисекунд после включения компьютера
                             // этот способ используется поскольку билиотека SDL не позволяет получить текущую позицию проигрывания - считаем её сами от момента когда запустили проигрывание
    uint m_nMusicPauseTime; // момент когда поставили проигрывание на паузу

    bool m_isPlaying; // признак что мелодия была запущена на воспроизведение(при этом она может играть или стоять на паузе)
    bool m_isPaused; // не останавливаем воспроизведение, а ставим на паузу, чтобы после команды play продолжить с той же позиции
    int m_Volume;

    CMusicContext(const CMusicContext&) = delete;
    void operator=(const CMusicContext&) = delete;

    // перезагрузить список доступных мелодий
    // из каталога music
    bool ReloadCurFile();
    void UnloadCurFile();
    void OnFinishMusicPlay();        // приватная функция для обработчика событий с доступом ко всем приватным полям этого класса
    friend void OnFinishMusicPlay(); // статическая функция для передачи в качестве обработчика события в библиотеку SDL
public:
    CMusicContext();
    ~CMusicContext();
    bool isPlaying();
    bool Play();
    bool Stop();
    int Volume() const;
    void Volume(int newVolume);
    int Position() const; // текущая проигрываемая позиция мелодии в милисекундах
    void Position(int newPositionMs); // перемотать мелодию на указанную в милисекундах позицию
    bool SelectNextFile(); // перейти к проигрыванию следующего файла
    bool SelectFirstFile(); // перейти к первому файлу
    void PrintAvailableMusics(CConsoleManip& cons) const;
    void ReloadMusicList();

    bool Store(IStorer* pStorer);
    bool Load(ILoader* pLoader);
};

*/