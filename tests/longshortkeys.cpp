/**
 * Initialize Options class with 2-item sized arrays so that:
 * - 1st: long option (--)
 * - 2nd: short option (-)
 *
 * Note: The long option is always prioritized if there is both
 * long + short available.
 */
#include <assert.h>
#include <algorithm>

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

    std::string exe = "executable";
    std::vector<char *> argv;
    argv.push_back((char *)(exe.data()));
    argv.push_back(nullptr);

    Parser::Options par_opt = Parser::Options(
        argv.size() - 1, argv.data(), options
    );

    std::vector<std::string> keys = par_opt.keys();
    assert(!keys.empty());

    // --long
    assert(std::find(keys.begin(), keys.end(), "long") != keys.end());

    // --longonly
    assert(std::find(keys.begin(), keys.end(), "longonly") != keys.end());

    // -l-d
    assert(std::find(keys.begin(), keys.end(), "long-dashed") != keys.end());

    // --longonly-dashed
    assert(
        std::find(keys.begin(), keys.end(), "longonly-dashed") != keys.end()
    );

    // -s
    assert(std::find(keys.begin(), keys.end(), "s") != keys.end());

    // -so
    assert(std::find(keys.begin(), keys.end(), "so") != keys.end());

    // shortonly
    assert(std::find(keys.begin(), keys.end(), "shortonly") != keys.end());

    // shortonly-dashed
    assert(
        std::find(keys.begin(), keys.end(), "shortonly-dashed") != keys.end()
    );

    return 0;
}
