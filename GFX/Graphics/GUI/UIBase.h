#include <d2d1.h>
#include <d2d1_1.h>
#include <memory>

#ifndef UI_BASE_H
#define UI_BASE_H

namespace uib {
	struct Rect {
		std::int32_t nLeft;
		std::int32_t nTop;
		std::int32_t nRight;
		std::int32_t nBottom;
	};
}

class UIElementBase {
public:
	virtual void draw(ID2D1DeviceContext*) = 0;
	virtual ~UIElementBase() noexcept = default;
};

class Panel : public UIElementBase {
public:
	Panel(const uib::Rect& dim_in) noexcept;
	~Panel() noexcept override;
	void draw(ID2D1DeviceContext* ptrContext) override;
private:
	struct {
		float r;
		float g;
		float b;
		float a = 1.f;
	} color;
	uib::Rect dim;
	std::shared_ptr<UIElementBase> ptrParent;
	ID2D1SolidColorBrush* ptrBrush;

	
};

#endif