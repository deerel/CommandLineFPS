#pragma once

#include <Windows.h>

#define FBLACK			0x0
#define FBLUE			0x1
#define FGREEN			0x2
#define FCYAN			0x3
#define FRED			0x4
#define FPURPLE			0x5
#define FYELLOW			0x6
#define FWHITE			0x7
#define FGRAY			0x8
#define FLIGHT_BLUE		0x9
#define FLIGHT_GREEN	0xA
#define FLIGHT_CYAN		0xB
#define FLIGHT_RED		0xC
#define FLIGHT_PURPLE	0xD
#define FLIGHT_YELLOW	0xE
#define FBRIGHT_WHITE	0xF

#define BBLACK			0x00
#define BBLUE			0x10
#define BGREEN			0x20
#define BAQUA			0x30
#define BRED			0x40
#define BPURPLE			0x50
#define BYELLOW			0x60
#define BWHITE			0x70
#define BGRAY			0x80
#define BLIGHT_BLUE		0x90
#define BLIGHT_GREEN	0xA0
#define BLIGHT_RED		0xB0
#define BLIGHT_PURPLE	0xC0
#define BLIGHT_YELLOW	0xD0
#define BBRIGHT_WHITE	0xE0

namespace clfps {

	struct Pixel
	{
		wchar_t symbol;
		WORD forground;
		WORD background;
	};

	class Screen
	{
	private:
		int m_width;
		int m_height;
		wchar_t *m_data;
		WORD * m_color;
		HANDLE m_Console;
		DWORD dwBytesWritten = 0;
	public:
		Screen(int, int);
		~Screen();
		void draw();
		int width() const;
		int height() const;
		void set(int, wchar_t);
		void set(int, wchar_t, WORD);
		wchar_t * get() { return m_data; };
		WORD get_wall_color(float distance, float max);
		WORD get_floor_color();
		WORD get_boundary_color();
	};
}

