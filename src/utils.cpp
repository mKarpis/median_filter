#include "utils.h"
#include <sstream>

std::string Utils::floatToString(const float value)
{
    std::stringstream out;
    out << value;
    return out.str();
}

std::string Utils::intToString(const int value)
{
    std::stringstream out;
    out << value;
    return out.str();
}


