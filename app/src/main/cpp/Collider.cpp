//
// Created by Laura on 13/06/2018.
//

#include "Collider.h"
#include <math.h>

Collider::Collider()
{
    type = NONE;
}
Collider::Collider(float pos_x, float pos_y, float r)
{
    x = pos_x;
    y = pos_y;
    radius = r;
    type = CIRCLE;
}

Collider::Collider(float pos_x, float pos_y, float width, float height)
{
    x = pos_x;
    y = pos_y;
    w = width;
    h = height;

    type = TUBE;
}


void Collider::Move(float move_x, float move_y)
{
    x += move_x;
    y += move_y;

}

const CollisionType Collider::GetType() const
{
    return type;
}
bool Collider::CheckCollision(Collider* col) const
{

    float deltaX = x - fmax(col->x, fmin(x, col->x + col->w));
    float deltaY = y - fmax(col->y, fmin(y, col->y + col->h));

    return (deltaX * deltaX + deltaY * deltaY) < (radius * radius);

}