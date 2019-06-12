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
    std::string exe = "executable";
    std::vector<char *> argv;
    argv.push_back((char *)(exe.data()));
    argv.push_back(nullptr);

    Parser::Options par_opt = Parser::Options(
        argv.size() - 1, argv.data(), options
    );
    std::unordered_map<std::string, int> par_map = par_opt.all_options();
    assert(par_map.empty());

    return 0;
}
