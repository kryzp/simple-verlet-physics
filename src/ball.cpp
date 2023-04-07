#include "ball.h"
#include <iostream>

Ball::Ball(float radius, const sf::Vector2f& position)
	: m_radius(radius)
	, m_position(position)
	, m_last_position(position)
	, m_acceleration(0.0f, 0.0f)
{
}

void Ball::move(float dt)
{
	sf::Vector2f velocity = m_position - m_last_position;
	sf::Vector2f new_pos = m_position + velocity + (0.5f * m_acceleration * dt * dt);
	m_last_position = m_position;
	m_position = new_pos;
	m_acceleration = { 0.0f, 0.0f };
}

void Ball::move_by(const sf::Vector2f& amount)
{
	m_position += amount;
}

void Ball::position(const sf::Vector2f& v) { m_position = v; m_last_position = v; }
void Ball::position_no_last(const sf::Vector2f& v) { m_position = v; }
void Ball::velocity(const sf::Vector2f& v) { m_last_position -= v; }
void Ball::acceleration(const sf::Vector2f& v) { m_acceleration = v; };
void Ball::radius(float v) { m_radius = v; }
sf::Vector2f Ball::position() const { return m_position; }
sf::Vector2f Ball::velocity() const { return m_position - m_last_position; }
float Ball::radius() const { return m_radius; }
