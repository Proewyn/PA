#include "SDL.h"
#include "type.h"



/* definition of global variables*/

SDL_Surface *grass,*student_base,*zombie_base;

SDL_Rect rcgrass, rcstudent_base,rcstudent_baserc, rczombie_base, rczombie_baserc;

int colorkey;



int main ()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Student versus Zombie", "Student versus Zombie");
  SDL_Surface* screen = SDL_SetVideoMode(1920, 1080, 0, 0);
  SDL_Surface *temp;

/*grass init*/
  rcgrass.x=10;
  rcgrass.y=50;


/*load grass img*/
 temp=SDL_LoadBMP("fond2.bmp");
 grass=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);


 colorkey = SDL_MapRGB(screen->format, 255, 0, 255);


  Input in;
  memset(&in, 0, sizeof(in));



  while (!in.key[SDLK_LAST]){
    UpdateEvents(&in);
    if (in.key[SDLK_ESCAPE]){
      in.key[SDLK_LAST] = 1;
    }





    /*draw the grass*/
    SDL_BlitSurface(grass,NULL,screen,&rcgrass);
  
  
  
  SDL_UpdateRect(screen, 0, 0, 0, 0);

  }
  

  
  SDL_Quit();
  
  return 0;
}
