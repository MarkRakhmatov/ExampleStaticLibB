#include <boost/ut.hpp>

#include <ExampleStaticLibB/ExampleStaticLibB.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <exception>

using namespace boost::ut;

void tests() {
  "get string"_test = [] {
    expect(!libB::getString().empty());
    expect(libB::getString() == std::string("cpp static lib example"));
  };

  "factorial"_test = [] {
    expect(libB::factorial(0) == 1_i);
    expect(libB::factorial(1) == 1_i);
    expect(libB::factorial(2) == 2_i);
    expect(libB::factorial(12) == 479001600_i);
    expect(libB::factorial(13) == -1_i);
  };

  "factorial_constexpr"_test = [] {
    static_assert(libB::factorialConstexpr(0) == 1_i);
    static_assert(libB::factorialConstexpr(1) == 1_i);
    static_assert(libB::factorialConstexpr(2) == 2_i);
  };
}

int main(int argc, const char** argv) {
  try {
    boost::ut::detail::cfg::parse_arg_with_fallback(argc, argv);
    tests();
  } catch (const std::exception& ex) {
    std::cout << "exception: "<< ex.what();
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cout <<"unknown exception";
    return EXIT_FAILURE;
  }
}
