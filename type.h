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
  zombie z;
}square;

typedef struct Level{
  square** field;
  student* student_tab;
  projectile* projectile_tab;
}level;

extern int highlight_menu;
extern level current_level;

/*declaration of function*/

void UpdateEvents(Input *in);
void HandleEvents(Input *in);
void init_zombie();
int in_range(student s);
int impact(projectile p, level l);
void summon_student(student summon);
void launch_projectile(projectile p);
void suppr_projectile(int num_projectile);
void suppr_student(int num_student);
void move_student();
void suppr_zombie(int X, int Y);
void attack(int attacker, int X, level *level);
void attack_z(int defender, int X, int Y, level *level);
void init_level();
int num_student_menu(int posX);
int num_case_x(int posX);
int num_case_y(int posY);
#endif
