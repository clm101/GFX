#include "UIBase.h"
#include "../clmGraphics.h"
#include "../DxgiInfoManager.h"
#include <immintrin.h>
#include <array>
#include <random>

Panel::Panel(const uib::Rect dim_in, const UIBase* parent) noexcept {
	dim = dim_in;
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
	D2D1_RECT_F rect = { (float)dim.nLeft, (float)dim.nTop,
		(float)dim.nRight, (float)dim.nBottom };

	ptrContext->FillRectangle(rect, ptrBrush);
	return;
}

bool Panel::contains_cursor(const Pos& pos) const noexcept {
	return ((pos.first > dim.nLeft) && (pos.first < dim.nRight)) &&
		((pos.second > dim.nTop) && (pos.second < dim.nBottom));
}

// Over-engineered getting whether or not cursor is in the resize region
// This can be extended to determining whether or not the cursor is in a panel, the only thing that changes is the nThreshold comparison
void Panel::cursor_in_resize_region(const Pos& pos, std::vector<UIResize>& v) const noexcept {
	constexpr std::int32_t nThreshold = 5;

	__m128i mPos = _mm_set_epi32(pos.first, pos.first, pos.second, pos.second);
	__m128i mBorders = _mm_set_epi32(dim.nLeft, dim.nRight, dim.nTop, dim.nBottom);
	__m128i mDist = _mm_sub_epi32(mPos, mBorders);
	mDist = _mm_abs_epi32(mDist);

	/*
	0: Bottom
	1: Top
	2: Right
	3: Left
	*/
	std::array<std::int32_t, 4> aDists = { _mm_extract_epi32(mDist, 0), _mm_extract_epi32(mDist, 1),
											_mm_extract_epi32(mDist, 2), _mm_extract_epi32(mDist, 3) };
	std::int32_t nMin = aDists[0];
	size_t nIndex = 0;
	for (size_t i = 1; i < 4; i++) {
		if (aDists[i] < nMin) {
			nMin = aDists[i];
			nIndex = i;
		}
	}
	if (nMin < nThreshold) {
		switch (nIndex) {
		case 0:
			[[fallthrough]];
		case 1:
		{
			v.emplace_back(UIResize{ true, UIBase::ResizeDirection::Vertical });
			break;
		}
		case 2:
			[[fallthrough]];
		case 3:
		{
			v.emplace_back(UIResize{ true, UIBase::ResizeDirection::Horizontal });
			break;
		}
		}
	}

	return;
}

void Panel::set_dim(uib::Rect dim_in) noexcept {
	dim = dim_in;
}