#ifndef split_h
#define split_h

#include <vector>
#include <string>

namespace util
{
	// ��������w�肵�������ŕ������������񃊃X�g�ɂ��ĕԂ�
	std::vector<std::string> split(const std::string& str, char del);
}

#endif // !split_h