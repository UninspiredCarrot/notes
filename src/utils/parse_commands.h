#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct {
  char key[64];
  char value[255];
} Option;

typedef struct {
  char cmd[64];
  char type[64];
  int no_options;
  Option *options;
} Command;

Command *parse_command(int argc, char *argv[]);
void print_command(Command *command_ptr);
#endif
