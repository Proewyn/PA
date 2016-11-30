#include "SDL.h"
#include "type.h"

/* definition of global variables*/

SDL_Surface *grass,*fond, *barricade, *student_base, *zombie_sprite_tab[5], *student_sprite_tab[10], *projectile_sprite_tab[5], *number_tab[10], *defeat, *victory, *coin, *menu, *bestiaire, *select_lvl;

SDL_Rect rcgrass, rcstudent_baserc, rczombie_base, rczombie_baserc, draw, menu_student_tab[5], rcchiffre, rccoin;

int colorkey, i, j, highlight_menu, game_state, money_draw, money_tab[4], menu_num=0;

level current_level;

int progress[NB_LEVELS][2];


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
  
 /*load element*/
 temp=SDL_LoadBMP("img/menu.bmp");
 menu=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/select_lvl.bmp");
 select_lvl=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/bestiaire.bmp");
 bestiaire=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/fond3.bmp");
 grass=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/fond.bmp");
 fond=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/barricade.bmp");
 barricade=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/coin.bmp");
 coin=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/victory.bmp");
 victory=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/defeat.bmp");
 defeat=SDL_DisplayFormat(temp);
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

 temp=SDL_LoadBMP("img/nain2.bmp");
 student_sprite_tab[3]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/student_select2.bmp");
 student_sprite_tab[4]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/archer_select2.bmp");
 student_sprite_tab[5]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/mage_select2.bmp");
 student_sprite_tab[6]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 temp=SDL_LoadBMP("img/nain_select2.bmp");
 student_sprite_tab[7]=SDL_DisplayFormat(temp);
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

 temp=SDL_LoadBMP("img/bombe.bmp");
 projectile_sprite_tab[2]=SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);

 /*load number*/
 temp = SDL_LoadBMP("img/0.bmp");
 number_tab[0] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/1.bmp");
 number_tab[1] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/2.bmp");
 number_tab[2] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/3.bmp");
 number_tab[3] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/4.bmp");
 number_tab[4] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/5.bmp");
 number_tab[5] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/6.bmp");
 number_tab[6] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/7.bmp");
 number_tab[7] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/8.bmp");
 number_tab[8] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
 
 temp = SDL_LoadBMP("img/9.bmp");
 number_tab[9] = SDL_DisplayFormat(temp);
 SDL_FreeSurface(temp);
  
 colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
 SDL_SetColorKey(zombie_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(zombie_sprite_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[0], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 0, 249, 252));
 SDL_SetColorKey(student_sprite_tab[3], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 0, 254, 255));
 SDL_SetColorKey(student_sprite_tab[4], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[5], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 SDL_SetColorKey(student_sprite_tab[6], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 0, 249, 252));
 SDL_SetColorKey(student_sprite_tab[7], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 0, 254, 255));
 SDL_SetColorKey(projectile_sprite_tab[0], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 255, 255, 255));
 SDL_SetColorKey(projectile_sprite_tab[1], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 255, 255, 255));
 SDL_SetColorKey(projectile_sprite_tab[2], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 255, 255, 255));
 SDL_SetColorKey(barricade, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(screen->format, 255, 255, 255));
 SDL_SetColorKey(coin, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
 for (i = 0 ; i < 10 ; i++)
  {
    SDL_SetColorKey(number_tab[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  }
 
 /*grass init*/
 rcgrass.x=SIZE_SQUARE;
 rcgrass.y=BOTTOM_MENU;
 
 /*load menu student */
 for (i=0;i<8;i++){
   menu_student_tab[i].x=170+SIZE_SQUARE*i;
   menu_student_tab[i].y=0;
 }

 /*init progress from save_file*/
 read_save();

 rccoin.x=30;
 rccoin.y=50;

 rcchiffre.x=70;
 rcchiffre.y=45;
 
 Input in;
 memset(&in, 0, sizeof(in));
 
 while (!in.key[SDLK_LAST] && !in.quit){
   
   if((SDL_GetTicks() -frame_time)>=1000/FPS){ //limitation of FPS
     
     frame_time=SDL_GetTicks();
     UpdateEvents(&in);
     HandleEvents(&in);
     move_student();
     move_projectile();
     global_move();
     game_state = etat();

     if (menu_num == 0){
       SDL_BlitSurface(menu,NULL,screen,NULL);
     }
     if (menu_num == 2){
       SDL_BlitSurface(bestiaire,NULL,screen,NULL);
     }
     if (menu_num == 4){
       SDL_BlitSurface(select_lvl,NULL,screen,NULL);
     }
     if (menu_num == 1){
       if (game_state == 0){
	 /*global draw*/
	 SDL_BlitSurface(fond,NULL,screen,NULL);
	 SDL_BlitSurface(grass,NULL,screen,&rcgrass);
	 
	 /*draw menu*/
	 for (i=0;i<4;i++){
	   if (highlight_menu == i+1){
	     SDL_BlitSurface(student_sprite_tab[i+4],NULL,screen,&menu_student_tab[i]);
	   }else{
	     SDL_BlitSurface(student_sprite_tab[i],NULL,screen,&menu_student_tab[i]);
	   }
	 }
	 
	 money_draw = current_level.money;
	 i = 0;
	 while (money_draw != 0){
	   money_tab[3-i]=money_draw%10;
	   money_draw = (int)money_draw/10;
	   i++;
	 }
	 for (j=i; j<=3; j++){
	   money_tab[3-j]=0;
	 }
	 SDL_BlitSurface(coin, NULL, screen, &rccoin);
	 for (i=0; i<4; i++){
	   SDL_BlitSurface(number_tab[money_tab[i]], NULL, screen, &rcchiffre);
	   rcchiffre.x = rcchiffre.x+30;
	 }
	 rcchiffre.x = 70;
	 
	 /*draw zombie*/
	 for (j=0;j<FIELD_X;j++){
	   for (i=0;i<FIELD_Y;i++){
	     draw.x = 80+j*SIZE_SQUARE;
	     draw.y = 140+i*SIZE_SQUARE;
	     if (current_level.field[i][j].z.type > 0){
	       SDL_BlitSurface(zombie_sprite_tab[current_level.field[i][j].z.type], NULL, screen, &draw); 
	     }
	   }
	 }
	 
	 /*draw obstacle*/
	 for (j=0;j<FIELD_X;j++){
	   for (i=0;i<FIELD_Y;i++){
	     draw.x = 90+j*SIZE_SQUARE;
	     draw.y = 180+i*SIZE_SQUARE;
	     if (current_level.field[i][j].obstacle.type != 0){
	       SDL_BlitSurface(barricade, NULL, screen, &draw); 
	     }
	   }
	 }
	 
	 /*draw student*/
	 i = 0;
	 while (i<STUDENT_MAX && current_level.student_tab[i].health != 0){
	   draw.y=140+(current_level.student_tab[i].posy)*SIZE_SQUARE;
	   draw.x=80+current_level.student_tab[i].posx;
	   SDL_BlitSurface(student_sprite_tab[current_level.student_tab[i].type-1], NULL, screen, &draw);
	   i++;
	 }
	 
	 /*draw projectile*/
	 i=0;
	 while(i<PROJECTILE_MAX && current_level.projectile_tab[i].type!=0){
	   draw.y=200+(current_level.projectile_tab[i].posy)*SIZE_SQUARE;
	   draw.x=90+current_level.projectile_tab[i].posx;
	   SDL_BlitSurface(projectile_sprite_tab[current_level.projectile_tab[i].type-1], NULL, screen, &draw);
	   i++;
	 }
       }else{
	 printf("game state:%d\n", game_state);
	 if (game_state == 1){
	   menu_num = 3;
	   SDL_BlitSurface(victory, NULL, screen, NULL);
	 }else{
	   menu_num = 3;
	   SDL_BlitSurface(defeat, NULL, screen, NULL);
	 }
       }
     }
     SDL_UpdateRect(screen, 0, 0, 0, 0);     
   }
 }
 
 SDL_Quit();
 
 return EXIT_SUCCESS;
}
