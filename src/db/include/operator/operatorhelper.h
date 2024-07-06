#ifndef OPERATORHELPER_H
#define OPERATORHELPER_H

#include <glm/glm.hpp>
#include <ostream>
#include <sstream>

// glm::vec3
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

std::istream& operator>>(std::istream& is, glm::vec3& vec)
{
    // 格式化输入：期望输入为 (x, y, z)
    char discard;
    is >> discard; // 读取左括号 '('
    is >> vec.x;
    is >> discard; // 读取逗号 ','
    is >> vec.y;
    is >> discard; // 读取逗号 ','
    is >> vec.z;
    is >> discard; // 读取右括号 ')'
    return is;
}

#endif // !OPERATORHELPER_H
