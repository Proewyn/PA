#ifndef TYPE_H 
#define TYPE_H

#include "SDL.h"
#include <math.h>
#include <stdbool.h>
#include <time.h>

#define FIELD_X 15
#define FIELD_Y 5

/*structures*/

typedef struct student{
  float rate_of_fire;
  int cost;
  int health;
  int damage;
  float speed;
  int range;
  double posx;
  int posy;
}student;

typedef struct zombie{
  float rate_of_fire;
  int health;
  int damage;
  int range;
}zombie;

typedef struct projectile{
  float speed;
  double posx;
  int posy;
  int damage;
  int effect;
}projectile;

typedef struct square{
  bool obstacle; //must init both of them in a function
  bool occupied;
  zombie z;
}square;
  
typedef struct level{
  square field[FIELD_Y][FIELD_X];
  student student_tab[100];
  projectile projectile_tab[50];
}level;

/*declaration of function*/

zombie init_default_zombie();
square init__default_square();
int in_range(student s, level level);
int impact(projectile p, level l);
void summon_student(student summon, level *level);
void launch_projectile(projectile p,level *level);
void suppr_projectile(int num_projectile, level *level);
void suppr_student(int num_student,level *level);
void move_student(level *level);
void attack(student *attacker, int X, level *level);
void attack_z(student *defender, int X, level *level);
void suppr_zombie(int X, int Y, level *level);

  
#endif
