#include "UIManager.h"

UIManager::UIManager(uib::Rect r) noexcept
{
	dim = r;
	ptrFirst = std::make_unique<Panel>(dim);
	ptrSecond = nullptr;
}

void UIManager::draw(ID2D1DeviceContext* ptrContext) noexcept {
	if (ptrFirst != nullptr) {
		ptrFirst->draw(ptrContext);
	}
	if (ptrSecond != nullptr) {
		ptrSecond->draw(ptrContext);
	}
}

void UIManager::create_zone_split_panel(std::unique_ptr<UIBase>& ptr, const SplitType& st) noexcept {
	uib::Rect rZone{ ptr->dim };
	uib::Rect rFirst{};
	uib::Rect rSecond{};
	switch (st) {
	case SplitType::Horizontal:
	{
		rFirst = { rZone.nLeft, rZone.nTop, rZone.nRight, (rZone.nBottom + rZone.nTop) / 2 };
		rSecond = { rZone.nLeft, (rZone.nBottom + rZone.nTop) / 2, rZone.nRight, rZone.nBottom};
		break;
	}
	case SplitType::Vertical:
	{
		rFirst = { rZone.nLeft, rZone.nTop, (rZone.nRight + rZone.nLeft) / 2, rZone.nBottom };
		rSecond = { (rZone.nRight + rZone.nLeft) / 2, rZone.nTop, rZone.nRight, rZone.nBottom };
		break;
	}
	}

	Panel* ptrTmp = (Panel*)ptr.release();
	ptrTmp->set_dim(rFirst);
	ptr = std::make_unique<Zone>(rZone);
	((Zone*)ptr.get())->ptrFirst.reset(ptrTmp);
	((Zone*)ptr.get())->ptrSecond = std::make_unique<Panel>(rSecond);
	ptrTmp = nullptr;
}



void UIManager::find_and_split_panel(UIBase* ptr, const Pos& pos, const SplitType& st) noexcept {
	ElementType t = (ElementType)*ptr;
	switch ((ElementType)*ptr) {
	case ElementType::UIManager:
	{
		UIManager* ptrTmp = (UIManager*)ptr;
		find_and_split_panel_util(ptrTmp, pos, st);
		break;
	}
	case ElementType::Zone:
	{
		Zone* ptrTmp = (Zone*)ptr;
		find_and_split_panel_util(ptrTmp, pos, st);
		break;
	}
	default:
		break;
	}
}

void UIManager::split_panel(Pos pos, SplitType st) noexcept {
	if (ptrSecond == nullptr) {
		Panel* ptrFirstTmp = (Panel*)ptrFirst.get();
		const uib::Rect rOldDim = ptrFirstTmp->dim;
		switch (st) {
		case SplitType::Vertical:
		{
			ptrFirstTmp->set_dim({
				rOldDim.nLeft, rOldDim.nTop,
				(rOldDim.nRight + rOldDim.nLeft) / 2, rOldDim.nBottom });
			ptrSecond = std::make_unique<Panel>(uib::Rect{
				(rOldDim.nRight + rOldDim.nLeft) / 2, rOldDim.nTop,
				rOldDim.nRight, rOldDim.nBottom });
			break;
		}
		case SplitType::Horizontal:
		{
			ptrFirstTmp->set_dim({
				rOldDim.nLeft, rOldDim.nTop,
				rOldDim.nRight, (rOldDim.nBottom + rOldDim.nTop) / 2});
			ptrSecond = std::make_unique<Panel>(uib::Rect{
				rOldDim.nLeft, (rOldDim.nBottom + rOldDim.nTop) / 2,
				rOldDim.nRight, rOldDim.nBottom });
			break;
		}
		}
	}
	else {
		find_and_split_panel(this, pos, st);
	}
	return;
}