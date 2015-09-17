#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <map>
#include <string>
#include "screen.h"

class Director
{
public:
	static Director* getDirector();

	void addScreen(const char* name, Screen* screen);
	void removeScreen(const char* name);

	const char* changeScreen(const char* name);
	Screen* currentScreen();

private:
	Director();

	typedef std::map<std::string, Screen*> ScreenContiner;
	
	ScreenContiner _screenCollection;
	ScreenContiner::iterator _currentScreen;
};

inline Director::Director()
{
	_currentScreen = _screenCollection.end();
}

inline Director* Director::getDirector()
{
	static Director director;
	return &director;
}

inline void Director::addScreen(const char* name, Screen* screen)
{
	if(!screen->init())
		return ;

	_screenCollection[name] = screen;

	if(_currentScreen == _screenCollection.end())
		_currentScreen = _screenCollection.begin();
}

inline void Director::removeScreen(const char* name)
{
	ScreenContiner::iterator it = _screenCollection.find(name);

	if(it == _screenCollection.end())
		return ;

	if(it == _currentScreen)
		_currentScreen = _screenCollection.begin();

	_screenCollection.erase(it);
}

inline const char* Director::changeScreen(const char* name)
{
	ScreenContiner::iterator it = _screenCollection.find(name);

	if(it == _screenCollection.end())
		return 0;

	const char* oldScreen = _currentScreen->first.c_str();

	_currentScreen->second->end();
	_currentScreen = it;
	_currentScreen->second->begin();

	return oldScreen;
}

inline Screen* Director::currentScreen()
{
	if(_currentScreen != _screenCollection.end())
		return _currentScreen->second;

	return 0;
}

#endif
