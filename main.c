#include "SDL.h"
#include "type.h"



/* definition of global variables*/

SDL_Surface *grass,*student_base, *zombie_tab[5];

SDL_Rect rcgrass, rcstudent_base,rcstudent_baserc, rczombie_base, rczombie_baserc, draw;

int colorkey, i, j;

level current_level;


int main ()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Student versus Zombie", "Student versus Zombie");
  SDL_Surface* screen = SDL_SetVideoMode(1080, 630, 0, 0);
  SDL_Surface *temp;

/*grass init*/
  rcgrass.x=90;
  rcgrass.y=90;

/*load grass img*/
 temp=SDL_LoadBMP("fond3.bmp");
 grass=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

/*load monster*/
 temp=SDL_LoadBMP("zombie.bmp");
 zombie_tab[1]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("lich.bmp");
 zombie_tab[2]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 init_level(&current_level);

 colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
 SDL_SetColorKey(zombie_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(zombie_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  Input in;
  memset(&in, 0, sizeof(in));


  while (!in.key[SDLK_LAST] && !in.quit){
    UpdateEvents(&in);
    HandleEvents(&in);
    
    /*draw*/
    SDL_BlitSurface(grass,NULL,screen,&rcgrass);

    for (j=0;j<5;j++){
      for (i=0;i<10;i++){
	draw.x = 80+i*90;
	draw.y = 50+j*90;
	if (current_level.field[i][j].z.type > 0){
	  SDL_BlitSurface(zombie_tab[current_level.field[i][j].z.type], NULL, screen, &draw); 
	}
      }
    }
    
    
    
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  
  
  
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
