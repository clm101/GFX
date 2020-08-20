#include <queue>
#include "Mouse.h"

Mouse::Mouse() noexcept {
	bIsLeftPressed = false;
	bIsRightPressed = false;
	posCursor = { 0, 0 };
	hCursor = 
}

const Mouse::Pos& Mouse::get_pos() const noexcept {
	return posCursor;
}

std::int32_t Mouse::get_pos_x() const noexcept {
	return posCursor.first;
}

std::int32_t Mouse::get_pos_y() const noexcept {
	return posCursor.second;
}

bool Mouse::get_lbstate() const noexcept {
	return bIsLeftPressed;
}

bool Mouse::get_rbstate() const noexcept {
	return bIsRightPressed;
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

Mouse::Event::Event(Type t, Pos p) noexcept : t(t), posCursor(p) {}