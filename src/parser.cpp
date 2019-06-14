#include "parser.h"


namespace Parser {
    std::vector<std::string> parse(const int argc, char *argv[]) {
        std::vector<std::string> result;
        for (int i = 1; i < argc; i++) {
            result.push_back(static_cast<std::string>(argv[i]));
        }
        return result;
    }

    Options::Options(
            const int argc, char *argv[],
            std::vector<std::vector<std::string>> custom_options
    ) {
        Options::_keys.clear();

        for (const std::vector<std::string> &opt : custom_options) {
            Options::_keys.push_back(opt);
        }

        Options::options.clear();
        Options::set_options(argc, argv);
    }

    void Options::set_options(const int argc, char *argv[]) {
        std::string opt_key;
        std::string value;
        std::string short_par;
        std::string long_par;
        std::string short_sep = "-";
        std::string long_sep = "--";
        bool named = false;

        for (int i = 1; i < argc; i++) {
            value = static_cast<std::string>(argv[i]);

            for (int j = 0; j < Options::_keys.size(); j++) {
                size_t opt_length = Options::_keys[j].size();

                if (opt_length < 2 || opt_length > 3) {
                    // ignore options with unhandled size
                    continue;
                } else if (opt_length == 3) {
                    named = true;
                    opt_key = Options::_keys[j][0];
                    long_par = Options::_keys[j][1];
                    short_par = Options::_keys[j][2];
                } else if (opt_length == 2) {
                    opt_key = long_par = Options::_keys[j][0];
                    short_par = Options::_keys[j][1];
                }

                bool has_long = long_par != "";
                bool has_short = short_par != "";
                bool found_long = has_long && (value == long_sep + long_par);
                bool found_short = has_short && (
                    value == short_sep + short_par
                );
                bool found_param = found_long || found_short;
                if (!named) {
                    if (has_long && found_param) {
                        Options::options[long_par] = 1;
                    } else if (!has_long && has_short && found_param) {
                        Options::options[short_par] = 1;
                    } else if (!has_long && !has_short) {
                        // nothing
                    }
                } else {
                    if (found_param) {
                        Options::options[opt_key] = 1;
                    }
                }
            }
        }
    }

    std::vector<std::string> Options::keys(void) {
        std::vector<std::string> result;

        for (std::vector<std::string> key : Options::_keys) {
            size_t opt_length = key.size();

            if (opt_length < 2 || opt_length > 3) {
                // ignore options with unhandled size
                continue;
            } else if (opt_length == 3) {
                // always use the name even if it'd be e.g. "" (empty string)
                result.push_back(key[0]);
            } else if (opt_length == 2) {
                if (key[0] == "") {
                    // use short-arg only if long is not present
                    result.push_back(key[1]);
                } else {
                    result.push_back(key[0]);
                }
            }
        }
        return result;
    }

    std::unordered_map<std::string, int> Options::all_options(void) {
        return Options::options;
    }
}
