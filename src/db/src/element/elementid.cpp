#include <include/element/elementid.h>

class IDManager 
{
public:
    static int64_t getNextId();

private:
    static std::atomic<int64_t> nextId;
};

std::atomic<int64_t> IDManager::nextId(0);

int64_t IDManager::getNextId() 
{
    return ++nextId;
}

ElementId::ElementId() : m_id(INVALID_ID) {}

ElementId ElementId::createNewId() 
{
    return ElementId(IDManager::getNextId());
}