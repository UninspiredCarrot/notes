#ifndef FILE_READER_H
#define FILE_READER_H

enum Path {
  TOPICS
};

void get_path(char path_string[255], enum Path* path);

#endif
