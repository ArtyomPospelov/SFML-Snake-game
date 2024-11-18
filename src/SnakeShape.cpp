#include "SnakeShape.h"
#include <stdexcept>
#include <cmath>

SnakeShape::SnakeShape()
    : m_Type(T_Rectangle),
    m_SideSize(FLT_MIN)
{
    // construct invalid shape as defautl.
}

SnakeShape::SnakeShape(Type t, float sideSize)
    : m_Type(t),
    m_SideSize(sideSize)
{
}

std::size_t SnakeShape::getPointCount() const
{
    switch (m_Type)
    {
    case T_Rectangle:
        return 4;
    case T_Circle:
        return 30;
    case T_Triangle:
        return 3;
    }

    return 0;
}

sf::Vector2f SnakeShape::getPoint(std::size_t index) const
{
    if (m_SideSize <= 0)
        throw std::runtime_error("Undefined shape size");

    if (m_Type == T_Rectangle)
    {
        switch (index)
        {
        default:
        case 0:
            return { 0, 0 };
        case 1:
            return { m_SideSize, 0 };
        case 2:
            return { m_SideSize, m_SideSize };
        case 3:
            return { 0, m_SideSize };
        }
    }
    else if (m_Type == T_Circle)
    {
        const float radius = m_SideSize / 2;
        double angle = 2 * 3.14 * index / getPointCount();
        return sf::Vector2f (radius + radius * std::cos(angle), radius + radius * std::sin(angle));
    }
    else if (m_Type == T_Triangle)
    {
        switch (index)
        {
        default:
        case 0:
            return { m_SideSize / 2, 0 };
        case 1:
            return { m_SideSize, m_SideSize };
        case 2:
            return { 0, m_SideSize };
        }
    }
}

SnakeShape& SnakeShape::operator=(const SnakeShape& other)
{
    if (this == &other)
        return *this;

    m_SideSize = other.m_SideSize;
    m_Type = other.m_Type;
    setPosition(other.getPosition());
    setFillColor(other.getFillColor());
    setOutlineColor(other.getOutlineColor());
    setOutlineThickness(other.getOutlineThickness());
    setOrigin(other.getOrigin());
    setRotation(other.getRotation());
    setScale(other.getScale());
    update();
    return *this;
}