#ifndef CDB_H_INCLUDED
#define CDB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYS 100
#define MAX_VALUE_LENGTH 1000

typedef struct {
  char keys[MAX_KEYS][MAX_VALUE_LENGTH];
  char values[MAX_KEYS][MAX_VALUE_LENGTH];
  int count;
} cdb_database;

cdb_database db;

void cdb_init_database() {
  db.count = 0;
}

void cdb_set(char* key, char* value) {
  strcpy(db.keys[db.count], key);
  strcpy(db.values[db.count], value);
  db.count++;
}

char* cdb_get(char* key) {
  for (int i = 0; i < db.count; i++) {
    if (strcmp(db.keys[i], key) == 0) {
      return db.values[i];
    }
  }
  return NULL;
}

void cdb_save_database(char* filename) {
  FILE* fp = fopen(filename, "w");
  for (int i = 0; i < db.count; i++) {
    fprintf(fp, "%s %s\n", db.keys[i], db.values[i]);
  }
  fclose(fp);
}

void cdb_load_database(char* filename) {
  cdb_init_database();

  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    return;
  }

  char key[MAX_VALUE_LENGTH];
  char value[MAX_VALUE_LENGTH];
  while (fscanf(fp, "%s %s\n", key, value) == 2) {
    cdb_set(key, value);
  }

  fclose(fp);
}

#endif // CDB_H_INCLUDED
