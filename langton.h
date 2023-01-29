#ifndef langton_h
#define langton_h

enum direction { UP, DOWN, LEFT, RIGHT };

struct ant
{
    int x;
    int y;
    enum direction direction;
};

struct rule
{
    char* rules;
};

struct state{ // State which will be used as a second version of cell (enum colour) to check the current state of the cell
    int current_state;
};
extern struct state *cells_general; // cell_general defined in langton.h as global variable

#define ant_is_at(posy, posx) ((ant->y == (posy)) && (ant->x == (posx))) // Checks wether ant is at coordinates (posy, posx)

enum colour { WHITE, BLACK };

// max_x and max_y defined so that they can be used in langton.c
static int max_x; 
static int max_y;

void turn_left(struct ant *ant);
void turn_right(struct ant *ant);
void move_forward(struct ant *ant);

void apply_rule(enum colour *colour, struct ant *ant);
void apply_rule_general(enum colour *colour, struct ant *ant, struct rule *rule);

void start();


#endif
