#include "type.h"

int highlight_menu;


void UpdateEvents(Input* in)
{
  SDL_Event event;

  while(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_KEYDOWN:
      in->key[event.key.keysym.sym]=1;
      break;
    case SDL_KEYUP:
      in->key[event.key.keysym.sym]=0;
      break;
    case SDL_MOUSEMOTION:
      in->mousex=event.motion.x;
      in->mousey=event.motion.y;
      break;
    case SDL_MOUSEBUTTONDOWN:
      in->mousebuttons[event.button.button]=1;
      break;
    case SDL_MOUSEBUTTONUP:
      in->mousebuttons[event.button.button]=0;
      break;
    case SDL_QUIT:
      in->quit=1;
      break;
    }
  }
}

void HandleEvents(Input *in){
  if (in->key[SDLK_ESCAPE]){
    in->key[SDLK_LAST] = 1;
  }
  if (in->mousebuttons[1]){
    in->mousebuttons[1]=0;
    highlight_menu = num_student_menu(in->mousex);
    printf("%d %d\n", in->mousex, in->mousey);
  }
}

void init_zombie(level *l){

  int i, j;

  for (j=0;j<=9;j++){
    for (i=0;i<=4;i++){
      if (l->field[j][i].z.type == 0){
	l->field[j][i].z.rate_of_fire=0;
	l->field[j][i].z.health=0;
	l->field[j][i].z.damage=0;
	l->field[j][i].z.range=0;
      }
      else if (l->field[FIELD_Y][FIELD_X].z.type == 1){
	l->field[j][i].z.rate_of_fire=2;
	l->field[j][i].z.health=20;
	l->field[j][i].z.damage=3;
	l->field[j][i].z.range=1;
      }
      else if (l->field[FIELD_Y][FIELD_X].z.type == 2){
	l->field[j][i].z.rate_of_fire=3;
	l->field[j][i].z.health=10;
	l->field[j][i].z.damage=3;
	l->field[j][i].z.range=3;
      }
    }
  }
}


int in_range(student s,level level){
  int i;
  int beg = (int)(s.posx);
  int end = (int)(s.posx) + s.range;
  for (i=beg;i<=end;i++){
    if (level.field[s.posy][i].obstacle==true){
      return -1;
    }
    else{if (level.field[s.posy][i].occupied==true){
      return i;
      }}
  }
  return -1;
}


int impact(projectile p, level l){
  if(l.field[p.posy][(int)(p.posx-0.5)].occupied==true){
    return (int)(p.posx-0.5);
  }
  return -1;   //no impact
}


void summon_student(student summon, level *level){
  int i=0;
  while (level->student_tab[i].health !=0 && i<=99){ //look for free pos in tab
    i++;
  }
  if (i<99){
    level->student_tab[i+1]=summon;
  }
}


void launch_projectile(projectile p,level *level){
  int i=0;
  while (level->projectile_tab[i].damage==0 && level->projectile_tab[i].effect==0 && i<=49){   //look for free pos in tab
    i++;
  }
  if (i<49){
    level->projectile_tab[i+1]=p;
  }
}

void suppr_projectile(int num_projectile,level *level){
  int i;
  for (i=num_projectile;i<49;i++){
    level->projectile_tab[i]=level->projectile_tab[i+1];
  }
  level->projectile_tab[49].damage=0;  //if damage and effect = 0
  level->projectile_tab[49].effect=0;  //projectile is considered null
}

void suppr_student(int num_student,level *level){
  int i;
  for (i=num_student;i<99;i++){
    level->student_tab[i]=level->student_tab[i+1];
  }
  level->student_tab[99].health = 0;
}


void move_student(level *level){
  int i=0;
  while (level->student_tab[i].health !=0 && i<=99){
    level->student_tab[i].posx=level->student_tab[i].speed;
    i++;
  }
}

void suppr_zombie(int X, int Y, level *level){
  level->field[Y][X].z.type=0; //zombie 0 is dead zombie
}

void attack(int attacker, int X, level *level){
  int result;
  
  result = level->field[level->student_tab[attacker].posy][X].z.health - level->student_tab[attacker].damage;
  if (result <= 0){
    suppr_zombie(X, level->student_tab[attacker].posy, level);
  }
  else{
    level->field[level->student_tab[attacker].posy][X].z.health = result;
  }
}

void attack_z(int defender, int X, int Y, level* level){
  int result;
  
  result = level->field[Y][X].z.damage - level->student_tab[defender].health;
  if (result <= 0){
    suppr_student(defender, level);
  }
  else{
    level->student_tab[defender].health = result;
  }
}

void init_level(level *level){
  int i,j;
  FILE* fichier = NULL;
  //char chaine[3]="";
  fichier = fopen("level1.txt", "r");
  int trash;

  if (fichier != NULL){
    for(j=0;j<5;j++){
      for(i=0;i<10;i++){;
	level->field[i][j].obstacle=fgetc(fichier)-48; //-48 valeur ASCII=>int
	level->field[i][j].occupied=fgetc(fichier)-48;
	level->field[i][j].z.type=fgetc(fichier)-48;
	trash=fgetc(fichier); // récupére les \n et fais avancer le curseur à la ligne suivante
      }
    }
  }
  fclose(fichier);
}

int num_student_menu(int posX){
  int i;

  for(i=1;i<=1;i++)
    if (posX>(90*(i+1)) && posX<(90*(i+2))){
	  return i;
  }
  return 0;
}

int num_case_x(int posX){
  return (int)(posX-90)/90;
}

int num_case_y(int posY){
  return (int)(posY-180)/90;
}
