#include "main.h"
#include <stdio.h>
#include <string.h>

void show_help(void) {
  printf("Usage: notes <command> [--options]\n");
  printf("Commands:\n");
  printf("  topic <action> [--options]   Initialise a new object\n");
}

void fuck(void) { printf("fuck me daddy\n"); }

int main(int argc, char *argv[]) {
  Command *cmd_ptr;
  cmd_ptr = parse_command(argc, argv);
  if (cmd_ptr == NULL) {
    show_help();
    return -1;
  }
  switch (cmd_ptr->type) {
  case TOPIC:
    cmd_topic(cmd_ptr);
    break;
  case PROBLEM:
    cmd_problem(cmd_ptr);
    break;
  }
  print_command(cmd_ptr);
  return 0;
}
