#include "SGPathUtils.h"
using namespace std;
std::string SGPathUtils::getDirectory(const std::string& fullPath)
{
    auto pos = fullPath.rfind("/");
    if (string::npos != pos)
    {
        return fullPath.substr(0,pos);
    }
    return "";
}
