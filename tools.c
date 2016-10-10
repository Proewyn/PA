#include type.h
#include tools.h

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



void suppr_projectile(int num_projectile,level *level){
  int i;
  for (i=num_projectile;i<49;i++){
    level.projectile_tab[i]=level.projectile_tab[i+1];
  }
  level.projectile_tab[49].damage=0;  //if damage and effect = 0
  level.projectile_tab[49].effect=0;  //projectile is considered null
}
