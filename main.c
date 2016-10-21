#include "SDL.h"
#include "type.h"



/* definition of global variables*/

SDL_Surface *grass,*student_base, *zombie_sprite_tab[5], *student_sprite_tab[10];

SDL_Rect rcgrass, rcstudent_base,rcstudent_baserc, rczombie_base, rczombie_baserc, draw;

int colorkey, i, j, highlight_menu;

level current_level;


int main ()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Student versus Zombie", "Student versus Zombie");
  SDL_Surface* screen = SDL_SetVideoMode(1080, 720, 0, 0);
  SDL_Surface *temp;

/*load grass img*/
 temp=SDL_LoadBMP("fond3.bmp");
 grass=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

/* load student*/

 temp=SDL_LoadBMP("student.bmp");
 student_sprite_tab[1]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("student_select.bmp");
 student_sprite_tab[2]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

/*load monster*/
 temp=SDL_LoadBMP("zombie.bmp");
 zombie_sprite_tab[1]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("lich.bmp");
 zombie_sprite_tab[2]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
 SDL_SetColorKey(zombie_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(zombie_sprite_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

/*grass init*/
  rcgrass.x=90;
  rcgrass.y=180;

/*load menu student 1*/
  rcstudent_base.x=170;
  rcstudent_base.y=0;
  
  init_level(&current_level);

  Input in;
  memset(&in, 0, sizeof(in));


  while (!in.key[SDLK_LAST] && !in.quit){
    UpdateEvents(&in);
    HandleEvents(&in);
    
    /*draw*/
    SDL_BlitSurface(grass,NULL,screen,&rcgrass);
    if (highlight_menu == 1){
      SDL_BlitSurface(student_sprite_tab[2],NULL,screen,&rcstudent_base);
    }
    else{
      SDL_BlitSurface(student_sprite_tab[1],NULL,screen,&rcstudent_base);
    }

    for (j=0;j<5;j++){
      for (i=0;i<10;i++){
	draw.x = 80+i*90;
	draw.y = 140+j*90;
	if (current_level.field[i][j].z.type > 0){
	  SDL_BlitSurface(zombie_sprite_tab[current_level.field[i][j].z.type], NULL, screen, &draw); 
	}
      }
    }
    
    
    
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  
  
  
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
