//
// Created by Laura on 13/06/2018.
//

#include "Character.h"
#include "Collider.h"
#include "Shapes.h"

Character::Character(float rad, float pos_x, float pos_y, Circle* circ)
{
    radius = rad;
    x = pos_x;
    y = pos_y;

    velocity = 0;
    collider = new Collider(x, y, radius);
    circle = circ;
}

Character::~Character() {

    delete collider;
    delete circle;

    collider = nullptr;
    circle = nullptr;
}

void Character::ApplyForce()
{
    velocity = 1200.0f;
}

void Character::Update(float dt)
{
//TODO BALANCE
    float to_move = velocity * dt + (0.5f * gravity * dt * dt);
    y += to_move;
    velocity += (gravity * dt);

    MoveCharacter(0, to_move);
}

void Character::MoveCharacter(float move_x, float move_y) {

    circle->Move(0, move_y);
    collider->Move(0, move_y);
}