#include <stdio.h>
#include <unistd.h>
#include "file_reader.h"
#include <strings.h>

int split_buffer(char words[][255], char buffer[255]); 

void get_path(char path_string[255], enum Path* path) {
  FILE* file_ptr = fopen("/Users/bolt/code/notes/src/config.txt", "r");  
  char buffer[255];
  char words[2][255];
  while(fgets(buffer, 255, file_ptr) != NULL && split_buffer(words, buffer) != -1) {
    if (*path == TOPICS && (strcmp(words[0], "topics_path") == 0)) {
      strcpy(path_string, words[1]);
    }
  }
}

int split_buffer(char words[][255], char buffer[255]) {

  char* delimiter = "=";
  if (strcmp(buffer, "\n") != 0) {
    strcpy(words[0], strtok(buffer, delimiter));
    strcpy(words[1], strtok(NULL, delimiter));
    return 0;
  }
  return -1;
}

