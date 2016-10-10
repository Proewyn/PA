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
  int posy
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
  bool obstacle=false;
  bool occupied=false;
  zombie z;
}square;
  
typedef struct level{
  square field[FIELD_Y][FIELD_X];
  student student_tab[100];
  projectile projectile_tab[50];
}level;
  
#endif
