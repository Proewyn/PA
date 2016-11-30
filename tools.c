#include "type.h"

bool is_select=false;
int num_selected_level;


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
  int i;

  if (in->key[SDLK_ESCAPE]){
    in->key[SDLK_LAST] = 1;
  }
  if (in->mousebuttons[1]){
    in->mousebuttons[1]=0;
    if (menu_num == 0){  //main_menu
      if(in->mousex > 470 && in->mousex < 675){
	if(in->mousey > 385 && in->mousey < 412){
	  menu_num = 4; 
	  for(i=0;i<NB_LEVELS;i++){
	    progress[i][0]=0;
	    progress[i][1]=0;
	  }
	  save_progress();
	}
	if(in->mousey > 460 && in->mousey < 489){
	  menu_num = 4;
	}
	if(in->mousey > 539 && in->mousey < 565){
	  menu_num = 2;
	}
	if(in->mousey > 613 && in->mousey < 645){
	  in->quit=1;
	}
      }
    }
    if (menu_num == 2){// bestiary
      if(in->mousey > 683 && in->mousey < 700 && in->mousex > 50 && in->mousex < 195){
	menu_num = 0;
      }
    }
    if (menu_num == 3){ //end of game screen
      if (game_state == 1){ //victory
	if(in->mousey > 605 && in->mousey < 630){

	  /*save progression*/
	  progress[num_selected_level-1][0]=1;
	  progress[num_selected_level-1][1]=current_level.money;
	  save_progress();

	  if(in->mousex > 75 && in->mousex < 200){
	    menu_num = 4;
	  }
	  if(in->mousex > 900 && in->mousex < 990){
	    in->quit=1;
	  }
	}
      }else if(game_state == -1){ //defeat
	if(in->mousey > 610 && in->mousey < 630){
	  progress[num_selected_level-1][0]=1;
	  progress[num_selected_level-1][1]=current_level.money;
	  save_progress();

	  if(in->mousex > 35 && in->mousex < 145){
	    menu_num = 4;
	  }
	  if(in->mousex > 945 && in->mousex < 1025){
	    in->quit=1;
	  }
	}
      }
    }
    if (menu_num == 4){ //level_selection
      if(in->mousex > 360 && in->mousex < 444){
	if(in->mousey > 192 && in->mousey < 210){
	  init_level(1);
	  num_selected_level = 1;
	  init_zombie();
	  init_obstacle();
	  menu_num = 1;
	}
	if(in->mousey > 237 && in->mousey < 253){
	  init_level(2);
	  num_selected_level = 2;
	  init_zombie();
	  init_obstacle();
	  menu_num = 1;
	}
      }
    }
    if (menu_num == 1){  //game
      if (in->mousey > 660 && in->mousey < 680 && in->mousex > 15 && in->mousex < 205){
	menu_num = 0;
	is_select = false;
	highlight_menu = 0;
	for (i=0;i<STUDENT_MAX;i++){
	  current_level.student_tab[i].health=0;
	}
	for (i=0;i<PROJECTILE_MAX;i++){
	  current_level.projectile_tab[i].type=0;
	}
      }
      if (in->mousey < BOTTOM_MENU){
	highlight_menu = num_student_menu(in->mousex);
	if (highlight_menu != 0){
	  is_select = true;
	}
      }
      else{
	if (is_select){
	  if (in->mousey<BOTTOM_MENU+5*SIZE_SQUARE && in->mousex>SIZE_SQUARE && in->mousex<=2*SIZE_SQUARE){
	    student student_temp;
	    if (highlight_menu == 1){
	      student_temp.rate_of_fire = 1;
	      student_temp.cost = 10;
	      student_temp.health = 15;
	      student_temp.damage = 2;
	      student_temp.speed = 5;
	      student_temp.range = 1;
	      student_temp.posx = (double)num_case_x(in->mousex)*SIZE_SQUARE;
	      student_temp.posy = num_case_y(in->mousey);
	      student_temp.last_hit = 0;
	      student_temp.type = 1;
	    }else if(highlight_menu == 2){
	      student_temp.rate_of_fire = 2;
	      student_temp.cost = 10;
	      student_temp.health = 10;
	      student_temp.damage = 12;
	      student_temp.speed = 3;
	      student_temp.range = 3;
	      student_temp.posx = (double)num_case_x(in->mousex)*SIZE_SQUARE;
	      student_temp.posy = num_case_y(in->mousey);
	      student_temp.last_hit = 0;
	      student_temp.type = 2;
	    }else if(highlight_menu == 3){
	      student_temp.rate_of_fire = 5;
	      student_temp.cost = 10;
	      student_temp.health = 7;
	      student_temp.damage = 7;
	      student_temp.speed = 1;
	      student_temp.range = 2;
	      student_temp.posx = (double)num_case_x(in->mousex)*SIZE_SQUARE;
	      student_temp.posy = num_case_y(in->mousey);
	      student_temp.last_hit = 0;
	      student_temp.type = 3;
	    }else if(highlight_menu == 4){
	      student_temp.rate_of_fire = 5;
	      student_temp.cost = 10;
	      student_temp.health = 1;
	      student_temp.damage = 1;
	      student_temp.speed = 2;
	      student_temp.range = 2;
	      student_temp.posx = (double)num_case_x(in->mousex)*SIZE_SQUARE;
	      student_temp.posy = num_case_y(in->mousey);
	      student_temp.last_hit = 0;
	      student_temp.type = 4;
	    }
	    if( student_temp.cost <= current_level.money){
	      summon_student(student_temp);
	      current_level.money=current_level.money-student_temp.cost;
	    }
	  }
	}
      }
      printf("%d %d\n", in->mousex, in->mousey);
    }
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
	current_level.field[j][i].z.last_hit=0;
      }
      else if (current_level.field[j][i].z.type == 1){
	current_level.field[j][i].z.rate_of_fire=2;
	current_level.field[j][i].z.health=20;
	current_level.field[j][i].z.damage=3;
	current_level.field[j][i].z.range=1;
	current_level.field[j][i].z.last_hit=0;
      }
      else if (current_level.field[j][i].z.type == 2){
	current_level.field[j][i].z.rate_of_fire=2;
	current_level.field[j][i].z.health=10;
	current_level.field[j][i].z.damage=3;
	current_level.field[j][i].z.range=3;
	current_level.field[j][i].z.last_hit=0;
      }
    }
  }
}

void init_obstacle(){
  int i, j;
  for (j=0;j<FIELD_Y;j++){
    for (i=0;i<FIELD_X;i++){
      if (current_level.field[j][i].obstacle.type == 1){
	current_level.field[j][i].obstacle.health = 2;
      }
    }
  }
}
  

int in_range_s(student s){
  int i;
  int beg = (int)(s.posx)/SIZE_SQUARE;
  int end = (int)(s.posx)/SIZE_SQUARE + s.range;
  for (i=beg;i<=end;i++){
    if (i<FIELD_X){
      if(s.type!=4){
	if (current_level.field[s.posy][i].obstacle.type!=0){
	  return -1;
	}else{
	  if(current_level.field[s.posy][i].z.type!=0){
	    return i;
	  }
	}
      }
      else{
	if (current_level.field[s.posy][i].z.type!=0){
	  return -1;
	}else{
	  if (current_level.field[s.posy][i].obstacle.type!=0){
	    return i;
	  }
	}
      }
    }
  }
  return -1;
}

int in_range_z(int X, int Y){
  int num_student=-1, i=0;
  double distance = 2000;
  int beg = X*SIZE_SQUARE;
  int end = (X-current_level.field[Y][X].z.range)*SIZE_SQUARE;
  
  while (i<STUDENT_MAX && current_level.student_tab[i].health !=0){
    if (current_level.student_tab[i].posy == Y){
      if (current_level.student_tab[i].posx <= beg && current_level.student_tab[i].posx >= end){
	if (distance > X*SIZE_SQUARE - current_level.student_tab[i].posx){
	  distance = X*SIZE_SQUARE - current_level.student_tab[i].posx;
	  num_student = i;
	}
      }
    }
    i++;
  }
  return num_student;
}


int impact(projectile p){
  if(current_level.field[p.posy][(int)(p.posx/SIZE_SQUARE)].z.type!=0 && p.type!=3){
    return (int)(p.posx/SIZE_SQUARE);
  }
  if(current_level.field[p.posy][(int)(p.posx/SIZE_SQUARE)].obstacle.type!=0 && p.type==3){
    return (int)(p.posx/SIZE_SQUARE);
  }
  return -1;   //no impact
}


void summon_student(student summon){
  int i=0;
  while (i<STUDENT_MAX && current_level.student_tab[i].health !=0){ //look for free pos in tab
    i++;
  }
  if (i<STUDENT_MAX-1){
    current_level.student_tab[i].rate_of_fire=summon.rate_of_fire;
    current_level.student_tab[i].cost=summon.cost;
    current_level.student_tab[i].health=summon.health;
    current_level.student_tab[i].damage=summon.damage;
    current_level.student_tab[i].speed=summon.speed;
    current_level.student_tab[i].range=summon.range;
    current_level.student_tab[i].posx=summon.posx;
    current_level.student_tab[i].posy=summon.posy;
    current_level.student_tab[i].last_hit=summon.last_hit;
    current_level.student_tab[i].type=summon.type;    
  }
}


void launch_projectile(int num){
  int i=0;
  projectile p;
  if(current_level.student_tab[num].type==2){
    p.type=1;
    p.speed=5;
    p.posx=current_level.student_tab[num].posx+80;
    p.posy=current_level.student_tab[num].posy;
    p.damage=current_level.student_tab[num].damage;
    p.effect=0;
    p.area=0;
    p.start=(int)current_level.student_tab[num].posx+80;
    p.range_max=current_level.student_tab[num].range;
  }
  if(current_level.student_tab[num].type==3){
    p.type=2;
    p.speed=5;
    p.posx=current_level.student_tab[num].posx+80;
    p.posy=current_level.student_tab[num].posy;
    p.damage=current_level.student_tab[num].damage;
    p.effect=0;
    p.area=1;
    p.start=(int)current_level.student_tab[num].posx+80;
    p.range_max=current_level.student_tab[num].range;
  }
  if(current_level.student_tab[num].type==4){
    p.type=3;
    p.speed=3;
    p.posx=current_level.student_tab[num].posx+80;
    p.posy=current_level.student_tab[num].posy;
    p.damage=current_level.student_tab[num].damage;
    p.effect=0;
    p.area=0;
    p.start=(int)current_level.student_tab[num].posx+80;
    p.range_max=current_level.student_tab[num].range;
  }

  while (i<PROJECTILE_MAX && current_level.projectile_tab[i].type!=0){   //look for free pos in tab
    i++;
  }
  if (i<PROJECTILE_MAX-1){
    current_level.projectile_tab[i].type=p.type;
    current_level.projectile_tab[i].speed=p.speed;
    current_level.projectile_tab[i].posx=p.posx;
    current_level.projectile_tab[i].posy=p.posy;
    current_level.projectile_tab[i].damage=p.damage;
    current_level.projectile_tab[i].effect=p.effect;
    current_level.projectile_tab[i].area=p.area;
    current_level.projectile_tab[i].start=p.start;
    current_level.projectile_tab[i].range_max=p.range_max;
  }
}

void suppr_projectile(int num_projectile){
  int i;
  for (i=num_projectile;i<PROJECTILE_MAX;i++){
    current_level.projectile_tab[i]=current_level.projectile_tab[i+1];
  }
  current_level.projectile_tab[PROJECTILE_MAX-1].type=0;
}

void suppr_student(int num_student){
  int i;
  for (i=num_student;i<STUDENT_MAX-1;i++){
    current_level.student_tab[i]=current_level.student_tab[i+1];
  }
  current_level.student_tab[STUDENT_MAX-1].health = 0;
}

int path_block(int num_student){
  if(current_level.student_tab[num_student].posx>FIELD_X*SIZE_SQUARE){
    return false;
  }else{
    return current_level.field[current_level.student_tab[num_student].posy][(int)current_level.student_tab[num_student].posx/SIZE_SQUARE+1].obstacle.type;
  }
}
  

void move_student(){
  int i=0;
  double nextpos;
  while (i<STUDENT_MAX && current_level.student_tab[i].health !=0 ){
    if(current_level.student_tab[i].type!=4){
      if(in_range_s(current_level.student_tab[i]) == -1){
	nextpos=current_level.student_tab[i].posx + current_level.student_tab[i].speed;
	if (nextpos>FIELD_X*SIZE_SQUARE-45){
	  suppr_student(i);
	}else{
	  if(!path_block(i)!=0){
	    current_level.student_tab[i].posx=nextpos;
	  }
	}
      }
    }else{
      if(in_range_s(current_level.student_tab[i]) == -1){
	nextpos=current_level.student_tab[i].posx + current_level.student_tab[i].speed;
	if (nextpos>FIELD_X*SIZE_SQUARE-45){
	  suppr_student(i);
	}else{
	  current_level.student_tab[i].posx=nextpos;
	}
      }
    }
    i++;
  }
}

void move_projectile(){
  int i=0;
  double nextpos;	
  while (i<PROJECTILE_MAX && current_level.projectile_tab[i].type !=0 ){
    if(impact(current_level.projectile_tab[i]) == -1){
      nextpos=current_level.projectile_tab[i].posx + current_level.projectile_tab[i].speed;
      if (nextpos>FIELD_X*SIZE_SQUARE){
	suppr_projectile(i);
      }else{
	if(nextpos>current_level.projectile_tab[i].start+current_level.projectile_tab[i].range_max*SIZE_SQUARE){
	  suppr_projectile(i);
	}else{
	  current_level.projectile_tab[i].posx=nextpos;
	}
      }
    }	
    i++;
  }
}



void suppr_zombie(int X, int Y){
  current_level.field[Y][X].z.type=0; //zombie 0 is dead zombie
}

void suppr_obstacle(int X, int Y){
  current_level.field[Y][X].obstacle.type=0; //zombie 0 is dead zombie
}

void attack(student attacker, int X){
  int result;
  
  if(attacker.type!=4){
    result = current_level.field[attacker.posy][X].z.health - attacker.damage;
    if (result <= 0){
      suppr_zombie(X, attacker.posy);
    }
    else{
      current_level.field[attacker.posy][X].z.health = result;
    }
  }else{
    result = current_level.field[attacker.posy][X].obstacle.health - attacker.damage;
    if (result <= 0){
      suppr_obstacle(X, attacker.posy);
    }
    else{
      current_level.field[attacker.posy][X].obstacle.health = result;
    }
  }
}

void projectile_hit(projectile p, int X){
  int result;
  if(p.type==3){
    result = current_level.field[p.posy][X].obstacle.health - p.damage;
    if (result <= 0){
      suppr_obstacle(X, p.posy);
    }
    else{
      current_level.field[p.posy][X].obstacle.health = result;
    }
  }else{
    result = current_level.field[p.posy][X].z.health - p.damage;
    if (result <= 0){
      suppr_zombie(X, p.posy);
    }
    else{
      current_level.field[p.posy][X].z.health = result;
    }
    if(p.area == 1){
      if(p.posy-1>=0){
	result = current_level.field[p.posy-1][X].z.health - p.damage;
	if (result <= 0){
	  suppr_zombie(X, p.posy-1);
	}
	else{
	  current_level.field[p.posy-1][X].z.health = result;
	}
      }
      if(p.posy+1<FIELD_Y){
	result = current_level.field[p.posy+1][X].z.health - p.damage;
	if (result <= 0){
	  suppr_zombie(X, p.posy+1);
	}
	else{
	  current_level.field[p.posy+1][X].z.health = result;
	}
      }

      result = current_level.field[p.posy][X+1].z.health - p.damage;
      if (result <= 0){
	suppr_zombie(X+1, p.posy);
      }
      else{
	if(p.posx+2<FIELD_X){
	  current_level.field[p.posy][X+2].z.health = result;
	}
      }    
    }
  }
}

void attack_z(int defender, int X, int Y){
  int result;
  
  result = current_level.student_tab[defender].health - current_level.field[Y][X].z.damage;
  if (result <= 0){
    suppr_student(defender);
  }
  else{
    current_level.student_tab[defender].health = result;
  }
}


void init_level(int num_lvl){
  int i,j;
  FILE* fichier = NULL;
  char chaine[4];
  int trash;
  switch(num_lvl){
    case 1:
      fichier = fopen("level1.txt", "r");
      break;
    case 2:
      fichier = fopen("level2.txt", "r");
      break;
    default:
      break;
  }
  
  if (fichier != NULL){
    current_level.money=atoi(fgets(chaine,4*sizeof(char),fichier));
    trash=fgetc(fichier);
    for(j=0;j<FIELD_X;j++){
      for(i=0;i<FIELD_Y;i++){
	current_level.field[i][j].obstacle.type=fgetc(fichier)-48; //-48 valeur ASCII=>int
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

  for(i=1;i<=4;i++){
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

int etat(){
  int i, j, result=1;

  for(j=0;j<FIELD_X;j++){
    for(i=0;i<FIELD_Y;i++){
      if (current_level.field[i][j].z.type != 0){
	result = 0;
      }
    }
  }
  if (result == 0 && current_level.money<10 && current_level.student_tab[0].type == 0 && current_level.projectile_tab[0].type == 0){
    result = -1;
  }
  return result;
}

void global_move(){
  int pos_attack, i, j;
  
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
      projectile_hit(current_level.projectile_tab[i], pos_attack);
      suppr_projectile(i);
    }
    i++;
  } 
}

void read_save(){
  FILE* fichier = NULL;
  int trash,i;
  int donne[4]={0};
  
  fichier = fopen ("save.txt","r");
  
  if (fichier != NULL){
    for(i=0;i<NB_LEVELS;i++){
      fscanf(fichier,"%d %d",&donne[1], &donne[2]);
      progress[i][0]=donne[1];
      progress[i][1]=donne[2];
    }
  }
  (void)trash;
  fclose(fichier);
}

void save_progress(){
  FILE* fichier = NULL;
  int i;
  char c[4];
  
  fichier = fopen("save.txt","w");
  
  if (fichier != NULL){
    for(i=0;i<NB_LEVELS;i++){
      fputc(progress[i][0]+48,fichier);
      fputc(' ',fichier);
      sprintf(c,"%04d",progress[i][1]);
      fputs(c,fichier);
      fputc('\n',fichier);
    }
  }

  fclose(fichier);
}
