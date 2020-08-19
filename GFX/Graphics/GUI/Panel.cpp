#include "UIBase.h"
#include "../clmGraphics.h"
#include "../DxgiInfoManager.h"

#include <random>

Panel::Panel(const uib::Rect& dim_in) noexcept : dim(dim_in) {
	color = { getrandom(), getrandom(), getrandom(), 1.0f };
	ptrBrush = nullptr;
};

Panel::~Panel() noexcept {
	SafeRelease(ptrBrush);
}

void Panel::draw(ID2D1DeviceContext* ptrContext) {
	if (ptrBrush == nullptr) {
		static HRESULT hr = S_OK;
		CLM_EXCEPT_GFX_HR(ptrContext->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g,
			color.b, color.a), &ptrBrush));
	}
	static D2D1_RECT_F rect = { (float)dim.nLeft, (float)dim.nTop,
		(float)dim.nRight, (float)dim.nBottom };

	ptrContext->FillRectangle(rect, ptrBrush);
	return;
}