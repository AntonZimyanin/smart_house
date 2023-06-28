#include "../stdafx.h"
#include <iostream>
//#include <windows.h>
#include "MusicContext.h"
#include "ConsoleManip.h"
#include "../libSDL/include/SDL_mixer.h"
#include <filesystem>
#include "../libSDL/include/SDL.h"



 



int CMusicContext::testPlay()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Check if the WAV file exists
    // bool fileExists = SDL_FileExists("m.wav");
    // if (!fileExists) {
    //     printf("The WAV file does not exist.\n");
    //     return 1;
    // }

    // Get the current working directory
    string workingDir = SDL_GetBasePath();

    // Load the WAV file
    Mix_Chunk* chunk = Mix_LoadWAV((const char *)(workingDir+ "/m.wav").data());
    if (chunk == NULL) {
        printf(workingDir.data(), "%s\n\n");
        printf("Failed to load WAV file: %s\n", Mix_GetError());
        return 1;
    }

    // Play the WAV file
    Mix_PlayChannel(-1, chunk, 0);

    // Wait for the WAV file to finish playing
    while (Mix_Playing(-1)) {
        SDL_Delay(100);
    }

    // Close SDL and SDL_mixer
    Mix_FreeChunk(chunk);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}



// #include <stdint.h>
// #include <time.h>

// uint32_t get_milliseconds_since_boot() {
//   // Get the current time in milliseconds
//   time_t now = time(NULL);

//   // Convert the time to milliseconds
//   uint32_t milliseconds = (uint32_t)now * 1000;

//   return milliseconds;
// }



using namespace std;
    #pragma comment(lib, "../libSDL/libs_x86/SDL2_mixer.lib")
    #pragma comment(lib, "../libSDL/libs_x86/SDL2.lib")
    namespace fs = std::filesystem;
#ifdef _MSC_VER
    // microsoft VC
    // поддерживает указание Lib файлов в коде
    // через директиву компилятору #pragma comment

#else
    // CodeBlocks + GCC
    // не поддерживает #pragma comment
    // lib файлы прописываются в параметрах проекта
#endif

CMusicContext* g_pMusicContext = nullptr; // указатель на единственный CMusicContext в программе, 
                                          // к сожалению библиотека SDL позволяет указать только функцию без параметров в качестве обработчика события окончания проигрывания
                                          // поэтому приходится для передачи параметров в неё использовать глобальные переменные.

// обработчик события окончания проигрывания мелодии
void OnFinishMusicPlay()
{
    g_pMusicContext->OnFinishMusicPlay();
}

CMusicContext::CMusicContext()
    : m_pMusic(nullptr),
      m_isPlaying(false),
      m_isPaused(false),
      m_Volume(MIN_MAX_VOLUME),
      m_iCurFile(0),
      m_nMusicStartTime(0),
      m_nMusicPauseTime(0)
{
    ReloadMusicList();
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) // открыть устройство для воспроизведения мелодий
        cout << "Mix_OpenAudio: " << Mix_GetError() << endl;
    else if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)   // загрузить кодек воспроизведения MP3 (отдельная библиотека)
        cout << "Mix_Init: " << Mix_GetError() << endl;
    else
        Mix_VolumeMusic(m_Volume);
    Mix_HookMusicFinished(&::OnFinishMusicPlay); // регистрируем в библиотеке свою функцию, чтобы она вызвалась когда проигрывание текущей мелодии завершится
                                          // из-за ограничений библиотеки (нельзя передать в эту функцию параметр), приходится использовать глобальную переменную g_pMusicContext
    g_pMusicContext = this; // музыкальный контекст у нас присуствует в программе в единственном экземпляре
                            // передаём его в обработчик события окончания проигрывания мелодии через глобальную переменную(к сожалению SDL не принимает lambd'ы с захватом переменных)
}

CMusicContext::~CMusicContext()
{
    g_pMusicContext = nullptr;
    if (m_isPlaying)
        Mix_PauseMusic();
    if (m_pMusic)
        Mix_FreeMusic(reinterpret_cast<Mix_Music*>(m_pMusic));
    m_pMusic = nullptr;
    Mix_CloseAudio();
    Mix_Quit();
}

void CMusicContext::OnFinishMusicPlay()
{
    SelectNextFile();
    if (m_pMusic) // может оказаться, что мелодий нет на диске, запускаем только, если таковые есть
    {
        if (Mix_PlayMusic(reinterpret_cast<Mix_Music*>(m_pMusic), 1) == -1)
            return; // error
        time_t now = time(nullptr);

        m_nMusicStartTime = (uint32_t)(now) * 10000;
        m_isPlaying = true;
    }
}

bool CMusicContext::isPlaying()
{
    if (m_isPaused)
        return false;
    if (!m_isPlaying)
        return false;
    if (!Mix_PlayingMusic()) // обновим статус на случай если музыка уже доиграла
        m_isPlaying = false;
    return m_isPlaying;
}

bool CMusicContext::Play()
{
    // if (!m_pMusic) // файл не удаётся загрузить
    // {
    //     if (!ReloadCurFile())
    //         return false;
    //     if (!m_pMusic)
    //         return false;
    // }
    // if (m_isPaused)
    // {
    //     Mix_ResumeMusic();
    //     // корректируем время запуска мелодии чтобы по нему можно было отследить текущую проигрываемую позицию
    //     // m_nMusicStartTime += 0 - m_nMusicPauseTime;
    //     m_nMusicStartTime = 1 * 10;
    //     m_isPaused = false;
    //     return true;
    // }
    // if (m_isPlaying)
    // {
    //     if (Mix_PlayingMusic())
    //         return true;
    //     m_isPlaying = false;  // обновим статус на случай если музыка уже доиграла
    // }
    // if (Mix_PlayMusic(reinterpret_cast<Mix_Music*>(m_pMusic), 1) == -1) // повторить мелодию один раз, указание большего числа повторений не работает
    //     return false;
    // m_nMusicStartTime = 10;
    // m_isPlaying = true;
    // return true;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

  // Load the WAV file
  Mix_Chunk* chunk = Mix_LoadWAV("m.wav");
  if (chunk == NULL) {
    printf("Failed to load WAV file: %s\n", Mix_GetError());
    return 1;
  }

  // Play the WAV file
  Mix_PlayChannel(-1, chunk, 0);

  // Wait for the WAV file to finish playing
  while (Mix_Playing(-1)) {
    SDL_Delay(100);
  }

//   Close SDL and SDL_mixer
  Mix_FreeChunk(chunk);
  Mix_CloseAudio();
  SDL_Quit();
}

bool CMusicContext::Stop()
{
    if (!m_isPlaying)
        return true;
    if (m_isPaused)
        return true;
    if (!Mix_PlayingMusic()) // обновим статус на случай если музыка уже доиграла
        m_isPlaying = false;
    if (m_isPlaying)
    {
        Mix_PauseMusic();
        m_nMusicPauseTime = 0;
        m_isPaused = true;
        return true;
    }
    return true;
}

int CMusicContext::Volume() const
{
    return m_Volume;
}

void CMusicContext::Volume(int newVolume)
{
    m_Volume = max(0, min(newVolume, MIN_MAX_VOLUME));
    Mix_VolumeMusic(m_Volume);
}

// получить текущую позицию проигрывания мелодии в милисекундых
int CMusicContext::Position() const
{
    if (!m_isPlaying)
        return 0;
    if (m_isPaused)
        return m_nMusicPauseTime - m_nMusicStartTime;
    // мелодия сейчас проигрывается
    return 0;
}

void CMusicContext::Position(int newPositionMs)
{
    if (!m_isPlaying)
        return;
    Mix_SetMusicPosition(newPositionMs / 1000.0); // переводим в секунды
    // m_nMusicStartTime = GetTickCount() - newPositionMs;
    m_nMusicStartTime = 0;

    if (m_isPaused)
        m_nMusicPauseTime = 0;
}

const char g_sMediaID[] = "Media"; // признак, что далее идут настройки проигрывателя музыки в файле

bool CMusicContext::Store(IStorer* pStorer)
{
    return pStorer->Store(g_sMediaID) &&
           pStorer->Store(m_iCurFile) &&
           pStorer->Store(m_isPlaying) &&
           pStorer->Store(m_isPaused) &&
           pStorer->Store(Volume()) &&
           pStorer->Store(Position());
}
bool CMusicContext::Load(ILoader* pLoader)
{
    string id;
    if (!pLoader->Load(OUT id) ||
        id != g_sMediaID)
        return false;
    bool isPlaying = false;
    bool isPaused = false;
    int volume = MIN_MAX_VOLUME;
    int position = 0;
    if (!pLoader->Load(OUT m_iCurFile) || 
        !pLoader->Load(OUT isPlaying) ||
        !pLoader->Load(OUT isPaused) ||
        !pLoader->Load(OUT volume) ||
        !pLoader->Load(OUT position))
        return false;
    if (isPlaying)
    {
        Play();
        if (isPaused)
            Stop();
        Position(position);
    }
    Volume(volume);
    return true;
}

/// Обновить список доступных музыкальных композиций
void CMusicContext::ReloadMusicList()
{
    m_vsFiles.clear();
    m_vsFiles.push_back("m.wav");
    // fs::path musicPath("home/anton/smart_house/src/Music");
    // if (fs::exists(musicPath) && fs::is_directory(musicPath))
    // {
    //     for (auto const & entry : fs::recursive_directory_iterator(musicPath))
    //     {
    //         if (fs::is_regular_file(entry) && entry.path().extension() == ".mp3")
    //             m_vsFiles.push_back(entry.path().string());
    //     }
    // }
}



bool CMusicContext::ReloadCurFile()
{
    
    if (m_pMusic)
        UnloadCurFile();
    if (m_vsFiles.size() == 0)
    {
        m_iCurFile = 0;
        return false;
    }
    if (m_iCurFile < 0 || m_iCurFile >= (int)m_vsFiles.size())
        m_iCurFile = 0;
    
    for (unsigned int i = 0; i < m_vsFiles.size(); i++, m_iCurFile++) // перебираем все файлы, на случай наличия сбойных (неподдерживаемых) файлов
    {                                                   // пробуем максимум m_vsFiles.size() файлов
        if (m_iCurFile >= (int)m_vsFiles.size())
            m_iCurFile = 0;
        FILE* f = fopen("../Music/m.wav", "rb");
        if (!f)
        {
            cout << "Failed to open file: " << m_vsFiles[0].c_str() << endl;
            return false;
        }
        SDL_RWops* rwops = SDL_RWFromFile(m_vsFiles[0].c_str(), "rb");
        m_pMusic = Mix_LoadWAV_RW(rwops, 0);
        SDL_RWclose(rwops);
        if (m_pMusic)
            return true;
        cout << "Mix_LoadMUS: " << Mix_GetError() << endl;
    }

    return false;
}
void CMusicContext::UnloadCurFile()
{
    if (!m_pMusic) // файл уже выгружен
        return;
    Mix_FreeMusic(reinterpret_cast<Mix_Music*>(m_pMusic));
    m_pMusic = nullptr;
    m_isPlaying = false;
    m_isPaused = false;
}
// перейти к проигрыванию следующего файла
bool CMusicContext::SelectNextFile()
{
    bool isPlaying = m_isPlaying;
    UnloadCurFile();
    m_iCurFile++;
    if (!ReloadCurFile())
        return false;
    if (isPlaying)
        if (!Play())
            return false;
    return true;
}
// перейти к первому файлу
bool CMusicContext::SelectFirstFile()
{
    bool isPlaying = m_isPlaying;
    UnloadCurFile();
    m_iCurFile = 0;
    if (!ReloadCurFile())
        return false;
    if (isPlaying)
        if (!Play())
            return false;
    return true;
}

void CMusicContext::PrintAvailableMusics(CConsoleManip& cons) const
{
    int i = 1;
    for(const auto & s : m_vsFiles)
    {
        fs::path p = fs::path(s);
        cons << i << ") " << p.filename() << endl;
        i++;
    }
    cons << "Всего найдено: " << m_vsFiles.size() << " файл(ов)" << endl;
}