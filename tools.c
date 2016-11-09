#include "type.h"

bool is_select=false;


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
    if (in->mousey < BOTTOM_MENU){
      highlight_menu = num_student_menu(in->mousex);
      if (highlight_menu != 0){
	is_select = true;
      }
    }
    else{
      if (is_select){
	student student_temp;
	if (highlight_menu == 1){
	  student_temp.rate_of_fire = 1;
	  student_temp.cost = 10;
	  student_temp.health = 15;
	  student_temp.damage = 2;
	  student_temp.speed = 1;
	  student_temp.range = 1;
	  student_temp.posx = (double)num_case_x(in->mousex)*SIZE_SQUARE;
	  student_temp.posy = num_case_y(in->mousey);
	  summon_student(student_temp);
	}  
      }
    }
    int j,i;
    for(i=0;i<FIELD_Y;i++){
      for(j=0;j<FIELD_X;j++){
	printf("%d ",current_level.field[i][j].z.type);
      }
      printf("\n");
    }
    for(i=0;i<10;i++){
      printf("vie %d: %d \n",i,current_level.student_tab[i].health);
    }
    printf("%d %d\n", in->mousex, in->mousey);
  }
}

void init_zombie(){

  int i, j;

  for (j=0;j<FIELD_Y;j++){
    for (i=0;i<FIELD_X;i++){
      if (current_level.field[j][i].z.type == 0){
	current_level.field[j][i].z.rate_of_fire=0;
	current_level.field[j][i].z.health=0;
	current_level.field[j][i].z.damage=0;
	current_level.field[j][i].z.range=0;
      }
      else if (current_level.field[j][i].z.type == 1){
	current_level.field[j][i].z.rate_of_fire=2;
	current_level.field[j][i].z.health=20;
	current_level.field[j][i].z.damage=3;
	current_level.field[j][i].z.range=1;
      }
      else if (current_level.field[j][i].z.type == 2){
	current_level.field[j][i].z.rate_of_fire=3;
	current_level.field[j][i].z.health=10;
	current_level.field[j][i].z.damage=3;
	current_level.field[j][i].z.range=3;
      }
    }
  }
}

int in_range(student s){
  int i;
  int beg = (int)(s.posx)/SIZE_SQUARE;
  int end = (int)(s.posx)/SIZE_SQUARE + s.range;
  for (i=beg;i<=end;i++){
    if (i<FIELD_X){
      if (current_level.field[s.posy][i].obstacle==true){
	return -1;
      }
      else{if (current_level.field[s.posy][i].z.type!=0){
	  return i;
	}
      }
    }
  }
  return -1;
}


int impact(projectile p, level l){
  if(l.field[p.posy][(int)(p.posx-0.5)].z.type!=0){
    return (int)(p.posx-0.5);
  }
  return -1;   //no impact
}


void summon_student(student summon){
  int i=0;
  while (i<STUDENT_MAX && current_level.student_tab[i].health !=0){ //look for free pos in tab
    i++;
  }
  if (i<STUDENT_MAX-1){
    printf("%d \n",i);
    current_level.student_tab[i].rate_of_fire=summon.rate_of_fire;
    current_level.student_tab[i].cost=summon.cost;
    current_level.student_tab[i].health=summon.health;
    current_level.student_tab[i].damage=summon.damage;
    current_level.student_tab[i].speed=summon.speed;
    current_level.student_tab[i].range=summon.range;
    current_level.student_tab[i].posx=summon.posx;
    current_level.student_tab[i].posy=summon.posy;
    
  }
}


void launch_projectile(projectile p){
  int i=0;
  while (current_level.projectile_tab[i].damage==0 && current_level.projectile_tab[i].effect==0 && i<PROJECTILE_MAX){   //look for free pos in tab
    i++;
  }
  if (i<PROJECTILE_MAX-1){
    current_level.projectile_tab[i+1].speed=p.speed;
    current_level.projectile_tab[i+1].posx=p.posx;
    current_level.projectile_tab[i+1].posy=p.posy;
    current_level.projectile_tab[i+1].damage=p.damage;
    current_level.projectile_tab[i+1].effect=p.effect;

  }
}

void suppr_projectile(int num_projectile){
  int i;
  for (i=num_projectile;i<PROJECTILE_MAX;i++){
    current_level.projectile_tab[i]=current_level.projectile_tab[i+1];
  }
  current_level.projectile_tab[PROJECTILE_MAX-1].damage=0;  //if damage and effect = 0
  current_level.projectile_tab[PROJECTILE_MAX-1].effect=0;  //projectile is considered null
}

void suppr_student(int num_student){
  int i;
  for (i=num_student;i<STUDENT_MAX-1;i++){
    current_level.student_tab[i]=current_level.student_tab[i+1];
  }
  current_level.student_tab[STUDENT_MAX-1].health = 0;
}

void move_student(){
  int i=0;
  while (i<STUDENT_MAX && current_level.student_tab[i].health !=0 ){
    if (in_range(current_level.student_tab[i]) == -1){
      current_level.student_tab[i].posx=current_level.student_tab[i].posx + current_level.student_tab[i].speed;
    }
    i++;
  }
}

void suppr_zombie(int X, int Y){
  current_level.field[Y][X].z.type=0; //zombie 0 is dead zombie
}

void attack(int attacker, int X, level *level){
  int result;
  
  result = level->field[level->student_tab[attacker].posy][X].z.health - level->student_tab[attacker].damage;
  if (result <= 0){
    suppr_zombie(X, level->student_tab[attacker].posy);
  }
  else{
    level->field[level->student_tab[attacker].posy][X].z.health = result;
  }
}

void attack_z(int defender, int X, int Y, level* level){
  int result;
  
  result = level->field[Y][X].z.damage - level->student_tab[defender].health;
  if (result <= 0){
    suppr_student(defender);
  }
  else{
    level->student_tab[defender].health = result;
  }
}


void init_level(){
  int i,j;
  FILE* fichier = NULL;
  //char chaine[3]="";
  fichier = fopen("level1.txt", "r");
  int trash;

  if (fichier != NULL){
    for(j=0;j<FIELD_X;j++){
      for(i=0;i<FIELD_Y;i++){;
	current_level.field[i][j].obstacle=fgetc(fichier)-48; //-48 valeur ASCII=>int
	current_level.field[i][j].z.type=fgetc(fichier)-48;
	trash=fgetc(fichier); // récupére les \n et fais avancer le curseur à la ligne suivante
      }
    }
  }
  (void)trash;
  fclose(fichier);
}

int num_student_menu(int posX){
  int i;

  for(i=1;i<=1;i++){
    if (posX>(SIZE_SQUARE*(i+1)) && posX<(SIZE_SQUARE*(i+2))){
      return i;
    }
  }
  return 0;
}

int num_case_x(int posX){
  return (int)(posX-SIZE_SQUARE)/SIZE_SQUARE;
}

int num_case_y(int posY){
  return (int)(posY-BOTTOM_MENU)/SIZE_SQUARE;
}

void global_draw(){
}
