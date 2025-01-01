#include "../main.h"
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
  if (strcmp(argv[2], "new") == 0) {
    command_ptr->action = NEW;
  }

  if (strcmp(argv[1], "topic") == 0) {
    command_ptr->type = TOPIC;
  }

  command_ptr->no_options = no_options;
  for (int i = 0; i < no_options; i++) {
    if (strcmp(argv[i * 2 + 3] + 2, "name") == 0) {
      (options[i]).key = NAME;
    }
    strcpy((options[i]).value, argv[i * 2 + 4]);
  }
  command_ptr->options = options;
  return command_ptr;
}

void print_command(Command *command_ptr) {
  printf("Command -> %d\n", command_ptr->action);
  printf("Type -> %d\n", command_ptr->type);
  printf("Number of Options -> %d\n\n", command_ptr->no_options);
  for (int i = 0; i < command_ptr->no_options; i++) {
    printf("Option[%d] key -> %d\n", i, (command_ptr->options)[i].key);
    printf("Option[%d] value -> %s\n", i, (command_ptr->options)[i].value);
  }
}
