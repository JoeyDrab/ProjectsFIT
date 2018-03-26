#include "gtest/gtest.h"
extern "C" {
#include "../lex.h"
}

namespace {

// The fixture for testing class Foo.
class LexTest : public ::testing::Test {
 protected:

  LexTest() {
	file = fopen("test/lex_input/input1.bas", "r");

	if (file == NULL) {
		fprintf(stderr, "Pokazilo sa otvarnie suboru\n");
		exit(-1);
	}
  }

  virtual ~LexTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(LexTest, identifier_int) {
    TToken * t = token_get();
    EXPECT_EQ(t->type, token_integer);
    EXPECT_STREQ(t->name, "123");
}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
