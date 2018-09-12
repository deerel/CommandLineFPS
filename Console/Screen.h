#pragma once

#include <Windows.h>

namespace clfps {
	class Screen
	{
	private:
		int m_width;
		int m_height;
		wchar_t *m_data;
		HANDLE m_Console;
		DWORD dwBytesWritten = 0;
	public:
		Screen(int, int);
		~Screen();
		void draw();
		int width() const;
		int height() const;
		void set(int, wchar_t);
	};
}

