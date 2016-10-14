#include "type.h"




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
    printf("%d %d\n", in->mousex, in->mousey);
  }
}

zombie init_default_zombie(){
  zombie z;
  z.rate_of_fire=0;
  z.health=0;
  z.damage=0;
  z.range=0;
  
  return z;
}

square init_default_square(){
  square s;
  s.obstacle=false; 
  s.occupied=false; 
  s.z=init_default_zombie();   

  return s;
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
  level->field[Y][X].z=init_default_zombie(); //default zombie is dead zombie
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
  

  
