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

void cdb_init_database(cdb_database* db) {
  db->count = 0;
}

void cdb_set(cdb_database* db, char* key, char* value) {
  if (strlen(key) > MAX_KEYS || strlen(value) > MAX_VALUE_LENGTH) {
    return;
  }
  strcpy(db->keys[db->count], key);
  strcpy(db->values[db->count], value);
  db->count++;
}

void cdb_remove(cdb_database* db, char* key) {
  if (strlen(key) > MAX_KEYS || db->count == 0) {
    return;
  }
  for (int i = 0; i < db->count; i++) {
    if (strcmp(db->keys[i], key) == 0) {
      strcpy(db->keys[i], db->keys[db->count - 1]);
      strcpy(db->values[i], db->values[db->count - 1]);
      db->count--;
      break;
    }
  }
}

char** cdb_get_keys(cdb_database* db) {
  char** keys = (char**)malloc(db->count * sizeof(char*));
  for (int i = 0; i < db->count; i++) {
    keys[i] = db->keys[i];
  }
  return keys;
}

char* cdb_get_value(cdb_database* db, char* key) {
  if (strlen(key) > MAX_KEYS) {
    return NULL;
  }
  for (int i = 0; i < db->count; i++) {
    if (strcmp(db->keys[i], key) == 0) {
      return db->values[i];
    }
  }
  return NULL;
}

void cdb_save_database(cdb_database* db, char* filename) {
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    return;
  }
  for (int i = 0; i < db->count; i++) {
    fprintf(fp, "%s %s\n", db->keys[i], db->values[i]);
  }
  fclose(fp);
}

void cdb_load_database(cdb_database* db, char* filename) {
  cdb_init_database(db);

  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    return;
  }

  char key[MAX_VALUE_LENGTH];
  char value[MAX_VALUE_LENGTH];
  while (fscanf(fp, "%s %s\n", key, value) == 2) {
    cdb_set(db, key, value);
  }

  fclose(fp);
}

#endif // CDB_H_INCLUDED
