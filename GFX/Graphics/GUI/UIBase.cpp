#include "UIBase.h"

void UIBase::cursor_in_resize_region(const Pos& pos, std::vector<UIResize>& v) const noexcept {
		constexpr std::int32_t nThreshold = 5;
		if (((pos.first >= dim.nLeft) && (pos.first <= (dim.nLeft + nThreshold))) ||
			((pos.first <= dim.nRight) && (pos.first >= (dim.nRight - nThreshold)))) {
			v.emplace_back(UIResize{ true, UIBase::ResizeDirection::Horizontal });
		}
		if (((pos.second >= dim.nTop) && (pos.second <= (dim.nTop + nThreshold))) ||
			((pos.second <= dim.nBottom) && (pos.second >= (dim.nBottom - nThreshold)))) {
			v.emplace_back(UIResize{ true, UIBase::ResizeDirection::Vertical });
		}

	return;
}