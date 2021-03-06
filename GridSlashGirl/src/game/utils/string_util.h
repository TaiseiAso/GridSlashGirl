#ifndef split_h
#define split_h

#include <vector>
#include <string>

namespace util
{
	// 文字列を指定した文字で分割した文字列リストにして返す
	std::vector<std::string> split(const std::string& str, char del);
}

#endif // !split_h