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
  if (strlen(key) > MAX_KEYS || strlen(value) > MAX_VALUE_LENGTH) {
    return;
  }
  strcpy(db.keys[db.count], key);
  strcpy(db.values[db.count], value);
  db.count++;
}

void cdb_remove(char* key) {
  if (strlen(key) > MAX_KEYS) {
    return;
  }
  for (int i = 0; i < db.count; i++) {
    if (strcmp(db.keys[i], key) == 0) {
      strcpy(db.keys[i], db.keys[db.count - 1]);
      strcpy(db.values[i], db.values[db.count - 1]);
      db.count--;
      break;
    }
  }

}

char** get_keys() {
  char** keys = (char**)malloc(db.count * sizeof(char*));
  for (int i = 0; i < db.count; i++) {
    keys[i] = db.keys[i];
  }
  return keys;
}

char* cdb_get(char* key) {
  if (strlen(key) > MAX_KEYS) {
    return;
  }
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
