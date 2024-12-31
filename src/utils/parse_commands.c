#include "parse_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Command *parse_command(int argc, char *argv[]) {
  if (argc < 3) {
    return NULL;
  }

  int no_options = (argc - 3) / 2;
  // allocate memory with argc
  Command *command_ptr = malloc(sizeof(Command));
  Option *options = malloc(no_options * sizeof(Option));

  // fill in the structs

  strcpy(command_ptr->cmd, argv[1]);
  strcpy(command_ptr->type, argv[2]);
  command_ptr->no_options = no_options;
  for (int i = 0; i < no_options; i++) {
    strcpy((options[i]).key, argv[i * 2 + 3] + 2);
    strcpy((options[i]).value, argv[i * 2 + 4]);
  }
  command_ptr->options = options;
  return command_ptr;
}

void print_command(Command *command_ptr) {
  printf("Command -> %s\n", command_ptr->cmd);
  printf("Type -> %s\n", command_ptr->type);
  printf("Number of Options -> %d\n\n", command_ptr->no_options);
  for (int i = 0; i < command_ptr->no_options; i++) {
    printf("Option[%d] key -> %s\n", i, (command_ptr->options)[i].key);
    printf("Option[%d] value -> %s\n", i, (command_ptr->options)[i].value);
  }
}
