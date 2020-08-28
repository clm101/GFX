#include "UIBaseElem.h"
#include "../../clmRandom.h"

UI::Rect::Rect() noexcept {
	for (size_t i = 0; i < 4; i++) {
		aBorders[i] = nullptr;
	}
}
UI::Rect::Rect(const Rect& r_in) noexcept {
	if (this != &r_in) {
		for (size_t i = 0; i < 4; i++) {
			aBorders[i] = r_in.aBorders[i];
		}
	}
}

UI::Rect& UI::Rect::operator=(const UI::Rect& r_in) noexcept {
	if (this != &r_in) {
		for (size_t i = 0; i < 4; i++) {
			if (aBorders[i] != r_in.aBorders[i]) {
				aBorders[i] = r_in.aBorders[i];
			}
		}
	}
	return *this;
}

UI::Rect::Rect(Rect&& r_in) noexcept {
	if (this != &r_in) {
		for (size_t i = 0; i < 4; i++) {
			if (aBorders[i] != r_in.aBorders[i]) {
				aBorders[i] = std::move(r_in.aBorders[i]);
				/*aBorders[i].reset(r_in.aBorders[i].get());
				r_in.aBorders[i].reset();*/
			}
		}
	}
}

UI::Rect& UI::Rect::operator=(Rect&& r_in) noexcept {
	if (this != &r_in) {
		for (size_t i = 0; i < 4; i++) {
			if (aBorders[i] != r_in.aBorders[i]) {
				aBorders[i] = std::move(r_in.aBorders[i]);
				/*aBorders[i].reset(r_in.aBorders[i].get());
				r_in.aBorders[i].reset();*/
			}
		}
	}
	return *this;
}

void UI::Rect::init_array_elem(UI::Side s, std::int32_t n) noexcept {
	aBorders[(std::int32_t)s] = std::make_shared<std::int32_t>(n);
	return;
}

void UI::Rect::init_array_elem(UI::Side s, std::shared_ptr<std::int32_t> ptr) noexcept {
	aBorders[(std::int32_t)s] = ptr;
	return;
}

std::int32_t& UI::Rect::operator[](UI::Side s) const noexcept {
	return *(aBorders[(std::int32_t)s]);
}

const std::shared_ptr<std::int32_t>& UI::Rect::get_ptr(UI::Side s) const noexcept {
	return aBorders[(std::int32_t)s];
}

void UI::Rect::set_ptr(UI::Side s, std::shared_ptr<std::int32_t>&& ptr) noexcept {
	aBorders[(std::int32_t)s] = ptr;
}

void UI::Rect::set_side(UI::Side s, std::int32_t n) noexcept {
	aBorders[(std::int32_t)s] = std::make_shared<std::int32_t>(n);
}

void UI::Rect::set_side(UI::Side s, std::shared_ptr<std::int32_t> ptr) noexcept {
	aBorders[(std::int32_t)s] = ptr;
}

/*********************************/
/*********** UIBaseElem **********/
/*********************************/

bool UIBaseElem::contains_cursor(const UI::Pos& pos) const noexcept {
	using uis = UI::Side;
	return ((pos.first > rBorder[uis::Left]) && (pos.first < rBorder[uis::Right])) &&
		((pos.second > rBorder[uis::Top]) && (pos.second < rBorder[uis::Bottom]));
}

void UIBaseElem::set_side(UI::Side s, std::int32_t n) noexcept {
	rBorder[s] = n;
}

void UIBaseElem::set_side(UI::Side s, std::shared_ptr<std::int32_t> ptr) noexcept {
	rBorder.set_ptr(s, std::move(ptr));
}