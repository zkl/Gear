#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <vector>

typedef bool (*EventWatcher)(int eventId, void* data, void* parm);

class EventHandler
{
public:
	static EventHandler* instance();

	void setMaxEventId(int max);
	void addEventWather(int id, EventWatcher watcher, void* data = 0);
	void dispatch(int id, void* param = 0);

private:
	EventHandler();
	struct Event
	{
		void* data;
		EventWatcher watcher;
	};

	std::vector< std::vector<Event> > _eventWathers;
};

inline EventHandler::EventHandler()
{
}

inline EventHandler* EventHandler::instance()
{
	static EventHandler handler ;
	return &handler;
}

inline void EventHandler::setMaxEventId(int max)
{
	for(int i=_eventWathers.size(); i<max; i++)
		_eventWathers.push_back(std::vector<Event>());
}

inline void EventHandler::addEventWather(int id, EventWatcher watcher, void* data)
{
	Event e;
	e.data = data;
	e.watcher = watcher;
	_eventWathers[id].push_back(e);
}

inline void EventHandler::dispatch(int id, void* param)
{
	std::vector<Event>& watchers = _eventWathers[id];

	for(unsigned int i=0; i<watchers.size(); i++)
		watchers[id].watcher(id, watchers[i].data, param);
}
#endif
