#include <stdio.h>
#include <stdlib.h>

#define LEFT 0
#define RIGHT 1

typedef struct {
  int pos;
  int zeros;
} Dial;

Dial create_dial() {
  return (Dial){.pos = 50, .zeros = 0};
}

int turn_right(Dial* dial, int amt) {
  dial->pos = (dial->pos + amt) % 100;
  dial->zeros += (dial->pos == 0) * 1;
  return dial->pos;
}

int turn_left(Dial* dial, int amt) {
  dial->pos = (dial->pos + (amt / 100 + 1) * 100 - amt) % 100;
  dial->zeros += (dial->pos == 0) * 1;
  return dial->pos;
}

int main() {
  FILE* input = fopen("input.txt", "r");
  if (!input) {
    printf("Could not open input.txt\n");
    return 1;
  }

  Dial dial = create_dial();

  char line[100];
  while (fgets(line, sizeof(line), input)) {
    const char* amtstr = &line[1];
    int amt = atoi(amtstr);

    int dir = (line[0] == 'R') * RIGHT;
    if (dir == LEFT) {
      turn_left(&dial, amt);
      printf("left %i, at %i\n", amt, dial.pos);
    } else if (dir == RIGHT) {
      turn_right(&dial, amt);
      printf("right %i, at %i\n", amt, dial.pos);
    }
  }

  printf("Zeros: %i\n", dial.zeros);

  return 0;
}
