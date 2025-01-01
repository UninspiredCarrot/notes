#ifndef MAIN_H
#define MAIN_H

enum Action { NEW };

enum Type { TOPIC };

enum KEY { NAME };

typedef struct {
  enum KEY key;
  char value[64];
} Option;

typedef struct {
  enum Type type;
  enum Action action;
  int no_options;
  Option *options;
} Command;

Command *parse_command(int argc, char *argv[]);
void print_command(Command *command_ptr);

int cmd_topic(Command *command_ptr);

void fuck(void);

#endif
