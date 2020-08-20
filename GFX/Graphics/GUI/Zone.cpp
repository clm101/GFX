#include "UIBase.h"
#include "UIManager.h"

Zone::Zone(const uib::Rect dim_in, UIBase* ptrFirst_in, UIBase* ptrSecond_in) noexcept {
	dim = dim_in;
	ptrFirst.reset(ptrFirst_in);
	ptrSecond.reset(ptrSecond_in);
}

void Zone::draw(ID2D1DeviceContext* ptrContext) {
	if (ptrFirst != nullptr) {
		ptrFirst->draw(ptrContext);
	}
	if (ptrSecond != nullptr) {
		ptrSecond->draw(ptrContext);
	}
}

bool Zone::contains_cursor(const Pos& pos) const noexcept {
	return ((pos.first > dim.nLeft) && (pos.first < dim.nRight)) &&
		((pos.second > dim.nTop) && (pos.second < dim.nBottom));
}

void Zone::cursor_in_resize_region(const Pos& pos, std::vector<UIResize>& v) const noexcept {
	if (ptrFirst != nullptr) {
		ptrFirst->cursor_in_resize_region(pos, v);
	}
	if (ptrSecond != nullptr) {
		ptrSecond->cursor_in_resize_region(pos, v);
	}
}