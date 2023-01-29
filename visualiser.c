#include <ncursesw/ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include "langton.h"
#include "visualiser.h"

#define cell_at(y, x) cells[(y * max_x) + x]
#define cell_under_ant cells[(ant->y * max_x) + ant->x]

struct state *cells_general; // referencing cells_general so that it can be used in visualiser.c

cell *cells;

void start_visualisation(struct ant* ant) {
  setlocale(LC_ALL, "");

   initscr();

   curs_set(FALSE);
   max_x = getmaxx(stdscr);
   max_y = getmaxy(stdscr);
   cells = calloc(max_y*max_x, sizeof(cell));
   cells_general = malloc(max_y*max_x * sizeof(struct state)); 
   for(int i=0; i<max_y*max_x; i++)
   {
      cells_general[i].current_state = 0; // Setting every element in the array cell_general to 0, its default value
   }
   ant->x = max_x/2;
   ant->y = max_y/2;
   ant->direction = UP;
   start(); // Initializing the neccessary variables in langotn.c
}


void visualise_and_advance(struct ant* ant) {
      /* Draw cells and ant */
      for (int y=0; y<max_y; y++)
      {
         for (int x=0; x<max_x; x++)
         {
            mvprintw(y,x,ant_is_at(y,x)
                 ? direction_to_s(ant->direction)
                 : cell_at(y,x)
                    ? "█"
                    : " "
            );
         }
      }
      refresh();
      
      
      /* Advance to next step */
      apply_rule(&cell_under_ant, ant);
      move_forward(ant);
}

void visualise_and_advance_general(struct ant* ant, struct rule* rule) {
      /* Draw cells and ant */
      
      for (int y = 0; y < max_y; y++) {
         for (int x = 0; x < max_x; x++) {
            if (ant->y == y && ant->x == x) {
            mvprintw(y, x, direction_to_s(ant->direction));
            } else {
               if(cells_general[(y * max_x) + x].current_state == 0){
                  mvprintw(y, x, " "); // If the current state of the cell is zero then no color is applied " "
               }else{
                  attron(COLOR_PAIR(cells_general[(y * max_x) + x].current_state-1));
                  mvprintw(y, x,"█"); // Otherwise, if the current state of the cell is greater than zero then color is applied on "█"
                  attroff(COLOR_PAIR(cells_general[(y * max_x) + x].current_state-1));
               }
               }
         }
      }
      refresh();
      
      /* Advance to next step */
      apply_rule_general(&cell_under_ant, ant, rule);
      move_forward(ant);
}

// Check if the user has input "q" to quit
bool not_quit() {
   return 'q' != getch();
}

void end_visualisation() {
   free(cells); 
   free(cells_general);
   endwin();
}

const char* direction_to_s(enum direction d) {
   return UP   == d ? "^" :
          DOWN == d ? "v" :
          LEFT == d ? "<" :
          /* else */  ">" ;
}

