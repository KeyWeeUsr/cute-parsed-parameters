#include "parser.h"


namespace Parser {
    std::vector<std::string> parse(const int argc, char *argv[]) {
        std::vector<std::string> result;
        for (int i = 1; i < argc; i++) {
            result.push_back(static_cast<std::string>(argv[i]));
        }
        return result;
    }

    Options::Options(const int argc, char *argv[]) {
        for (int i = 0; i < Options::_keys.size(); i++) {
            Options::options[Options::_keys[i][0]] = 0;
        }

        std::string value;
        for (int i = 1; i < argc; i++) {
            value = static_cast<std::string>(argv[i]);

            std::string short_par;
            std::string long_par;
            for (int j = 0; j < Options::_keys.size(); j++) {
                long_par = Options::_keys[j][0];
                short_par = Options::_keys[j][1];

                bool found_long = value == "--" + long_par;
                bool found_short = (
                    short_par != "" && value == "-" + short_par
                );

                if (found_long || found_short)
                    Options::options[Options::_keys[j][0]] = 1;
            }
        }
    }

    std::vector<std::string> Options::keys(void) {
        std::vector<std::string> result;
        for (int i = 0; i < Options::_keys.size(); i++)
            result.push_back(Options::_keys[i][0]);
        return result;
    }

    std::unordered_map<std::string, int> Options::all_options(void) {
        return Options::options;
    }
}
