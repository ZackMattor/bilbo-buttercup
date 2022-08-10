#include <stdio.h>
#include <unistd.h>
#include "./map_data.h"

struct Entity {
  int x;
  int y;
};

struct GameState {
  char floor;
  Entity player;
};

void change_floor(GameState *state, char floor) {
  state->floor = floor;

  printf("looking for spawn!");
  // Determine where to spawn the player
  for(int y=0; y<MAP_SIZE; y++) {
    for(int x=0; x<MAP_SIZE; x++) {
      if(map_data[floor][y][x] == 2) {
        printf("found spawn!");
        state->player.x = x;
        state->player.y = y;
      }
    }
  }
}

void output(char *chars) {
  printf(chars);
}

void print_map(char map[20][20], Entity p) {
  for(int y=0; y<MAP_SIZE; y++) {
    for(int x=0; x<MAP_SIZE; x++) {
      if(p.x == x && p.y == y) {
        output("a");
      } else {
        switch(map[y][x]) {
          case 0:
          case 2:
            output(" ");
            break;
          case 1:
            output("#");
            break;
          default:
            output("X");
            break;
        }
      }
    }
    output("\n");
  }
}

int main() {
  GameState *state = new GameState();
  change_floor(state, 0);

  while(1) {
    output("\n");
    printf("Floor %i\n", state->floor+1);
    print_map(map_data[state->floor], state->player);

    int input = getchar();
    printf("Input: %i\n", input);

    char cx = 0;
    char cy = 0;

    // Parse user input
    switch(input) {
      case 'w':
        cy--;
        break;
      case 'a':
        cx--;
        break;
      case 's':
        cy++;
        break;
      case 'd':
        cx++;
        break;
    }

    // Determine what to do depending on the tile the user lands on
    char next_tile = map_data[state->floor][state->player.y + cy][state->player.x + cx];
    printf("Next Time: %i\n", next_tile);
    switch(next_tile) {
      case 2:
      case 0:
        state->player.x += cx;
        state->player.y += cy;
        break;
      default:
        if(next_tile >= 100 && next_tile <= (100 + NUM_FLOORS)) {
          change_floor(state, next_tile - 100);
        }
        break;
    }
  }

  return 0;
}
