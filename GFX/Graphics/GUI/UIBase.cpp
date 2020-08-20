#include "UIBase.h"

bool UIBase::cursor_in_resize_region(const Pos& pos) const noexcept {
	constexpr std::int32_t nThreshold = 5;
	bool bReturn = ((pos.first >= dim.nLeft) && (pos.first <= (dim.nLeft + nThreshold))) ||
		((pos.first <= dim.nRight) && (pos.first >= (dim.nRight - nThreshold))) ||
		((pos.second >= dim.nTop) && (pos.second <= (dim.nTop + nThreshold))) ||
		((pos.second <= dim.nBottom) && (pos.second >= (dim.nBottom - nThreshold)));

	return bReturn;
}