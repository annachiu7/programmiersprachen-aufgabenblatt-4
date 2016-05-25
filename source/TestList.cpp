#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "List.hpp"

TEST_CASE("describe_constructor", "[aufgabe1]")
{
	List<int> list{};
	REQUIRE(list.empty()==true);
	REQUIRE(list.size()==0);
}

TEST_CASE ( " add an element with push_front " , " [ modifiers ] " )
{
	List<int> list ;
	list.push_front(42);
	REQUIRE(42 == list.front());
}

int main(int argc, char *argv[])
{
	return Catch::Session().run(argc, argv);
}