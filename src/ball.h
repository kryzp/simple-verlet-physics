#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
public:
	Ball(float radius, const sf::Vector2f& position);

	void move(float dt);
	void move_by(const sf::Vector2f& amount);

	void position(const sf::Vector2f& v);
	void position_no_last(const sf::Vector2f& v);
	void velocity(const sf::Vector2f& v);
	void acceleration(const sf::Vector2f& v);
	void radius(float v);

	sf::Vector2f position() const;
	sf::Vector2f velocity() const;
	float radius() const;

	sf::Color col = sf::Color::Green;

private:
	sf::Vector2f m_position;
	sf::Vector2f m_last_position;
	sf::Vector2f m_acceleration;
	float m_radius;
};

#endif // BALL_H
