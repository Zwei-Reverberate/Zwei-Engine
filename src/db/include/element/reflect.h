#ifndef REFLECT_H
#define REFLECT_H

#include <include/geometry/basicshape/cuboid.h>
#include <include/operator/operatorhelper.h>
#include <include/graphic/graphicelement.h>
#include <include/element/element.h>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>

namespace ZwReflect
{
    constexpr int CLASS_NAME_SPLIT = 5;

    // 编译期序列化器
    template<typename T>
    constexpr std::string serialize(const T& obj)
    {
        constexpr auto metadata = T::getMetadata();
        std::stringstream ss;
        std::string className = typeid(T).name();
        className.erase(0, CLASS_NAME_SPLIT);
        ss << className << ' '; // 添加类型信息
        std::apply([&obj, &ss](auto&&... args)
            {
                ((ss << obj.*args.second << ' '), ...);
            }, metadata);
        return ss.str();
    }

    // 编译期反序列化器
    template<typename T>
    constexpr T deserialize(std::istringstream& ss)
    {
        T obj;
        constexpr auto metadata = T::getMetadata();
        std::apply([&obj, &ss](auto&&... args)
            {
                ((ss >> obj.*args.second), ...);
            }, metadata);
        return obj;
    }


    // 类型识别
    Element* deserialize(const std::string& str)
    {
        std::istringstream ss(str);
        std::string typeName;
        ss >> typeName;

        if (typeName == "Element")
        {
            Element element = deserialize<Element>(ss);
            return &element;
        }
        else if (typeName == "GraphicElement")
        {
            GraphicElement graphicElement = deserialize<GraphicElement>(ss);
            return &graphicElement;
        }
        else if (typeName == "Cuboid")
        {
            Cuboid cuboid = deserialize<Cuboid>(ss);
            return &cuboid;
        }
        return nullptr;
    }
}

#endif // !REFLECT_H
