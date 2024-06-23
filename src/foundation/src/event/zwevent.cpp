#include <include/event/zwevent.h>


void EventManager::addListener(const std::string& eventName, std::shared_ptr<EventCallback> callback, int priority)
{
    m_listeners[eventName].emplace_back(callback, priority);
   
    std::sort(m_listeners[eventName].begin(), m_listeners[eventName].end(),
        [](const ListenerPriorityPair& a, const ListenerPriorityPair& b) 
        {
            return a.second > b.second;
        });
}

void EventManager::removeListener(const std::string& eventName, std::shared_ptr<EventCallback> callback)
{
    auto& listenerList = m_listeners[eventName];

    listenerList.erase(std::remove_if(listenerList.begin(), listenerList.end(),
        [&](const ListenerPriorityPair& pair) 
        {
            return pair.first == callback;
        }), listenerList.end());
}

void EventManager::sendEvent(const Event& event)
{
    auto& listenerList = m_listeners[event.getName()];

    for (const auto& listener : listenerList) 
    {
        if (!listener.first)
            return;
        (*listener.first)(event);
    }
}