#include "langton.h"
#include <string.h>
#include <stdio.h>
#include <ncursesw/ncurses.h> // ncurses included so that its functions can be used in the start function below

void start(){
    max_x = getmaxx(stdscr); // max_x is referenced, which is the full width of the screen
    max_y = getmaxy(stdscr); // max_y is referenced, which is the full height of the screen
    struct state *cells_general; // *cells_general referenced here in langton.c so that it can be used as it is a global variable defined in langton.h
}

void turn_left(struct ant *ant)
{
    switch (ant->direction) // Used a switch to change the direction of the ant. void turn_left(struct ant *ant) to be used when the ant is on a white square
    {
        case UP:
            ant->direction = LEFT;
            break;
        case LEFT:
            ant->direction = DOWN;
            break;
        case DOWN:
            ant->direction = RIGHT;
            break;
        case RIGHT:
            ant->direction = UP;
            break;
    }
}

void turn_right(struct ant *ant) // Used a switch to change the direction of the ant. void turn_right(struct ant *ant) to be used when the ant is on a black square
{
    switch (ant->direction)
    {
        case UP:
            ant->direction = RIGHT;
            break;
        case RIGHT:
            ant->direction = DOWN;
            break;
        case DOWN:
            ant->direction = LEFT;
            break;
        case LEFT:
            ant->direction = UP;
            break;
    }
}

void move_forward(struct ant *ant) { // When moving forward the ant will leave the screen if it goes beyond the screen's size. This function allows the ant to move while keeping the ant in the screen by making the screen have a topology of torus
    switch (ant->direction) { // In this switch the modulus operation was made used of. For example, if ant->y is equal to max_y then it goes back to 0, or if ant->y is at y-coordinate 0 and it goes more up then ant->y will equal max_y-1
        case UP:
            ant->y = (ant->y - 1 + max_y) % max_y;
            break;
        case LEFT:
            ant->x = (ant->x - 1 + max_x) % max_x;
            break;
        case DOWN:
            ant->y = (ant->y + 1) % max_y;
            break;
        case RIGHT:
            ant->x = (ant->x + 1) % max_x;
            break;
    }
}


void apply_rule(enum colour *colour, struct ant* ant) {
    *colour == WHITE ? turn_right(ant) : turn_left(ant); // if colour of the cell is white then make the ant turn right, otherwise make it turn left
    *colour = *colour == WHITE ? BLACK : WHITE; // if colour of the cell is equal to white then turn it to black, otherwise turn it to white
}

void apply_rule_general(enum colour *colour, struct ant *ant, struct rule *rule){ // For the advanced functionality
    int state = cells_general[(ant->y * max_x) + ant->x].current_state;  // Make state store the current state of the cell under the ant e.g. 0 (for state 0), 1 (for state 1)
    char transition_rule = rule->rules[state]; // Make transition_rule store the current rule applied to the cell depending on the value of state. For example, in LLR, if the state of the cell 1 then the value of transition_rule of that cell would be L

    transition_rule == 'L' ? turn_left(ant) : turn_right(ant); // If transition_rule is equal to L then make the ant turn left, otherwise turn right

    cells_general[(ant->y * max_x) + ant->x].current_state = state == (int)strlen(rule->rules)-1 ? 0 : state + 1; // The current state of the cell has to be incremented. If the state of cell is equal to the length of rule then set it to zero, otherwise increment it
}
