#include "SDL.h"
#include "type.h"

/* definition of global variables*/

SDL_Surface *grass,*student_base, *zombie_sprite_tab[5], *student_sprite_tab[10], *projectile_sprite_tab[5];

SDL_Rect rcgrass,rcstudent_baserc, rczombie_base, rczombie_baserc, draw, menu_student_tab[5];

int colorkey, i, j, highlight_menu;

level current_level;


int main ()
{
  current_level.field=(square**)malloc(FIELD_Y*sizeof(square*));
  for (i=0;i<FIELD_Y;i++){
    current_level.field[i]=(square*)malloc(FIELD_X*sizeof(square));
  }
  current_level.student_tab=(student*)malloc(STUDENT_MAX*sizeof(student));
  current_level.projectile_tab=(projectile*)malloc(PROJECTILE_MAX*sizeof(projectile));
  
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Student versus Zombie", "Student versus Zombie");
  SDL_Surface* screen = SDL_SetVideoMode(1080, 720, 0, 0);
  SDL_Surface *temp;
  Uint32 frame_time = 0;
  
  /*load grass img*/
 temp=SDL_LoadBMP("img/fond3.bmp");
 grass=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 /* load student*/
 
 temp=SDL_LoadBMP("img/student2.bmp");
 student_sprite_tab[0]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp=SDL_LoadBMP("img/archer2.bmp");
 student_sprite_tab[1]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/mage2.bmp");
 student_sprite_tab[2]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/student_select2.bmp");
 student_sprite_tab[3]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/archer_select2.bmp");
 student_sprite_tab[4]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/mage_select2.bmp");
 student_sprite_tab[5]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
  
 /*load monster*/
 temp=SDL_LoadBMP("img/zombie.bmp");
 zombie_sprite_tab[1]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp=SDL_LoadBMP("img/lich.bmp");
 zombie_sprite_tab[2]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

/*load projectile*/
temp=SDL_LoadBMP("img/fleche.bmp");
projectile_sprite_tab[0]=SDL_DisplayFormat(temp);
SDL_FreeSurface(temp);

temp=SDL_LoadBMP("img/fireball.bmp");
projectile_sprite_tab[1]=SDL_DisplayFormat(temp);
SDL_FreeSurface(temp);
 
 colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
 SDL_SetColorKey(zombie_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(zombie_sprite_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[0], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 0, 249, 252));
 SDL_SetColorKey(student_sprite_tab[3], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[4], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[5], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 0, 249, 252));
 SDL_SetColorKey(projectile_sprite_tab[0], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 255, 255, 255));
 SDL_SetColorKey(projectile_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 255, 255, 255));
 
 /*grass init*/
 rcgrass.x=SIZE_SQUARE;
 rcgrass.y=BOTTOM_MENU;
 
 /*load menu student */
 for (i=0;i<6;i++){
   menu_student_tab[i].x=170+SIZE_SQUARE*i;
   menu_student_tab[i].y=0;
 }
 
 init_level();
 init_zombie();
 
 int pos_attack;
 Input in;
 memset(&in, 0, sizeof(in));
 
 while (!in.key[SDLK_LAST] && !in.quit){

   if((SDL_GetTicks() -frame_time)>=1000/FPS){ //limitation of FPS
   
     frame_time=SDL_GetTicks();
     UpdateEvents(&in);
     HandleEvents(&in);
     move_student();
     move_projectile();

     i=0;
     while (i<STUDENT_MAX && current_level.student_tab[i].health != 0){
       pos_attack = in_range_s(current_level.student_tab[i]);
       if (pos_attack != -1){
	 if(SDL_GetTicks()-current_level.student_tab[i].last_hit >= current_level.student_tab[i].rate_of_fire*1000){
	   current_level.student_tab[i].last_hit = SDL_GetTicks();
	   if(current_level.student_tab[i].type==1){
	     printf("cac\n");
	     attack(current_level.student_tab[i], pos_attack);
	   }else{
	     printf("ranged\n");
	     launch_projectile(i);
	   }
	 }
       }
       i++;
     }
     
     i=0;
     while (i<PROJECTILE_MAX && current_level.projectile_tab[i].type != 0){
       pos_attack = impact(current_level.projectile_tab[i]);
       if(pos_attack != -1){
	 printf("pos_attack: %d\n",pos_attack);
	 projectile_hit(current_level.projectile_tab[i], pos_attack);
	 suppr_projectile(i);
       }
       i++;
     }
     
     for (j=0;j<FIELD_X;j++){
       for (i=0;i<FIELD_Y;i++){
	 if (current_level.field[i][j].z.type != 0){
	   pos_attack = in_range_z(j, i);
	   if (pos_attack != -1){
	     if (SDL_GetTicks()-current_level.field[i][j].z.last_hit >= current_level.field[i][j].z.rate_of_fire*1000){
	       current_level.field[i][j].z.last_hit = SDL_GetTicks();
	       printf("zombie\n");
	       attack_z(pos_attack, j, i);
	     }
	   }
	 }
       }
     }
     
     /*draw*/
     SDL_BlitSurface(grass,NULL,screen,&rcgrass);
     
     for (i=0;i<3;i++){
       if (highlight_menu == i+1){
	 SDL_BlitSurface(student_sprite_tab[i+3],NULL,screen,&menu_student_tab[i]);
       }else{
	 SDL_BlitSurface(student_sprite_tab[i],NULL,screen,&menu_student_tab[i]);
       }
     }
     
     
     
     for (j=0;j<FIELD_X;j++){
       for (i=0;i<FIELD_Y;i++){
	 draw.x = 80+j*SIZE_SQUARE;
	 draw.y = 140+i*SIZE_SQUARE;
	 if (current_level.field[i][j].z.type > 0){
	   SDL_BlitSurface(zombie_sprite_tab[current_level.field[i][j].z.type], NULL, screen, &draw); 
	 }
       }
     }
     
     i = 0;
     while (i<STUDENT_MAX && current_level.student_tab[i].health != 0){
       draw.y=140+(current_level.student_tab[i].posy)*SIZE_SQUARE;
       draw.x=80+current_level.student_tab[i].posx;
       SDL_BlitSurface(student_sprite_tab[current_level.student_tab[i].type-1], NULL, screen, &draw);
       i++;
     }
     
     i=0;
     while(i<PROJECTILE_MAX && current_level.projectile_tab[i].type!=0){
       draw.y=180+(current_level.projectile_tab[i].posy)*SIZE_SQUARE;
       draw.x=90+current_level.projectile_tab[i].posx;
       SDL_BlitSurface(projectile_sprite_tab[current_level.projectile_tab[i].type-1], NULL, screen, &draw);
       i++;
     }
     
     
     SDL_UpdateRect(screen, 0, 0, 0, 0);
     
   }
 }
 
 
 
 SDL_Quit();
 
 return EXIT_SUCCESS;
}
