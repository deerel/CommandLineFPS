#include "Screen.h"


clfps::Screen::Screen(int width, int height) : m_width(width), m_height(height)
{
	m_data = new wchar_t[m_width*m_height];
	m_color = new WORD[m_width*m_height];
	m_Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(m_Console);

}


clfps::Screen::~Screen()
{
	delete[] m_data;
	delete[] m_color;
}

void clfps::Screen::draw()
{
	// Display Frame
	set(m_width * m_height - 1, '\0');
	WriteConsoleOutputAttribute(m_Console, m_color, m_width * m_height, { 0,0 }, &dwBytesWritten);
	//WriteConsoleOutputCharacter(m_Console, m_data, m_width * m_height, { 0,0 }, &dwBytesWritten);
	
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
	m_color[index] = FGRAY | BBLACK;
}

void clfps::Screen::set(int index, wchar_t ch, WORD color)
{
	m_data[index] = ch;
	m_color[index] = color;
}

WORD clfps::Screen::get_wall_color(float distance, float max)
{
	WORD color = ' ';
	if (distance <= max / 7.0f)			color = FGREEN | BGRAY;			// Close
	else if (distance <= max / 6.0f)	color = FGREEN | BGRAY;
	else if (distance <= max / 5.0f)	color = FGREEN | BGRAY;
	else if (distance <= max / 4.0f)	color = FGREEN | BBLACK;	
	else if (distance < max / 3.0f)		color = FGREEN | BBLACK;
	else if (distance < max / 2.0f)		color = FGREEN | BBLACK;
	else if (distance < max)			color = FGREEN | BBLACK;
	else								color = FBLACK | BBLACK;			// Too far away
	return color;
}

WORD clfps::Screen::get_floor_color()
{
	return (WORD)(FBLUE | BGRAY);
}

WORD clfps::Screen::get_boundary_color()
{
	return (WORD)(FBLACK | BBLACK);
}
