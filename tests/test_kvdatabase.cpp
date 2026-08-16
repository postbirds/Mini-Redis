#include <gtest/gtest.h>
#include "KVDatabase.h"

TEST(KVDatabaseTest, SetAndGet) {
  KVDatabase db;
  db.set("a", "a_val");

  EXPECT_EQ(db.get("a"), "a_val");
}

TEST(KVDatabaseTest, GetNonExistentKey) {
  KVDatabase db;

  EXPECT_EQ(db.get("unknown_key"), "(nil)");
}

TEST(KVDatabaseTest, SaveAndLoadSnapshot) {
  {
    KVDatabase db;
    db.set("lang", "C++");
    db.save_snapshot();
  }

  {
    KVDatabase db2;
    EXPECT_EQ(db2.get("lang"), "C++");
  }
}
