#include "Application.h"

Application::Application(const wchar_t* wWindowName, short sWidth, short sHeight) {
	ptrWnd = std::make_unique<Window>(wWindowName, sWidth, sHeight);
	tmrTimer.set();
}

int Application::Start() {
	while (true) {
		if (const auto ret = Window::ProcessMessages()) {
			return *ret;
		}
		DoFrame((float)tmrTimer.peek());
	}
}

void Application::DoFrame(const float fTime) const {
	ptrWnd->gfx().BeginFrame(fTime);

	ptrWnd->gfx().EndFrame();
}