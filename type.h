#ifndef TYPE_H 
#define TYPE_H

#include "SDL.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FIELD_X 10
#define FIELD_Y 5

/*structures*/

typedef struct input{
  char key[SDLK_LAST+1];
  int mousex, mousey;
  char mousebuttons[8];
  char quit;
}Input;

typedef struct Student{
  float rate_of_fire;
  int cost;
  int health;
  int damage;
  float speed;
  int range;
  double posx;
  int posy;
}student;

typedef struct Zombie{
  int type;
  float rate_of_fire;
  int health;
  int damage;
  int range;
}zombie;

typedef struct Projectile{
  float speed;
  double posx;
  int posy;
  int damage;
  int effect;
}projectile;

typedef struct Square{
  bool obstacle; //must init both of them in a function
  bool occupied;
  zombie z;
}square;
  
typedef struct Level{
  square field[FIELD_Y][FIELD_X];
  student student_tab[100];
  projectile projectile_tab[50];
}level;

/*declaration of function*/

void UpdateEvents(Input *in);
void HandleEvents(Input *in);
void init_zombie(level *l);
int in_range(student s, level level);
int impact(projectile p, level l);
void summon_student(student summon, level *level);
void launch_projectile(projectile p,level *level);
void suppr_projectile(int num_projectile, level *level);
void suppr_student(int num_student,level *level);
void move_student(level *level);
void suppr_zombie(int X, int Y, level *level);
void attack(int attacker, int X, level *level);
void attack_z(int defender, int X, int Y, level *level);
void init_level(level *level);
#endif
