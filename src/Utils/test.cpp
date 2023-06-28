// #include "../libSDL/include/SDL_mixer.h"
// #include "../libSDL/include/SDL.h"




// int main(int argc, char** argv) {
//   // Initialize SDL and SDL_mixer
//   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//   Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

//   // Load the WAV file
//   Mix_Chunk* chunk = Mix_LoadWAV("m.wav");
//   if (chunk == NULL) {
//     printf("Failed to load WAV file: %s\n", Mix_GetError());
//     return 1;
//   }

//   // Play the WAV file
//   Mix_PlayChannel(-1, chunk, 0);

//   // Wait for the WAV file to finish playing
//   while (Mix_Playing(-1)) {
//     SDL_Delay(100);
//   }

//   // Close SDL and SDL_mixer
//   Mix_FreeChunk(chunk);
//   Mix_CloseAudio();
//   SDL_Quit();

//   return 0;
// }

