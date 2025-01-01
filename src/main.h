#ifndef MAIN_H
#define MAIN_H

enum Action { NEW };

enum Type { TOPIC, PROBLEM };

enum KEY { NAME, URL };

enum DIFFICULTY { EASY, MEDIUM, HARD };

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

struct Leetcode_Question {
  char link[255];
  char questionID[255];
  char questionTitle[255];
  enum DIFFICULTY difficulty;
  char questionHTML[5000];
};

Command *parse_command(int argc, char *argv[]);
void print_command(Command *command_ptr);

int cmd_topic(Command *command_ptr);
int cmd_problem(Command *command_ptr);
void fuck(void);

#endif
