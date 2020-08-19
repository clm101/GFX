#include "UIManager.h"

UIManager::UIManager(uib::Rect r) noexcept
	:
	dim(r)
{
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