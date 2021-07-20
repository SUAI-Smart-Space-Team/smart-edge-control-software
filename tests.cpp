#include <iostream>
#include <gtest/gtest.h>
#include "commands/WebCommand.h"

static std::string json(R"({
    "_id": "60ec4cd460550f6c845acf33",
    "void_test": "",
    "quote_test": "\""
  })");

TEST(findValue_tests, standart)
{
	ASSERT_EQ(WebCommand::findValue("_id",json),"60ec4cd460550f6c845acf33");
}

TEST(findValue_tests, quote)
{
	ASSERT_EQ(WebCommand::findValue("quote_test", json), "?");
}

TEST(findValue_tests, voidtest)
{
	ASSERT_THROW(WebCommand::findValue("void_test", json),std::exception);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
