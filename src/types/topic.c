#include "../main.h"
#include <stdio.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>

int new_topic(Option *options, int no_options);

int cmd_topic(Command *command_ptr) {
  if (command_ptr->action == NEW) {
    if (new_topic(command_ptr->options, command_ptr->no_options) < 0) {
      printf("Couldn't create topic\n");
      return -1;
    }
  }
  return 0;
}

int new_topic(Option *options, int no_options) {
  struct stat st = {0};
  char topic_path[64] = "Topics";
  if (stat(topic_path, &st) == -1) {
    if (mkdir(topic_path, 0700) != 0) {
      perror("Error creating folder");
      return -1;
    }
  }
  strcat(topic_path, "/");
  for (int i = 0; i < no_options; i++) {
    if (options[i].key == NAME) {
      char folder_path[255];
      strcpy(folder_path, topic_path);
      strcat(folder_path, options[i].value);
      mkdir(folder_path, 0700);
    }
  }

  return 0;
}
