#include "../../volumealsabt.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void usage(char* argv[]){
  printf("Usage: %s <asoundrc file> <expected file>\n", argv[0]);
  exit(1);
}

int main(int argc, char* argv[]){
  if(argc != 3){
    usage(argv);
  }
  char* asoundrc_filename = argv[1];
  char* expected_filename = argv[2];
  FILE* asoundrc_fp = open(asoundrc_filename, "r");
  if(asoundrc_fp == NULL){
    printf("Cannot open the file %s", asoundrc_filename);
    exit(2);
  }

  char exptected_type[16], expected_cid[16];
  FILE* expected_fp = open(expected_filename, "r");
  fscanf(expected_fp, "%s %s", exptected_type, expected_cid);
  fclose(expected_fp);

  char type[16], cid[16];
  int result;
  parse_asoundrc(asoundrc_fp, &type, &cid);
  if(strcmp(type, exptected_type) == 0 && strcmp(type, expected_cid) == 0){
    result = true;
  }else{
    result = false;
  }

  fclose(asoundrc_fp);

  assert(result == true);
}
