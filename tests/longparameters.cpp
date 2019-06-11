#include <vector>
#include <iostream>

#include "parser.h"


int main() {
    std::vector<std::string> params= {"executable", "--help"};
    std::vector<char *> argv;
    for (const std::string &par : params) {
        argv.push_back((char *)(par.data()));
    }
    argv.push_back(nullptr);

    Parser::Options opt = Parser::Options(argv.size() - 1, argv.data());
    if (opt.all_options()["help"] != 1) {
        std::cout << "Expected true for 'help' option" << std::endl;
        return 1;
    }
    return 0;
}
