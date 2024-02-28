#include "catch.hpp"

#include "exceptions.h"
#include "image.h"
#include "parse.h"
#include "processor.h"

TEST_CASE("Parser") {
    const char* argv_1arg[] = {"image_processor"};
    const char* argv_2arg[] = {"image_processor", "../tasks/image_processor/test_script/data/lenna.bmp"};
    const char* argv_3arg[] = {"image_processor ", "../tasks/image_processor/test_script/data/lenna.bmp",
                               "../tasks/image_processor/test_script/data/lenna.bmp"};
    const char* argv_incorrect_filter[] = {"image_processor ", "../tasks/image_processor/test_script/data/lenna.bmp",
                                           "../tasks/image_processor/test_script/data/lenna.bmp", "abcdefu"};
    REQUIRE(Parse(1, const_cast<char**>(argv_1arg)).filter_params.empty());       // printed documentation
    REQUIRE_THROWS_AS(Parse(2, const_cast<char**>(argv_2arg)), ParserException);  // not enough arugments
    REQUIRE_THROWS_AS(Parse(3, const_cast<char**>(argv_3arg)), ParserException);  // not enough arugments
    REQUIRE_THROWS_AS(Parse(4, const_cast<char**>(argv_incorrect_filter)),
                      ParserException);  // incorrect filter (no '-' before filter's name)

    std::vector<FilterParams> args(2);
    args[0] = {"neg", {}};
    args[1] = {"crop", {"100", "100"}};
    ParserResults result = {"../tasks/image_processor/test_script/data/lenna.bmp",
                            "../tasks/image_processor/test_script/data/lenna.bmp", args};

    const char* argv_ok[] = {"image_processor ",
                             "../tasks/image_processor/test_script/data/lenna.bmp",
                             "../tasks/image_processor/test_script/data/lenna.bmp",
                             "-neg",
                             "-crop",
                             "100",
                             "100"};
    auto actual_results = Parse(7, const_cast<char**>(argv_ok));
    bool check = actual_results.input_path == result.input_path &&
                 actual_results.output_path == actual_results.output_path &&
                 actual_results.filter_params[0].filter_name == actual_results.filter_params[0].filter_name &&
                 actual_results.filter_params[0].filter_arguments == result.filter_params[0].filter_arguments &&
                 actual_results.filter_params[1].filter_name == actual_results.filter_params[1].filter_name &&
                 actual_results.filter_params[1].filter_arguments == result.filter_params[1].filter_arguments;
    REQUIRE(check);
}

TEST_CASE("Processor") {
    FilterParams params;

    params = {"sharp", {"x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect number of args for Sharp
    params = {"neg", {"x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect number of args for Negative
    params = {"gs", {"x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);

    params = {"crop", {"x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect number of args for Crop
    params = {"crop", {"x", "x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect type of args for Crop
    params = {"crop", {"1.4", "1.4"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"crop", {"-1", "-1"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"crop", {"10000000000000000000000000", "10000000000000000000000000"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);

    params = {"edge", {}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect number of args for Edge
    params = {"edge", {"x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect type of args for Edge
    params = {"edge", {"-1"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"edge", {"10000000000000000000000000"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"edge", {"10000000000000000000000000.0"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);

    params = {"blur", {}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect number of args for Blur
    params = {"blur", {"x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect type of args for Blur
    params = {"blur", {"-1"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"blur", {"10000000000000000000000000"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"blur", {"10000000000000000000000000.0"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);

    params = {"cryst", {}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect number of args for Crystallize
    params = {"cryst", {"x"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);  // incorrect type of args for Crystallize
    params = {"cryst", {"-1"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"cryst", {"1.0"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"cryst", {"10000000000000000000000000"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
    params = {"cryst", {"10000000000000000000000000.0"}};
    REQUIRE_THROWS_AS(CreateFilter(params), ParserException);
}