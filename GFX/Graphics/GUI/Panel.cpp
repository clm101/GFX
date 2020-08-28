#include "UIBaseElem.h"
#include "../clmGraphics.h"
#include "../DxgiInfoManager.h"
#include <immintrin.h>
#include <array>
#include <cassert>
#include "../../clmRandom.h"

//Panel::Panel(const uib::Rect dim_in, const UIBase* parent) noexcept {
//	dim.set_sides_single(dim_in);
//	color = { getrandom(), getrandom(), getrandom(), 1.0f };
//	ptrBrush = nullptr;
//};

Panel::~Panel() noexcept {
	SafeRelease(ptrBrush);
}

void Panel::draw(ID2D1DeviceContext* ptrContext) {
	if (ptrBrush == nullptr) {
		static HRESULT hr = S_OK;
		CLM_EXCEPT_GFX_HR(ptrContext->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g,
			color.b, color.a), &ptrBrush));
	}
	assert(rBorder.get_ptr(uis::Left) != nullptr);
	assert(rBorder.get_ptr(uis::Top) != nullptr);
	assert(rBorder.get_ptr(uis::Right) != nullptr);
	assert(rBorder.get_ptr(uis::Bottom) != nullptr);
	D2D1_RECT_F rect = { (float)rBorder[uis::Left], (float)rBorder[uis::Top],
		(float)rBorder[uis::Right], (float)rBorder[uis::Bottom] };

	ptrContext->FillRectangle(rect, ptrBrush);
	return;
}

//bool Panel::contains_cursor(const Pos& pos) const noexcept {
//	return ((pos.first > (*ptrDim)[Side::Left]) && (pos.first < (*ptrDim)[Side::Right])) &&
//		((pos.second > (*ptrDim)[Side::Top]) && (pos.second < (*ptrDim)[Side::Bottom]));
//}

// Over-engineered getting whether or not cursor is in the resize region
// This can be extended to determining whether or not the cursor is in a panel, the only thing that changes is the nThreshold comparison
//void Panel::cursor_in_resize_region(const Pos& pos, std::vector<UIResize>& v) const noexcept {
//	constexpr std::int32_t nThreshold = 5;
//
//	__m128i mPos = _mm_set_epi32(pos.first, pos.first, pos.second, pos.second);
//	__m128i mBorders = _mm_set_epi32((*ptrDim)[Side::Left], (*ptrDim)[Side::Right], (*ptrDim)[Side::Top], (*ptrDim)[Side::Bottom]);
//	__m128i mDist = _mm_sub_epi32(mPos, mBorders);
//	mDist = _mm_abs_epi32(mDist);
//
//	/*
//	0: Bottom
//	1: Top
//	2: Right
//	3: Left
//	*/
//	std::array<std::int32_t, 4> aDists = { _mm_extract_epi32(mDist, 0), _mm_extract_epi32(mDist, 1),
//											_mm_extract_epi32(mDist, 2), _mm_extract_epi32(mDist, 3) };
//	std::int32_t nMin = aDists[0];
//	size_t nIndex = 0;
//	for (size_t i = 1; i < 4; i++) {
//		if (aDists[i] < nMin) {
//			nMin = aDists[i];
//			nIndex = i;
//		}
//	}
//	if (nMin < nThreshold) {
//		switch (nIndex) {
//		case 0: v.emplace_back(UIResize{ true, UIBase::Side::Bottom });	break;
//		case 1: v.emplace_back(UIResize{ true, UIBase::Side::Top });	break;
//		case 2:	v.emplace_back(UIResize{ true, UIBase::Side::Right });	break;
//		case 3: v.emplace_back(UIResize{ true, UIBase::Side::Left });	break;
//		}
//	}
//
//	return;
//}

//void Panel::set_dim(Side s, std::int32_t n) noexcept {
//	dim.set_side_single(s, n);
//}
//
//void Panel::set_dim(Side s, std::shared_ptr<std::int32_t> ptr) noexcept {
//	dim.set_side_global(s, ptr);
//}

void Panel::set_dim(UI::Side side, std::int32_t n) noexcept {
	rBorder.set_ptr(side, std::make_shared<std::int32_t>(n));
}

void Panel::set_dim(UI::Side side, std::shared_ptr<std::int32_t> ptr) noexcept {
	rBorder.set_ptr(side, std::move(ptr));
}

void Panel::set_dims(UI::Rect&& r_in) noexcept {
	rBorder = r_in;
}