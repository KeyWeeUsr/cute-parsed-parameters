#ifndef PARSER_CPP
#define PARSER_CPP

#include <vector>
#include <string>
#include <unordered_map>


namespace Parser {
    std::vector<std::string> parse(const int argc, char *argv[]);

    class Options {
    private:
        std::unordered_map<std::string, int> options;
        std::vector<std::vector<std::string>> _keys = {
            {"help", "h"},
            {"lines", "l"},
            {"chars", "c"}
        };

    public:
        Options(std::vector<std::vector<std::string>> options);
        Options(const int argc, char *argv[]);
        Options(
            const int argc, char *argv[],
            std::vector<std::vector<std::string>> custom_options
        );
        void set_options(const int argc, char *argv[]);
        std::vector<std::string> keys(void);
        std::unordered_map<std::string, int> all_options(void);
    };
}
#endif
