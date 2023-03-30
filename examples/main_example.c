#include "cdb.h"
#include <stdio.h>

int main() {
  cdb_database db;
  cdb_init_database(&db);

  // добавляем записи в БД
  cdb_set(&db, "key1", "value1");
  cdb_set(&db, "key2", "value2");
  cdb_set(&db, "key3", "value3");

  // сохраняем БД в файл
  cdb_save_database(&db, "mydb.cdb");

  // загружаем БД из файла
  cdb_load_database(&db, "mydb.cdb");

  // получаем список ключей
  char** keys = cdb_get_keys(&db);
  for (int i = 0; i < db.count; i++) {
    printf("%s\n", keys[i]);
  }
  free(keys);

  // получаем значение по ключу
  char* value = cdb_get_value(&db, "key1");
  printf("%s\n", value);

  // удаляем запись из БД
  cdb_remove(&db, "key2");

  // сохраняем изменения в файл
  cdb_save_database(&db, "mydb.cdb");

  return 0;
}
