#include <vector>
#include <utility>
#include <algorithm>

#include "Engine.h"



float clfps::Engine::calc_deltatime()
{
	auto time_now = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = time_now - m_time;
	m_time = time_now;
	return elapsedTime.count();
}

void clfps::Engine::update_screen()
{
	int x = 0;
	for (int x = 0; x < m_screen->width(); x++)
	{
		// For each column, calculate the projected ray angle into world space
		const float fov = m_player->fov();
		const float fRayAngle = (m_player->rotation() - fov / 2.0f) + ((float)x / (float)m_screen->width()) * fov;

		// Find distance to wall
		const float fStepSize = 0.5f;		  // Increment size for ray casting, decrease to increase										
		float fDistanceToWall = 0.0f;		  //                                           resolution

		bool bHitWall = false;		// Set when ray hits wall block
		bool bBoundary = false;		// Set when ray hits boundary between two wall blocks

		const float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
		const float fEyeY = cosf(fRayAngle);

		// Incrementally cast ray from player, along ray angle, testing for 
		// intersection with a block
		while (!bHitWall && fDistanceToWall < m_render_depth)
		{
			fDistanceToWall += fStepSize;
			const int nTestX = (int)(m_player->x() + fEyeX * fDistanceToWall);
			const int nTestY = (int)(m_player->y() + fEyeY * fDistanceToWall);

			// Test if ray is out of bounds
			if (nTestX < 0 || nTestX >= m_screen->width() || nTestY < 0 || nTestY >= m_screen->height())
			{
				bHitWall = true;			// Just set distance to maximum depth
				fDistanceToWall = m_render_depth;
			}
			else
			{
				// Ray is inbounds so test to see if the ray cell is a wall block
				if (!m_map->available(nTestX, nTestY))
				{
					// Ray has hit wall
					bHitWall = true;

					// To highlight tile boundaries, cast a ray from each corner
					// of the tile, to the player. The more coincident this ray
					// is to the rendering ray, the closer we are to a tile 
					// boundary, which we'll shade to add detail to the walls
					std::vector<std::pair<float, float>> p;

					// Test each corner of hit tile, storing the distance from
					// the player, and the calculated dot product of the two rays
					for (int tx = 0; tx < 2; tx++)
						for (int ty = 0; ty < 2; ty++)
						{
							// Angle of corner to eye
							float vy = (float)nTestY + ty - m_player->x();
							float vx = (float)nTestX + tx - m_player->y();
							float d = sqrt(vx*vx + vy*vy);
							float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
							p.push_back(std::make_pair(d, dot));
						}

					// Sort Pairs from closest to farthest
					std::sort(p.begin(), p.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right) {return left.first < right.first; });

					// First two/three are closest (we will never see all four)
					float fBound = 0.01;
					if (acos(p.at(0).second) < fBound) bBoundary = true;
					if (acos(p.at(1).second) < fBound) bBoundary = true;
					if (acos(p.at(2).second) < fBound) bBoundary = true;
				}
			}
		}

		// Calculate distance to ceiling and floor
		int nCeiling = (float)(m_screen->height() / 2.0) - m_screen->height() / ((float)fDistanceToWall);
		int nFloor = m_screen->height() - nCeiling;

		// Shader walls based on distance
		short nShade = ' ';
		if (fDistanceToWall <= m_render_depth / 7.0f)			nShade = 0x2591;	// Very close
		else if (fDistanceToWall <= m_render_depth / 6.0f)		nShade = 0x2592;	// Middle
		else if (fDistanceToWall <= m_render_depth / 5.0f)		nShade = 0x2593;	// Middle
		else if (fDistanceToWall <= m_render_depth / 4.0f)		nShade = 0x2588;	// Middle
		else if (fDistanceToWall < m_render_depth / 3.0f)		nShade = 0x2593;
		else if (fDistanceToWall < m_render_depth / 2.0f)		nShade = 0x2592;
		else if (fDistanceToWall < m_render_depth)				nShade = 0x2591;
		else													nShade = ' ';		// Too far away

		// Wall color based on distance
		//WORD color = m_screen->get_wall_color(fDistanceToWall, m_render_depth);

		if (bBoundary)		nShade = ' '; // Black it out

		for (int y = 0; y < m_screen->height(); y++)
		{
			// Each Row
			if (y <= nCeiling)
				m_screen->set(y*m_screen->width() + x, ' ', m_screen->get_boundary_color());
			else if (y > nCeiling && y <= nFloor)
				m_screen->set(y*m_screen->width() + x, nShade, m_screen->get_wall_color(fDistanceToWall, m_render_depth));
			else // Floor
			{
				// Shade floor based on distance
				float b = 1.0f - (((float)y - m_screen->height() / 2.0f) / ((float)m_screen->height() / 2.0f));
				if (b < 0.25)		nShade = '#';
				else if (b < 0.5)	nShade = 'x';
				else if (b < 0.75)	nShade = '.';
				else if (b < 0.9)	nShade = '-';
				else				nShade = ' ';
				m_screen->set(y*m_screen->width() + x, nShade, m_screen->get_floor_color());
			}
		}
	}
}

void clfps::Engine::update_screen_hud()
{
	// Display Map
	for (int nx = 0; nx < m_map->width(); nx++)
		for (int ny = 0; ny < m_map->height(); ny++)
		{
			m_screen->set((ny + 1)*m_screen->width() + nx, m_map->get(ny * m_map->width() + nx));
		}
	m_screen->set(((int)m_player->x() + 1) * m_screen->width() + (int)m_player->y(), m_player->representation());

	swprintf_s(m_screen->get(), 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", m_player->x(), m_player->y(), m_player->fov(), 1.0f / m_deltatime);
}

clfps::Engine::Engine(int screen_width, int screen_height)
{
	m_screen = new Screen(screen_width, screen_height);
	m_time = std::chrono::system_clock::now();
	m_render_depth = 16.0f;
}


clfps::Engine::~Engine()
{
	delete m_screen;
}

void clfps::Engine::player(Player * player)
{
	m_player = player;
}

void clfps::Engine::map(Map * map)
{
	m_map = map;
}

void clfps::Engine::update()
{
	m_deltatime = calc_deltatime();

}

void clfps::Engine::draw()
{
	update_screen();
	update_screen_hud();
	m_screen->draw();
}

float clfps::Engine::deltatime() const
{
	return m_deltatime;
}

bool clfps::Engine::key_pressed(unsigned short ch) const
{
	bool ret = GetAsyncKeyState(ch) & 0x8000;
	return ret;
}

