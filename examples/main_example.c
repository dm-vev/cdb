#include "cdb.h"

int main(int argc, char** argv) {

  cdb_init_database(); // Initializing database
  cdb_set("hello", "world"); // Set to "hello" cell value: "world"
  cdb_set("foo", "bar"); // Set to "foo" cell value: "bar"
  cdb_set("delete", "eggs"); // "Deleted" must be deleted
  cdb_remove("delete"); // Deleting "Deleted"

  cdb_save_database("test.db"); // Save database to test.db
  cdb_load_database("test.db"); // Load database to test.db

  printf("%s\n", cdb_get("hello")); // Print "hello" cell
  printf("%s\n", cdb_get("foo")); // Print "foo" cell

  char** keys = get_keys(); // Get all keys from database
  for (int i = 0; i < db.count; i++) {
    printf("Key: %s\n", keys[i]); // Printing. Key "delete" must not displayed
  }
  free(keys); // Free memory

  return 0;
}
