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
    };
    Parser::Options par_opt = Parser::Options(options);
    std::unordered_map<std::string, int> par_map = par_opt.all_options();
    assert(par_map.empty());

    return 0;
}
