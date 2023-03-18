/*
NOTE: only posix systems, windows is not yet supported :(
*/

#ifndef CDB_H_INCLUDED
#define CDB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_KEYS 100
#define MAX_VALUE_LENGTH 1000

// Структура базы данных
typedef struct {
  char keys[MAX_KEYS][MAX_VALUE_LENGTH];
  char values[MAX_KEYS][MAX_VALUE_LENGTH];
  int count;
  pthread_mutex_t lock;
} cdb_database;

cdb_database db;

// Инициализация базы данных
void cdb_init_database() {
  db.count = 0;
  pthread_mutex_init(&db.lock, NULL);
}

// Установка значения
void cdb_set(char* key, char* value) {
  pthread_mutex_lock(&db.lock);

  if (strlen(key) > MAX_KEYS || strlen(value) > MAX_VALUE_LENGTH) {
    pthread_mutex_unlock(&db.lock);
    return;
  }

  strcpy(db.keys[db.count], key);
  strcpy(db.values[db.count], value);
  db.count++;

  pthread_mutex_unlock(&db.lock);
}

// Удаление значения
void cdb_remove(char* key) {
  pthread_mutex_lock(&db.lock);

  if (strlen(key) > MAX_KEYS) {
    pthread_mutex_unlock(&db.lock);
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

  pthread_mutex_unlock(&db.lock);
}

// Получение всех ключей
char** get_keys() {
  pthread_mutex_lock(&db.lock);

  char** keys = (char**)malloc(db.count * sizeof(char*));
  for (int i = 0; i < db.count; i++) {
    keys[i] = db.keys[i];
  }

  pthread_mutex_unlock(&db.lock);
  return keys;
}

// Получение значения по ключу
char* cdb_get(char* key) {
  pthread_mutex_lock(&db.lock);

  if (strlen(key) > MAX_KEYS) {
    pthread_mutex_unlock(&db.lock);
    return NULL;
  }

  for (int i = 0; i < db.count; i++) {
    if (strcmp(db.keys[i], key) == 0) {
      char* value = db.values[i];
      pthread_mutex_unlock(&db.lock);
      return value;
    }
  }

  pthread_mutex_unlock(&db.lock);
  return NULL;
}

// Сохранение базы данных в файл
void cdb_save_database(char* filename) {
  pthread_mutex_lock(&db.lock);

  FILE* fp = fopen(filename, "w");
  for (int i = 0; i < db.count; i++) {
    fprintf(fp, "%s %s\n", db.keys[i], db.values[i]);
  }
  fclose(fp);

  pthread_mutex_unlock(&db.lock);
}

// Загрузка базы данных из файла
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
