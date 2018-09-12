#include "Map.h"



clfps::Map::Map(int width, int height) : m_width(width), m_height(height)
{
	// Create Map of world space # = wall block, . = space
	m_mapdata += L"################";
	m_mapdata += L"#..............#";
	m_mapdata += L"#.......########";
	m_mapdata += L"#..............#";
	m_mapdata += L"#......##......#";
	m_mapdata += L"#......##......#";
	m_mapdata += L"#..............#";
	m_mapdata += L"###............#";
	m_mapdata += L"##.............#";
	m_mapdata += L"#......####..###";
	m_mapdata += L"#......#.......#";
	m_mapdata += L"#......#.......#";
	m_mapdata += L"#..............#";
	m_mapdata += L"#......#########";
	m_mapdata += L"#..............#";
	m_mapdata += L"################";
}


clfps::Map::~Map()
{
}

int clfps::Map::width() const
{
	return m_width;
}

int clfps::Map::height() const
{
	return m_height;
}

char clfps::Map::getchar(int index)
{
	return m_mapdata.c_str()[index];
}

wchar_t& clfps::Map::get(int index)
{
	return m_mapdata[index];
}

bool clfps::Map::available(int x, int y)
{
	return getchar(x * m_width + y) != '#';
}
