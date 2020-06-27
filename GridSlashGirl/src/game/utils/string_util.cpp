#include "string_util.h"

namespace util
{
    std::vector<std::string> split(const std::string& str, char del) {
        int first = 0;
        int last = str.find_first_of(del);

        std::vector<std::string> result;

        while (first < static_cast<int>(str.size())) {
            std::string subStr(str, first, last - first);

            result.push_back(subStr);

            first = last + 1;
            last = str.find_first_of(del, first);

            if (last == std::string::npos) {
                last = str.size();
            }
        }

        return result;
    }
}