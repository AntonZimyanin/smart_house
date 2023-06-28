// // #include "../libSDL/include/SDL_mixer.h"
// // #include "../libSDL/include/SDL.h"




// // int main(int argc, char** argv) {
// //   // Initialize SDL and SDL_mixer
// //   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
// //   Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

// //   // Load the WAV file
// //   Mix_Chunk* chunk = Mix_LoadWAV("m.wav");
// //   if (chunk == NULL) {
// //     printf("Failed to load WAV file: %s\n", Mix_GetError());
// //     return 1;
// //   }

// //   // Play the WAV file
// //   Mix_PlayChannel(-1, chunk, 0);

// //   // Wait for the WAV file to finish playing
// //   while (Mix_Playing(-1)) {
// //     SDL_Delay(100);
// //   }

// //   // Close SDL and SDL_mixer
// //   Mix_FreeChunk(chunk);
// //   Mix_CloseAudio();
// //   SDL_Quit();

// //   return 0;
// // }



// #include <unistd.h>
// #include <iostream>
// #include <cstdlib>
// #include <signal.h>
// using namespace std;
// // Define the function to be called when ctrl-c (SIGINT) is sent to process
// void signal_callback_handler(int signum) {
//    cout << "Caught signal " << signum << endl;
//    // Terminate program
//    exit(signum);
// }
// int main(){
//    // Register signal and signal handler
//    signal(SIGINT, signal_callback_handler);
//    while(true){
//       cout << "Program processing..." << endl;
//       sleep(1);
//    }
//    return EXIT_SUCCESS;
// }
