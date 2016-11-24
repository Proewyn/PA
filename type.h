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
#define SIZE_SQUARE 90
#define BOTTOM_MENU 180
#define STUDENT_MAX 100
#define PROJECTILE_MAX 50
#define FPS 60

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
  Uint32 last_hit;
  int type;
}student;

typedef struct Zombie{
  int type;
  float rate_of_fire;
  int health;
  int damage;
  int range;
  Uint32 last_hit;
}zombie;

typedef struct Obstacle{
  int type;
  int health;
}obstacle;

typedef struct Projectile{
  int type;
  float speed;
  double posx;
  int posy;
  int damage;
  int effect;
  int area;
  int start;
  int range_max;
;
}projectile;

typedef struct Square{
  obstacle obstacle; //must init both of them in a function
  zombie z;
}square;

typedef struct Level{
  square** field;
  student* student_tab;
  projectile* projectile_tab;
  int money;
}level;

extern int highlight_menu;
extern level current_level;

/*declaration of function*/

void UpdateEvents(Input *in);
void HandleEvents(Input *in);
void init_zombie();
void init_obstacle();
int in_range_s(student s);
int in_range_z(int X, int Y);
int impact(projectile p);
void summon_student(student summon);
void launch_projectile(int num);
void suppr_projectile(int num_projectile);
void suppr_student(int num_student);
int path_block(int num_student);
void move_student();
void move_projectile();
void suppr_zombie(int X, int Y);
void suppr_obstacle(int X, int Y);
void attack(student attacker, int X);
void projectile_hit(projectile p, int X);
void attack_z(int defender, int X, int Y);
void init_level(int num_lvl);
int num_student_menu(int posX);
int num_case_x(int posX);
int num_case_y(int posY);
#endif
