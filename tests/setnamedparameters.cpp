/**
 * Initialize Options class with 3-item sized arrays so that:
 * - 1st: name of the option
 * - 2nd: long option (--)
 * - 3rd: short option (-)
 */
#include <assert.h>

#include "parser.h"


int main() {
    std::vector<std::vector<std::string>> options = {
        // name                | --parameter        | -p
        { "longpar",             "long",              "l"                },
        { "longonlypar",         "longonly",          ""                 },
        { "longdashedpar",       "long-dashed",       "l-d"              },
        { "longonlydashedpar",   "longonly-dashed",   ""                 },
        { "short1par",           "",                  "s"                },
        { "short2par",           "",                  "so"               },
        { "shortonlypar",        "",                  "shortonly"        },
        { "shortonlydashedpar",  "",                  "shortonly-dashed" },
        { "invalid",             "",                  ""                 }
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
    assert(par_map.find("longpar") != par_map.end());
    assert(par_map.find("long") == par_map.end());
    assert(par_map.find("l") == par_map.end());
    assert(par_map["longpar"] == 1);
    assert(par_map.count("long") == 0);
    assert(par_map.count("l") == 0);

    // --longonly
    assert(par_map.find("longonlypar") != par_map.end());
    assert(par_map.find("longonly") == par_map.end());
    assert(par_map.find("") == par_map.end());
    assert(par_map["longonlypar"] == 1);
    assert(par_map.count("longonly") == 0);
    assert(par_map.count("") == 0);

    // -l-d
    assert(par_map.find("longdashedpar") != par_map.end());
    assert(par_map.find("long-dashed") == par_map.end());
    assert(par_map.find("l-d") == par_map.end());
    assert(par_map["longdashedpar"] == 1);
    assert(par_map.count("long-dashed") == 0);
    assert(par_map.count("l-d") == 0);

    // --longonly-dashed
    assert(par_map.find("longonlydashedpar") != par_map.end());
    assert(par_map.find("longonly-dashed") == par_map.end());
    assert(par_map.find("") == par_map.end());
    assert(par_map["longonlydashedpar"] == 1);
    assert(par_map.count("longonly-dashed") == 0);
    assert(par_map.count("") == 0);

    // -s
    assert(par_map.find("short1par") != par_map.end());
    assert(par_map.find("") == par_map.end());
    assert(par_map.find("s") == par_map.end());
    assert(par_map["short1par"] == 1);
    assert(par_map.count("") == 0);
    assert(par_map.count("s") == 0);

    // -so
    assert(par_map.find("short2par") != par_map.end());
    assert(par_map.find("") == par_map.end());
    assert(par_map.find("so") == par_map.end());
    assert(par_map["short2par"] == 1);
    assert(par_map.count("") == 0);
    assert(par_map.count("so") == 0);

    return 0;
}
