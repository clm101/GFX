#include <memory>
#include <vector>

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "UIBase.h"

struct Dimensions {
	Dimensions(std::int32_t w, std::int32_t h) : nWidth(w), nHeight(h) {}
	std::int32_t nWidth;
	std::int32_t nHeight;
};

class UIManager : public UIBase {
public:
	UIManager(uib::Rect r) noexcept;
	~UIManager() noexcept override = default;
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
	operator ElementType() override { return ElementType::UIManager; }
	void draw(ID2D1DeviceContext* ptrContext) noexcept override;
	void split_panel(Pos, SplitType) noexcept;
private:
	std::unique_ptr<UIBase> ptrFirst;
	std::unique_ptr<UIBase> ptrSecond;

	enum class WhichPanel {
		First,
		Second
	};
	template<typename T>
	static void find_and_split_panel_util(T* ptr, const Pos& pos, const SplitType& st) noexcept;
	static void create_zone_split_panel(std::unique_ptr<UIBase>& ptr, const SplitType& st) noexcept;
	static void find_and_split_panel(UIBase* ptr, const Pos& pos, const SplitType& st) noexcept;
};

template<typename T>
void UIManager::find_and_split_panel_util(T* ptr, const Pos& pos, const SplitType& st) noexcept {
	if (ptr->ptrFirst->contains_cursor(pos)) {
		switch ((ElementType) * (ptr->ptrFirst.get())) {
		case ElementType::Panel:
		{
			create_zone_split_panel(ptr->ptrFirst, st);
			break;
		}
		case ElementType::Zone:
		{
			find_and_split_panel(ptr->ptrFirst.get(), pos, st);
			break;
		}
		}
	}
	else {
		switch ((ElementType) * (ptr->ptrSecond.get())) {
		case ElementType::Panel:
		{
			create_zone_split_panel(ptr->ptrSecond, st);
			break;
		}
		case ElementType::Zone:
		{
			find_and_split_panel(ptr->ptrSecond.get(), pos, st);
			break;
		}
		}
	}
}

#endif