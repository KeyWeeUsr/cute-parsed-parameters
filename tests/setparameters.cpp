#include <vector>
#include <assert.h>
#include <unordered_map>

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

    for (const std::vector<std::string> opt : options) {
        if (opt[0] != "") {
            // first value is not empty, expect same-named key
            assert (par_map[opt[0]] == 0);
            assert (par_map.find(opt[1]) == par_map.end());
        } else if (opt[1] != "" && opt[0] == "") {
            // second value is not empty, expect same-named key
            assert (par_map[opt[1]] == 0);
            assert (par_map.find(opt[0]) == par_map.end());
        } else if (opt[0] != "" && opt[1] != "") {
            // both values are not empty, expect same-named key
            // as the first value
            assert (par_map[opt[0]] == 0);
            assert (par_map.find(opt[1]) == par_map.end());
        }
    }
    return 0;
}
