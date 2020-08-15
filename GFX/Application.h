#include "Windows/clmWinStuff.h"
#include "clmTimer.h"
#include <memory>

#ifndef APPLICATION_H
#define APPLICATION_H

class Application {
private:
	std::unique_ptr<Window> ptrWnd;
	clmTimer tmrTimer;
public:
	Application(const wchar_t*, short, short);
	Application(const Application&) = delete;
	Application& operator=(const Application) = delete;

	int Start();
	void DoFrame(const float) const;
};

#endif