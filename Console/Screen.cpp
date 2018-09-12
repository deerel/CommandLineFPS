#include "Screen.h"



clfps::Screen::Screen(int width, int height) : m_width(width), m_height(height)
{
	m_data = new wchar_t[m_width*m_height];
	m_Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_Console);

}


clfps::Screen::~Screen()
{
	delete[] m_data;
}

void clfps::Screen::draw()
{
	// Display Frame
	set(m_width * m_height - 1, '\0');
	WriteConsoleOutputCharacter(m_Console, m_data, m_width * m_height, { 0,0 }, &dwBytesWritten);
}

int clfps::Screen::width() const
{
	return m_width;
}

int clfps::Screen::height() const
{
	return m_height;
}

void clfps::Screen::set(int index, wchar_t ch)
{
	m_data[index] = ch;
}
