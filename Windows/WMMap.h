#ifndef WMMAP_H
#define WMMAP_H

#include <string>
#include <unordered_map>
#include "Windows.h"

#define REGISTER_MESSAGE(msg) {msg, L#msg}

class WindowsMessages {
private:
	std::unordered_map<DWORD, std::wstring> umMessages;
public:
	WindowsMessages() noexcept;
	~WindowsMessages() noexcept;

	std::wstring operator()(DWORD, WPARAM, LPARAM) const noexcept;
};

#endif