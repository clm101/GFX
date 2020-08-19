#include <memory>
#include <vector>
#include "UIBase.h"

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

struct Dimensions {
	Dimensions(std::int32_t w, std::int32_t h) : nWidth(w), nHeight(h) {}
	std::int32_t nWidth;
	std::int32_t nHeight;
};

class UIManager : public UIElementBase {
public:
	UIManager(uib::Rect r) noexcept;
	~UIManager() noexcept override = default;
	void draw(ID2D1DeviceContext* ptrContext) noexcept override;
private:
	uib::Rect dim;
	std::unique_ptr<UIElementBase> ptrFirst;
	std::unique_ptr<UIElementBase> ptrSecond;
};

#endif