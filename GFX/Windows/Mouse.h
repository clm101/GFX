#include <queue>
#include <cstdint>

#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
	typedef std::pair<std::int32_t, std::int32_t> Pos;
public:
	Mouse() noexcept;
	~Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	void on_left_click(Pos pos) noexcept;
	void on_left_release(Pos pos) noexcept;
	void on_right_click(Pos pos) noexcept;
	void on_right_release(Pos pos) noexcept;
	void on_move(Pos pos) noexcept;

private:
	static constexpr std::uint8_t nBufferSize = 16u;
	void trim_buffer() noexcept;

	class Event {
	private:
		Pos posCursor;
	public:
		enum class Type {
			LClick,
			LRelease,
			RClick,
			RRelease,
			Move
		};

		Event(Type t, Pos p) noexcept;
		~Event() = default;
		Event(const Event&) = delete;
		Event& operator=(const Event&);
	};

	bool bIsLeftPressed;
	bool bIsRightPressed;
	Pos posCursor;
	std::queue<Event> buffer;
};

#endif