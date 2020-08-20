#include "Application.h"
#include "Windows/clmWinStuff.h"
#include "Windows/Mouse.h"

Application::Application(const wchar_t* wWindowName, short sWidth, short sHeight) {
	ptrWnd = std::make_unique<Window>(wWindowName, sWidth, sHeight);
	tmrTimer.set();
}

int Application::Start() {
	ptrWnd->ui().split_panel({ 100, 100 }, UIBase::SplitType::Vertical);
	ptrWnd->ui().split_panel({ 100, 100 }, UIBase::SplitType::Vertical);
	ptrWnd->ui().split_panel({ 100, 100 }, UIBase::SplitType::Horizontal);
	while (true) {
		if (const auto ret = Window::ProcessMessages()) {
			return *ret;
		}
		process_input();
		DoFrame((float)tmrTimer.peek());
	}
}

void Application::process_input() {
	while (const auto e = ptrWnd->ptrMouse->get_next_event()) {
		if (e->get_type() == Mouse::Event::Type::Move) {
			Mouse::Pos posCursor = e->get_cursor_pos();
			ptrWnd->ptrMouse->update_cursor_pos(posCursor);
			if (ptrWnd->ui().cursor_in_resize_region(posCursor)) {
				ptrWnd->ptrMouse->update_cursor(Mouse::CursorType::Resize);
			}
			else {
				ptrWnd->ptrMouse->update_cursor(Mouse::CursorType::Normal);
			}
		}
		else if (e->get_type() == Mouse::Event::Type::LClick) {
			int breakpoint = 3;
		}
	}
}

void Application::DoFrame(const float fTime) const {
	ptrWnd->gfx().BeginFrame(ptrWnd->ui());

	ptrWnd->gfx().EndFrame();
}