#include "vendor/catch.hpp"

#include <sfl/errors.hpp>
#include <sfl/registry.hpp>

using namespace sfl;

static const char *M = "[registry]";

TEST_CASE("definition name and user data", M) {
  const definition a{"foo"};
  REQUIRE(a.name() == "foo");
  REQUIRE(a.user_data() == -1);

  const definition b{"bar", 42};
  REQUIRE(b.name() == "bar");
  REQUIRE(b.user_data() == 42);
}

TEST_CASE("add to registry", M) {
  registry reg;
  REQUIRE(reg.count("foo") == 0);

  reg.add(definition{"foo"});

  REQUIRE(reg.count("foo") == 1);
  REQUIRE(reg.at("foo").name() == "foo");
}

TEST_CASE("add duplicate", M) {
  registry reg;
  reg.add(definition{"foo"});

  REQUIRE_THROWS_AS({
    reg.add(definition{"foo"});
  }, duplicate_definition);

  REQUIRE(reg.count("foo") == 1);
}

TEST_CASE("unknown definition", M) {
  const registry reg;
  REQUIRE(reg.count("foo") == 0);

  REQUIRE_THROWS_AS({
    reg.at("foo");
  }, std::out_of_range);
}

TEST_CASE("lowercase names", M) {
  const definition def{"FOO_BAR"};
  REQUIRE(def.name() == "foo_bar");
}

TEST_CASE("name validation", M) {
  REQUIRE_THROWS_AS(definition{"a b"}, illegal_name);
  REQUIRE_THROWS_AS(definition{"0x"}, illegal_name);
  definition{"x0"};
  definition{"_"};
}
