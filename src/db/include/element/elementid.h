#ifndef ELEMENTID_H
#define ELEMENTID_H
#include <cstdint>
#include <atomic>
#include <iostream>

class Element;
class ElementId 
{
public:
    static const int64_t INVALID_ID = -1;

    ElementId();
    static ElementId createNewId();

    bool operator==(const ElementId& other) const { return m_id == other.m_id; }
    bool operator!=(const ElementId& other) const { return m_id != other.m_id; }
    bool operator<(const ElementId& other) const { return m_id < other.m_id;}
    void operator=(const ElementId& other) { m_id = other.m_id; }
    bool isValid() const { return m_id != INVALID_ID; }
 
    friend std::ostream& operator<<(std::ostream& os, const ElementId& elementId) 
    {
        os << elementId.m_id;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ElementId& elementId) 
    {
        is >> elementId.m_id;
        return is;
    }

    int64_t getId() const { return m_id; }

private:
    explicit ElementId(int64_t id) : m_id(id) {}

private:
    int64_t m_id;
};


namespace std 
{
    template <>
    struct hash<ElementId> 
    {
        std::size_t operator()(const ElementId& eid) const 
        {
            return std::hash<int64_t>()(eid.getId());
        }
    };
}

#endif // !ELEMENTID_H