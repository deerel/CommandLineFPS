#include "Player.h"

#include <algorithm>


clfps::Player::Player(float pos_x, float pos_y, float rotation, float fov, float speed) :
	m_pos_x(pos_x), m_pos_y(pos_y), m_rotation(rotation), m_fov(fov), m_speed(speed)
{
}

void clfps::Player::update(float deltatime)
{

}

void clfps::Player::rotate_left(float deltatime)
{
	m_rotation -= m_speed * 0.75f * deltatime;
}

void clfps::Player::rotate_right(float deltatime)
{
	m_rotation += m_speed * 0.75f * deltatime;
}

void clfps::Player::forward(float deltatime)
{
	m_pos_x += sinf(m_rotation) * m_speed * deltatime;
	m_pos_y += cosf(m_rotation) * m_speed * deltatime;

}

void clfps::Player::backward(float deltatime)
{
	m_pos_x -= sinf(m_rotation) * m_speed * deltatime;
	m_pos_y -= cosf(m_rotation) * m_speed * deltatime;
}

float clfps::Player::next_forward_x(float deltatime)
{
	return m_pos_x + sinf(m_rotation) * m_speed * deltatime;
}

float clfps::Player::next_forward_y(float deltatime)
{
	return m_pos_y + cosf(m_rotation) * m_speed * deltatime;
}

float clfps::Player::next_backward_x(float deltatime)
{
	return m_pos_x - sinf(m_rotation) * m_speed * deltatime;
}

float clfps::Player::next_backward_y(float deltatime)
{
	return m_pos_y - cosf(m_rotation) * m_speed * deltatime;
}

wchar_t clfps::Player::representation()
{
	const float TWO_PI = 6.2831853;
	float direction = (m_rotation / (TWO_PI / 8.0f));
	direction = std::fmodf(direction, 8.0f);

	if (direction < 0)
		direction += 8.0f;

	if (direction <= 3.0f && direction > 1.0f)
		return 0x2193; // Down
	if (direction <= 5.0f && direction > 3.0f)
		return 0x2190; // Left
	if (direction <= 7.0f && direction > 5.0f)
		return 0x2191; // Up
	if (direction <= 1.0f || direction > 7.0f)
		return 0x2192; // Right

	return 0x00A9; // Something wierd is happening

}

float clfps::Player::rotation()
{
	return m_rotation;
}

float clfps::Player::fov()
{
	return m_fov;
}

float clfps::Player::x()
{
	return m_pos_x;
}

float clfps::Player::y()
{
	return m_pos_y;
}
