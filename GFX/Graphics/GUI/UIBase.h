#ifndef UI_BASE_H
#define UI_BASE_H

#include <d2d1.h>
#include <d2d1_1.h>
#include <memory>

namespace uib {
	struct Rect {
		std::int32_t nLeft;
		std::int32_t nTop;
		std::int32_t nRight;
		std::int32_t nBottom;
	};
}

class UIBase {
	friend class UIManager;
	friend class Zone;
	friend class Panel;
public:
	typedef std::pair<std::int32_t, std::int32_t> Pos;
	uib::Rect dim;
	virtual void draw(ID2D1DeviceContext*) = 0;
	virtual ~UIBase() noexcept = default;
	enum class SplitType {
		Horizontal,
		Vertical
	};
	enum class ElementType {
		UIManager,
		Zone,
		Panel
	};
	virtual operator ElementType() = 0;
	virtual bool contains_cursor(Pos) noexcept { return true; }
	virtual bool cursor_in_resize_region(const Pos& pos) const noexcept;
};

class Panel : public UIBase {
	friend class UIManager;
public:
	Panel(const uib::Rect dim_in, const UIBase* parent = nullptr) noexcept;
	~Panel() noexcept override;
	void draw(ID2D1DeviceContext* ptrContext) override;
	operator ElementType() override { return ElementType::Panel; }
private:
	struct {
		float r;
		float g;
		float b;
		float a = 1.f;
	} color;
	//uib::Rect dim;
	ID2D1SolidColorBrush* ptrBrush;
	bool contains_cursor(Pos) noexcept override;
	void set_dim(uib::Rect dim_in) noexcept;
};


class Zone : public UIBase {
	friend class UIManager;
private:
	//uib::Rect dim;
	std::unique_ptr<UIBase> ptrFirst;
	std::unique_ptr<UIBase> ptrSecond;
	bool contains_cursor(Pos) noexcept override;
	void find_and_split_panel(const Pos&, const SplitType&) noexcept;
public:
	Zone(const uib::Rect dim_in, UIBase* ptrFirst_in = nullptr, UIBase* ptrSecond_in = nullptr) noexcept;
	void draw(ID2D1DeviceContext* ptrContext) override;
	operator ElementType() override { return ElementType::Zone; }
	bool cursor_in_resize_region(const Pos& pos) const noexcept override;
};

#endif