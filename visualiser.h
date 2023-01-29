#ifndef visualiser_h
#define visualiser_h

#include "langton.h" //langton.h included in the header file so that there is no need to include it in visualiser.c
#include <stdbool.h>

static int max_x;
static int max_y;

typedef enum colour cell;

void start_visualisation(struct ant* ant);
void visualise_and_advance(struct ant* ant);
void visualise_and_advance_general(struct ant* ant, struct rule* rule);
bool not_quit();
cell cell_at_fct(int y, int x); //optional
void end_visualisation();
const char* direction_to_s(enum direction d);

#endif
