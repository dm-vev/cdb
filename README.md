### CDB - Fast and efficient NoSQL database written in pure C

It is a non-relational database written in pure C for fast performance. At the moment, this database can only store strings, but it may soon be possible to store other types of data.

#### Features
- It only takes up 52 lines!
- Saved to its proprietary file format(It's just writing a structure to a binary file)
- The compiled source is only 140 KB
- Performance

#### Examples:

##### Main example
```c
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
```

Created with :gift_heart:
