#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

#include "ball.h"
#include "chunks.h"
#include "util.h"

#define CHUNK_SIZE 16

float magnitude(const sf::Vector2f& v) {
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}

float magnitude_sqr(const sf::Vector2f& v) {
	return (v.x * v.x) + (v.y * v.y);
}

void physics_update(float dt, std::vector<Ball>& balls, Chunks& chunks, const sf::Vector2u& map_size)
{
	chunks.clear();
	for (int i = 0; i < balls.size(); i++) {
		chunks.assign(balls[i].position().x, balls[i].position().y, i);
	}

	for (int i = 0; i < balls.size(); i++) {
		auto& b = balls[i];
		b.acceleration(sf::Vector2f(0.0f, 918.0f));
		b.move(dt);
		const float padding = b.radius() * 2.0f;
		if (b.position().x > map_size.x - padding) {
			b.position_no_last(sf::Vector2f(map_size.x - padding, b.position().y));
		} else if (b.position().x < padding) {
			b.position_no_last(sf::Vector2f(padding, b.position().y));
		}
		if (b.position().y > map_size.y - padding) {
			b.position_no_last(sf::Vector2f(b.position().x, map_size.y - padding));
		} else if (b.position().y < padding) {
			b.position_no_last(sf::Vector2f(b.position().x, padding));
		}
	}

	for (int i = 0; i < balls.size(); i++) {
		auto& b1 = balls[i];
		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++) {
				int cx = (int)(b1.position().x / CHUNK_SIZE) + dx;
				int cy = (int)(b1.position().y / CHUNK_SIZE) + dy;
				if (!chunks.exists(cx, cy)) {
					continue;
				}
				const auto& chunk_here = chunks.get(cx, cy);
				for (const auto& j : chunk_here) {
					if (i == j) {
						continue;
					}
					auto& b2 = balls[j];
					sf::Vector2f to_from = b2.position() - b1.position();
					float distance_sqr = magnitude_sqr(to_from);
					float rad_sum = b1.radius() + b2.radius();
					bool intersects = distance_sqr < (rad_sum * rad_sum) && distance_sqr > 0.001f;
					if (intersects) {
						float distance = std::sqrt(distance_sqr);
						float delta = distance - rad_sum;
						sf::Vector2f normal = to_from / distance;
						sf::Vector2f offset = normal * delta;
						b1.move_by(offset * 0.5f);
						b2.move_by(-offset * 0.5f);
					}
				}
			}
		}
	}
}

void physics_update_step(float dt, int sub_steps, std::vector<Ball>& balls, Chunks& chunks, const sf::Vector2u& map_size)
{
	const float sub_dt = dt / (float)sub_steps;
	for (int s = 0; s < sub_steps; s++) {
		physics_update(sub_dt, balls, chunks, map_size);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 768), "Verlet Physics");
	sf::Clock delta_clock;
	float dt = 0.0f;

	Chunks chunks(1280, 768, CHUNK_SIZE);
	std::vector<Ball> balls;

	for (int i = 0; i < 1024; i++)
	{
		Ball b(5.0f, sf::Vector2f(rand() % (window.getSize().x - 100) + 50, rand() % (window.getSize().y - 100) + 50));

		b.col = col_from_hsv(rand() % 360, 1.0f, 1.0f);

		for (int j = 0; j < balls.size(); j++)
		{
			const auto& b2 = balls[j];
			sf::Vector2f to_from = b2.position() - b.position();
			float distance_sqr = magnitude_sqr(to_from);
			while (distance_sqr < 200.0f + (b.radius() * b.radius()))
			{
				b.position(sf::Vector2f(rand() % (window.getSize().x - 100) + 50, rand() % (window.getSize().y - 100) + 50));
				to_from = b2.position() - b.position();
				distance_sqr = magnitude_sqr(to_from);
			}
		}

		balls.push_back(b);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto pos = sf::Vector2f(sf::Mouse::getPosition(window));
			balls.emplace_back(5.0f, pos);
			balls.back().col = sf::Color::White;
		}

		physics_update_step(dt, 8, balls, chunks, window.getSize());

		window.clear();
		for (const auto& b : balls)
		{
			sf::CircleShape circle;
			circle.setFillColor(b.col);
			circle.setRadius(b.radius());
			circle.setPosition(b.position());
			circle.setOrigin(b.radius(), b.radius());

			window.draw(circle);
		}
		window.display();

		dt = delta_clock.restart().asSeconds();
	}

	return 0;
}
