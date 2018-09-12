#pragma once

#include <cmath>

namespace clfps {
	class Player
	{
	private:
		float m_pos_x;
		float m_pos_y;
		float m_rotation;
		float m_fov;
		float m_speed;
	public:
		Player() = delete;
		Player(float, float, float, float, float);
		void update(float);
		void rotate_left(float deltatime);
		void rotate_right(float deltatime);
		void forward(float deltatime);
		void backward(float deltatime);
		float next_forward_x(float deltatime);
		float next_forward_y(float deltatime);
		float next_backward_x(float deltatime);
		float next_backward_y(float deltatime);
		wchar_t representation();
		float rotation();
		float fov();
		float x();
		float y();
	};
}
