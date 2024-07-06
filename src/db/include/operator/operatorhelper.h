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
    // ��ʽ�����룺��������Ϊ (x, y, z)
    char discard;
    is >> discard; // ��ȡ������ '('
    is >> vec.x;
    is >> discard; // ��ȡ���� ','
    is >> vec.y;
    is >> discard; // ��ȡ���� ','
    is >> vec.z;
    is >> discard; // ��ȡ������ ')'
    return is;
}

#endif // !OPERATORHELPER_H
