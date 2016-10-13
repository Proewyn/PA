#include "SDL.h"
#include "type.h"

int main ()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Student versus Zombie", "Student versus Zombie");
  SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, 0);

  Input in;
  memset(&in, 0, sizeof(in));

  while (!in.key[SDLK_LAST]){
    UpdateEvents(&in);
    handle
    if (in.key[SDLK_ESCAPE]){
      in.key[SDLK_LAST] = 1;
    }
  }
  
  SDL_UpdateRect(screen, 0, 0, 0, 0);
  
  SDL_Quit();
  
  return 0;
}
