#include "vendor/catch.hpp"

#include <sfl/doctor.hpp>
#include <sfl/errors.hpp>
#include <sfl/object.hpp>

using namespace sfl;

static const char *M = "[object]";

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
  doctor doc;
  registry reg;
  reg.add({"foo"});
  location loc({&doc, &reg});

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
