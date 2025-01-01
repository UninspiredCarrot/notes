#include "../main.h"
#include </usr/local/include/cjson/cJSON.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>

struct memory {
  char *response;
  size_t size;
};

size_t write_callback(void *ptr, size_t size, size_t nmemb, struct memory *mem);

int new_problem(Option *options, int no_options);
struct Leetcode_Question *parse_lcq_link(struct Leetcode_Question *lcq_ptr,
                                         char *link);

int cmd_problem(Command *command_ptr) {
  if (command_ptr->action == NEW) {
    if (new_problem(command_ptr->options, command_ptr->no_options) < 0) {
      printf("Couldn't create problem\n");
      return -1;
    }
  }
  return 0;
}

int new_problem(Option *options, int no_options) {
  struct stat st = {0};
  char problem_path[64] = "Problems";
  if (stat(problem_path, &st) == -1) {
    if (mkdir(problem_path, 0700) != 0) {
      perror("Error creating folder");
      return -1;
    }
  }
  strcat(problem_path, "/");
  char folder_path[255];
  struct Leetcode_Question *lcq_ptr = NULL;
  for (int i = 0; i < no_options; i++) {
    if (options[i].key == URL) {
      lcq_ptr = parse_lcq_link(lcq_ptr, options[i].value);
      strcpy(folder_path, problem_path);
      char title[255];
      strcpy(title, lcq_ptr->questionID);
      strcat(title, ".");
      strcat(title, lcq_ptr->questionTitle);
      strcat(folder_path, title);
      mkdir(folder_path, 0700);
    } else if (options[i].key == NAME) {
      strcpy(folder_path, problem_path);
      strcat(folder_path, options[i].value);
      mkdir(folder_path, 0700);
    }
  }
  strcat(folder_path, "/");
  char question_path[255];
  strcpy(question_path, folder_path);
  strcat(question_path, "Question.md");
  // config file
  FILE *config_ptr = fopen(question_path, "a+");
  fprintf(config_ptr, "# Question\n");
  if (lcq_ptr != NULL) {
    fprintf(config_ptr, "%s\n", lcq_ptr->questionHTML);
  }
  fprintf(config_ptr, "# Difficulty\n");
  if (lcq_ptr != NULL) {
    switch (lcq_ptr->difficulty) {
    case EASY:
      fprintf(config_ptr, "Easy\n");
      break;
    case MEDIUM:
      fprintf(config_ptr, "Medium\n");
      break;
    case HARD:
      fprintf(config_ptr, "Hard\n");
      break;
    }
  }

  fprintf(config_ptr, "# Solutions Paths\n");
  fprintf(config_ptr, "## Naive/ Brute Force\n");
  fprintf(config_ptr, "## Optimal\n");
  fprintf(config_ptr, "# Topics\n");
  fprintf(config_ptr, "# Points\n");
  fprintf(config_ptr, "# Source\n");
  if (lcq_ptr != NULL) {
    fprintf(config_ptr, "%s\n", lcq_ptr->link);
  }

  fprintf(config_ptr, "# Dates\n");
  // solutions folder
  strcat(folder_path, "/Solutions");
  mkdir(folder_path, 0700);

  return 0;
}

// Write callback function for libcurl to write the response into the memory
// struct
size_t write_callback(void *ptr, size_t size, size_t nmemb,
                      struct memory *mem) {
  size_t new_size = mem->size + size * nmemb;
  mem->response = realloc(mem->response, new_size + 1);
  if (mem->response == NULL) {
    printf("Error reallocating memory!\n");
    return 0;
  }

  memcpy(mem->response + mem->size, ptr, size * nmemb);
  mem->response[new_size] = '\0'; // Null terminate the string
  mem->size = new_size;

  return size * nmemb;
}

struct Leetcode_Question *parse_lcq_link(struct Leetcode_Question *lcq_ptr,
                                         char *link) {
  char *start;
  char result[100];

  start = strstr(link, "problems/");
  if (start) {
    start += strlen("problems/");

    int i = 0;
    while (start[i] != '/' && start[i] != '\0') {
      result[i] = start[i];
      i++;
    }
    result[i] = '\0';
  }
  char url[255] = "https://alfa-leetcode-api.onrender.com/select?titleSlug=";
  strcat(url, result);
  CURL *curl;
  CURLcode res;
  struct memory chunk = {0};

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (!curl) {
    printf("CURL initialisation failed\n");
    return NULL;
  }
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

  // Perform the HTTP GET request
  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    printf("CURL error: %s\n", curl_easy_strerror(res));
    return NULL;
  }
  // Parse the fetched JSON
  cJSON *root = cJSON_Parse(chunk.response);
  if (root == NULL) {
    printf("Error parsing JSON\n");
    return NULL;
  }

  // Extract specific fields from the JSON
  const cJSON *clink = cJSON_GetObjectItemCaseSensitive(root, "link");
  const cJSON *questionId =
      cJSON_GetObjectItemCaseSensitive(root, "questionId");
  const cJSON *questionTitle =
      cJSON_GetObjectItemCaseSensitive(root, "questionTitle");
  const cJSON *difficulty =
      cJSON_GetObjectItemCaseSensitive(root, "difficulty");
  const cJSON *questionHTML =
      cJSON_GetObjectItemCaseSensitive(root, "question");

  lcq_ptr = malloc(sizeof(struct Leetcode_Question));
  // Display the extracted fields
  if (cJSON_IsString(clink) && clink->valuestring) {
    strcpy(lcq_ptr->link, clink->valuestring);
  }
  if (cJSON_IsString(questionId) && questionId->valuestring) {
    strcpy(lcq_ptr->questionID, questionId->valuestring);
  }

  if (cJSON_IsString(questionTitle) && questionTitle->valuestring) {
    strcpy(lcq_ptr->questionTitle, questionTitle->valuestring);
  }
  if (cJSON_IsString(difficulty) && difficulty->valuestring) {
    if (strcmp(difficulty->valuestring, "Easy")) {
      lcq_ptr->difficulty = EASY;
    } else if (strcmp(difficulty->valuestring, "Medium")) {
      lcq_ptr->difficulty = MEDIUM;
    } else if (strcmp(difficulty->valuestring, "Hard")) {
      lcq_ptr->difficulty = HARD;
    }
  }
  if (cJSON_IsString(questionHTML) && questionHTML->valuestring) {
    strncpy(lcq_ptr->questionHTML, questionHTML->valuestring,
            strlen(questionHTML->valuestring));
  }
  // Clean up
  cJSON_Delete(root);
  free(chunk.response);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return lcq_ptr;
}
