#include "utils/parse_commands.h"
#include <stdio.h>
#include <string.h>

void show_help(void) {
  printf("Usage: notes <command> [--options]\n");
  printf("Commands:\n");
  printf("  new <command> [--options]   Initialise a new object\n");
}

int main(int argc, char *argv[]) {
  Command *cmd_ptr;
  cmd_ptr = parse_command(argc, argv);
  if (cmd_ptr == NULL) {
    show_help();
    return -1;
  }
  print_command(cmd_ptr);
  return 0;
}
