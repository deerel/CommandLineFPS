#pragma once
#include <chrono>

#include "Screen.h"
#include "Player.h"
#include "Map.h"

namespace clfps {
	class Engine
	{
	private:
		bool is_running = false;
		std::chrono::time_point<std::chrono::system_clock> m_time;
		float m_deltatime;
		float m_render_depth;
		Screen * m_screen = nullptr;
		Player * m_player = nullptr;
		Map * m_map = nullptr;

		inline float calc_deltatime();
		void update_screen();
		void update_screen_hud();
	public:
		Engine(int, int);
		~Engine();
		void player(Player * player);
		void map(Map * map);
		void update();
		void draw();
		float deltatime() const;
		bool key_pressed(unsigned short) const;
	};
}

