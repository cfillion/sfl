#include "vendor/catch.hpp"

#include <sfl/doctor.hpp>
#include <sfl/errors.hpp>
#include <sfl/object.hpp>

using namespace sfl;

static const char *M = "[object]";

static object make_object()
{
  registry reg;
  reg.add({"foo"});
  location loc({0, &reg});
  return object{"foo", loc};
}

TEST_CASE("unregistered object", M) {
  doctor doc;
  registry reg;
  location loc({&doc, &reg});

  REQUIRE_THROWS_AS({
    object obj("qwfpgjluy", loc);
  }, unknown_object);

  const diagnosis_bag bag = doc.bag();
  REQUIRE(bag.size() == 1);
  REQUIRE(bag.at(0) ==
    diagnosis(diagnosis::error, "unknown object name 'qwfpgjluy'")
  );
}

TEST_CASE("case insensitive object name", M) {
  registry reg;
  reg.add({"foo"});
  location loc({0, &reg});

  object{"FOO", loc};
}

TEST_CASE("error retains original name", M) {
  doctor doc;
  registry reg;
  location loc({&doc, &reg});

  REQUIRE_THROWS_AS({
    object obj("FOO", loc);
  }, unknown_object);

  const diagnosis_bag bag = doc.bag();
  REQUIRE(bag.size() == 1);
  REQUIRE(bag.at(0) ==
    diagnosis(diagnosis::error, "unknown object name 'FOO'") // not 'foo'
  );
}

TEST_CASE("set variable", M) {
  object obj = make_object();

  REQUIRE(obj.var_count("test") == 0);
  obj.var_set({"test", variable::string});
  REQUIRE(obj.var_count("test") == 1);
}

TEST_CASE("get variable", M) {
  object obj = make_object();

  REQUIRE_THROWS_AS({
    obj.var_get("test");
  }, undefined_variable);

  const variable var{"test", "hello world"};
  obj.var_set(var);

  REQUIRE(obj.var_get("test") == var);
  REQUIRE(obj.var_value<std::string>("test") == "hello world");
}
