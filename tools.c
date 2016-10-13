#include type.h
#include tools.h


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
  square.obstacle=false; 
  square.occupied=false; 
  square.zombie=init_default_zombie();   

  return s;
}



int in_range(student s,level level){
  int i;
  int beg = int(student.posx);
  int end = int(student.posx + student.range);
  for (i=beg;i<=end;i++){
    if (level.field[student.posy][i].obstacle==true){
      return -1;
    }
    else{if (level.field[student.posy][i].occupied==true){
      return i;
      }}
  }
  return -1;
}


int impact(projectile p, level l){
  if(level.field[p.posy][int(p.posx-0.5)]==occupied){
    return int(p.posx-0.5);
  }
  return -1;   //no impact
}


void summon_student(student summon, level *level){
  int i=0;
  while (level->student_tab[i].health !=0 and  i<=99){ //look for free pos in tab
    i++;
  }
  if (i<99){
    level->student_tab[i+1]=summon;
  }
}


void launch_projectile(projectile p,level *level){
  int i=0;
  while (level->projectile_tab[i].damage==0 and level->projectile_tab[i].effect==0 and i<=49){   //look for free pos in tab
    i++;
  }
  if (i<49){
    level->projectile_tab[i+1]=p;
  }
}

void suppr_projectile(int num_projectile,level *level){
  int i;
  for (i=num_projectile;i<49;i++){
    level->projectile_tab[i]=level.projectile_tab[i+1];
  }
  level->projectile_tab[49].damage=0;  //if damage and effect = 0
  level->projectile_tab[49].effect=0;  //projectile is considered null
}

void suppr_student(int num_student,level *level){
  int i;
  for (i=num_student;i<99;i++){
    level->student_tab[i]=level.student_tab[i+1];
  }
  level->student_tab[99].health = 0;
}


void move_student(level *level){
  int i=0;
  while (level->student_tab[i].health !=0 and  i<=99){
    level->student_tab[i].posx=level->student_tab[i].speed;
    i++;
  }
}

void attack(int attacker, int x, level *level){
  int result;
  
  result = level->field[level->student_tab[attacker].posy][x].z.health - level->student_tab[attacker].damage;
  if (result <= 0){
    suppr_zombie(int x, int attacker, level level);
  }
  else{
    level->field[level->student_tab[attacker].posy][x]z.health = result;
  }
}

void attack_z(int defender, int x, int y, level* level){
  int result;
  
  result = level->field[y][x].z.damage - level->student_tab[defender].health;
  if (result <= 0){
    suppr_student(int defender, level level);
  }
  else{
    level->student_tab[defender].health = result;
  }
}


void suppr_zombie(int X, int Y, level *level){
  level->field[Y][X].z=init_default_zombie(); //default zombie is dead zombie
}
  

  
