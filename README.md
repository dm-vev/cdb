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

int main(int argc, char** argv) {

  cdb_init_database(); // Initializing database
  cdb_set("hello", "world"); // Set to "hello" cell value: "world"
  cdb_set("foo", "bar"); // Set to "foo" cell value: "bar"

  cdb_save_database("test.db"); // Save database to test.db
  cdb_load_database("test.db"); // Load database to test.db

  printf("%s\n", cdb_get("hello")); // Print "hello" cell
  printf("%s\n", cdb_get("foo")); // Print "foo" cell

  return 0;
}

```

Created with :gift_heart:
