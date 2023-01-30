#include <stdio.h>
#include "langton.h"
#include "visualiser.h"
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <ncursesw/ncurses.h>

struct rule* rule; // rule is defined from the struct rule in langton.h

void handle_keyboard_interrupt() {
    end_visualisation();
    free(rule); // Memory of rule is freed at the end of the program
    printf("Keyboard interrupt. Exiting program");
    exit(0);
}

int main(int argc, char** argv) {
  signal(SIGINT, handle_keyboard_interrupt); // handle_keyboard_interrupt function to be called when a SIGINT signal is received

  rule = (struct rule*) malloc(sizeof(struct rule)); // Dynamically allocating memory to rule

  if (argc > 1) { // Checking if there is more than one argument, where the first argument is the name of the file
      for (int j = 0; j < (int)strlen(argv[1]); j++) { // If a second argument is present then it checked for any invalid character (not L or R) using a for loop which checks every character 
          if (argv[1][j] != 'L' && argv[1][j] != 'R') {
              printf("Invalid input. Exiting program\n");
              free(rule); // Memory of rule is freed at the end of the program
              exit(0);
          }
      }
      
      rule->rules = argv[1]; // rules, which is a memember variable of the struct rule which is defined in langton.h, is appointed the value of the second argument
  }
  struct ant ant;
  
  start_visualisation(&ant);

  if(rule->rules){ // If there is a second argument, where in this case it is stored in the rule->rules then run the while loop for the advanced functionality, else the while loop for basic functionality
    start_color();
    use_default_colors(); // Set terminal's background to its default background
    for(int i = 0; i < (int)strlen(rule->rules)-1; i++) // Only colours pairs that are needed are initialized 
    {
        init_pair(i, i, COLOR_WHITE);
    }
    while (not_quit()) {
      visualise_and_advance_general(&ant, rule); // A second function similar to visualise_and_advance was created, however it also takes as an argument rule so that it can be made used of
    }
  }else{
    while (not_quit()) {
      visualise_and_advance(&ant);
    }
  }

  free(rule); // Memory of rule is freed at the end of the program
  end_visualisation();
  return 0;
}
