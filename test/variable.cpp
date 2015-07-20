#include "vendor/catch.hpp"

#include <sfl/variable.hpp>

using namespace sfl;

static const char *M = "[variable]";

TEST_CASE("variable attributes", M) {
  // TODO: test with a non-default location
  const location loc{};
  variable var("name", variable::string, loc);

  REQUIRE(var.name() == "name");
  REQUIRE(var.location() == loc);
}

TEST_CASE("string variable", M) {
  variable var("name", variable::string);

  REQUIRE(var.empty());
  var = "hello world";
  REQUIRE(!var.empty());

  const std::string &value = var.get<std::string>();
  REQUIRE(value == "hello world");
}

TEST_CASE("invalid assignment", M) {
  variable var("name", variable::string);

  REQUIRE_THROWS_AS({
    var = 42;
  }, invalid_assignment);
}

TEST_CASE("invalid conversion", M) {
  variable var("name", variable::string);
  var = "hello world";

  REQUIRE_THROWS_AS({
    var.get<int>();
  }, invalid_conversion);
}

TEST_CASE("reading undefined values", M) {
  variable var("name", variable::string);

  REQUIRE_THROWS_AS({
    var.get<std::string>();
  }, undefined_value);
}

TEST_CASE("direct definition", M) {
  SECTION("string") {
    variable var("name", "hello world");
    REQUIRE(!var.empty());
    REQUIRE(var.get<std::string>() == "hello world");
  }
}
