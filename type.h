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
}student;

typedef struct zombie{
  float rate_of_fire;
  int health;
  float speed;
  int damage;
  int range;
  double posx;
}zombie;

typedef struct projectile{
  float speed;
  double posx;
  int damage;
  int effect;
}projectile;

typedef struct square{
  bool hidden=false;
  bool occupied=false;
  student dude;
}square;
  
typedef struct level{
  square field[FIELD_Y][FIELD_X];
  zombie zom_line1[10];
  zombie zom_line2[10];
  zombie zom_line3[10];
  zombie zom_line4[10];
  zombie zom_line5[10];
  projectile proj_line1[20];
  projectile proj_line2[20];
  projectile proj_line3[20];
  projectile proj_line4[20];
  projectile proj_line5[20];
}level;
  
#endif
