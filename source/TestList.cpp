#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "List.hpp"

TEST_CASE("describe_constructor", "[aufgabe1]")
{
	List<int> list{};
	REQUIRE(list.empty()==true);
	REQUIRE(list.size()==0);
}

TEST_CASE ( "push_front, push_back, pop_front, pop_back, front, back" , " [ modifiers ] " )
{
	List<int> list ;
	list.push_front(42);
	REQUIRE(42 == list.front());
	list.push_front(32);
	REQUIRE(32 == list.front());
	List<int> l2;

	l2.push_back(10);
	REQUIRE(10 == l2.back());
	l2.push_back(52);
	REQUIRE(52 == l2.back());
	REQUIRE(10 == l2.front());

	list.pop_front();
	REQUIRE(42 == list.front());

	l2.pop_back();
	REQUIRE(10 == l2.back());
}

TEST_CASE ( "should be empty after clearing " , " [ clear ] " )
{
	List<int> list ;
	list.push_front (1);
	list.push_front (2);
	list.push_front (3);
	list.push_front (4);
	list.clear();
	REQUIRE(list.empty());
}

TEST_CASE ("should be an empty range after default construction ", " [ iterators ] " )
{
	List<int> list ;
	auto b = list.begin();
	auto e = list.end();
	REQUIRE( b == e );
}

TEST_CASE ("provide access to the first element with begin/end " , " [ iterators ] " )
{
List<int> list ;
list.push_front(42);
REQUIRE(42 == *list.begin());
REQUIRE(42 == *list.end());
}

TEST_CASE ( " copy constructor " , " [ constructor ] " )
{
List<int> list;
list.push_front(1);
list.push_front(2);
list.push_front(3);
list.push_front(4);
List<int> list2{list};
REQUIRE ( list == list2 );
}


int main(int argc, char *argv[])
{
	return Catch::Session().run(argc, argv);
}