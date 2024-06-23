#ifndef ZWEVENT_H
#define ZWEVENT_H
#include <functional>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

class Event
{
public:
    virtual ~Event() = default;
    virtual std::string getName() const = 0;
};


class EventListener 
{
public:
    virtual ~EventListener() = default;
    virtual void onEvent(const Event& event) = 0;
};

class EventManager
{
private:
    EventManager() = default;

public:
    using EventCallback = std::function<void(const Event&)>;
    using ListenerPriorityPair = std::pair<std::shared_ptr<EventCallback>, int>;

    void addListener(const std::string& eventName, std::shared_ptr<EventCallback> callback, int priority = 0);
    void removeListener(const std::string& eventName, std::shared_ptr<EventCallback> callback);
    void sendEvent(const Event& event);

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    static EventManager* getEventManager() 
    {
        static EventManager instance;
        return &instance;
    }

private:
    std::map<std::string, std::vector<ListenerPriorityPair>> m_listeners;
};

#endif // !ZWEVENT_H
