#pragma once

#include <string>
namespace clfps {
	class Map
	{
	private:
		int m_width;
		int m_height;
		std::wstring m_mapdata;
	public:
		Map(int, int);
		~Map();
		char getchar(int);
		wchar_t& get(int);
		bool available(int, int);
	};
}

