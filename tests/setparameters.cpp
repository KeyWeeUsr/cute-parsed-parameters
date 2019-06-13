/**
 * Initialize Options class with 2-item sized arrays so that:
 * - 1st: long option (--)
 * - 2nd: short option (-)
 *
 * Note: The long option is always prioritized if there is both
 * long + short available.
 */
#include <assert.h>

#include "parser.h"


int main() {
    std::vector<std::vector<std::string>> options = {
        // --parameter | -p
        {"long", "l"},
        {"longonly", ""},
        {"long-dashed", "l-d"},
        {"longonly-dashed", ""},
        {"", "s"},
        {"", "so"},
        {"", "shortonly"},
        {"", "shortonly-dashed"},
        {"", ""}
    };

    std::vector<std::string> params = {
        "executable",         // [key]
        "--long",             // long
        "-l-d",               // long-dashed
        "--longonly",         // longonly
        "--longonly-dashed",  // longonly-dashed
        "-s",                 // s
        "-so"                 // so
    };
    std::vector<char *> argv;
    for (const std::string &par : params) {
        argv.push_back((char *)(par.data()));
    }
    argv.push_back(nullptr);

    Parser::Options par_opt = Parser::Options(
        argv.size() - 1, argv.data(), options
    );

    std::unordered_map<std::string, int> par_map = par_opt.all_options();

    // --long
    assert(par_map.find("long") != par_map.end());
    assert(par_map.find("l") == par_map.end());
    assert(par_map["long"] == 1);
    assert(par_map.count("l") == 0);

    // --longonly
    assert(par_map.find("longonly") != par_map.end());
    assert(par_map.find("") == par_map.end());
    assert(par_map["longonly"] == 1);
    assert(par_map.count("") == 0);

    // -l-d
    assert(par_map.find("long-dashed") == par_map.end());
    assert(par_map.find("l-d") != par_map.end());
    assert(par_map.count("long-dashed") == 0);
    assert(par_map["l-d"] == 1);

    // --longonly-dashed
    assert(par_map.find("longonly-dashed") != par_map.end());
    assert(par_map.find("") == par_map.end());
    assert(par_map["longonly-dashed"] == 1);
    assert(par_map.count("") == 0);

    // -s
    assert(par_map.find("") == par_map.end());
    assert(par_map.find("s") != par_map.end());
    assert(par_map.count("") == 0);
    assert(par_map["s"] == 1);

    // -so
    assert(par_map.find("") == par_map.end());
    assert(par_map.find("so") != par_map.end());
    assert(par_map.count("") == 0);
    assert(par_map["so"] == 1);

    return 0;
}
