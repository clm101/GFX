#include <queue>
#include "Mouse.h"

Mouse::Mouse() noexcept {
	bIsLeftPressed = false;
	bIsRightPressed = false;
	posCursor = { 0, 0 };
}

void Mouse::on_left_click(Pos pos) noexcept {
	buffer.emplace(Event::Type::LClick, pos );
	trim_buffer();
	return;
}

void Mouse::on_left_release(Pos pos) noexcept {
	buffer.emplace(Event::Type::LRelease, pos);
	trim_buffer();
	return;
}

void Mouse::on_right_click(Pos pos) noexcept {
	buffer.emplace(Event::Type::RClick, pos);
	trim_buffer();
	return;
}

void Mouse::on_right_release(Pos pos) noexcept {
	buffer.emplace(Event::Type::RRelease, pos);
	trim_buffer();
	return;
}

void Mouse::on_move(Pos pos) noexcept {
	buffer.emplace(Event::Type::Move, pos);
	trim_buffer();
	return;
}

void Mouse::trim_buffer() noexcept {
	while (buffer.size() > nBufferSize) {
		buffer.pop();
	}
}