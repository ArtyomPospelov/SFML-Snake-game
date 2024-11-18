#pragma once
#include <SFML/Graphics/Shape.hpp>

// Custom SFML shape for snake game requrements.
// Include some types of simple forms shape (rectange, circle, etc.)
class SnakeShape : public sf::Shape
{
public:
	enum Type
	{
		T_Rectangle,
		T_Circle,
		T_Triangle
	};

	SnakeShape();
	SnakeShape(Type t, float sideSize);

	std::size_t getPointCount() const override;
	sf::Vector2f getPoint(std::size_t index) const override;

	SnakeShape& operator=(const SnakeShape& other);

private:
	Type m_Type;
	float m_SideSize = 0;
};