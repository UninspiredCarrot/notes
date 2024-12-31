#include <stdio.h>
#include "new.h"
#include <string.h>
#include <stdlib.h>
#include "../utils/file_reader.h"

typedef struct {
  char name[64];
  /*char* tags[64];*/
  /*char** books;*/
} Topic; 

void init_topic(Topic* new_topic);
void print_topic(Topic* new_topic);
void get_name(char name[64]);
void save_topic(Topic* new_topic);


int command_new(int argc, char *argv[]) {
  printf("%d %s\n", argc, argv[0]);
  if (strcmp(argv[0], "topic") == 0) {
    /*Topic* new_topic_ptr = malloc(sizeof(Topic));*/
    /*Topic new_topic;*/
    /*init_topic(&new_topic);*/
    /*/*print_topic(&new_topic);*/
    /*/*write_topic();*/
    /*char topics_path[255];*/
    /*get_path(topics_path, TOPICS);*/
    /*/*write_path(strcat(topics_path, new_topic.name), FOLDER);*/
    /*/*write_path(strcat(topics_path, "problem_set"), FOLDER);*/
    /*printf("%s\n", topics_path);*/
    
  }
    return 0;
}

void init_topic(Topic* new_topic_ptr) {
  /*new_topic_ptr->name = &name;*/
  char name[64];
  get_name(name);
  strcpy(new_topic_ptr->name, name);
  /*new_topic->tags = {"new_tags", "newer_tags"};*/
  /*new_topic->books = {"new_books", "newer_books"};*/
}

void print_topic(Topic* new_topic_ptr) {
  printf("Topic Name: %s\n", new_topic_ptr->name);
  /*printf("new_topic tags: %s", new_topic->tags);*/
  /*printf("new_topic books: %s", new_topic->books);*/
}

void get_name(char name[64]) {
  printf("Enter topic name: ");
  scanf("%s", name);
}

void save_topic(Topic* new_topic) {

}

