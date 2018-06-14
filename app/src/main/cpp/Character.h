//
// Created by Laura on 13/06/2018.
//

#include <math.h>

#ifndef FLAPPYBIRD_CHARACTER_H
#define FLAPPYBIRD_CHARACTER_H

class Collider;
class Quad;
struct Vertex;

class Character{

public:
    Character(float rad, float pos_x, float pos_y, Circle* circ);
    void ApplyForce();
    void Update(float dt);

    void MoveCharacter(float move_x, float move_y);
    ~Character();

    float radius;
    float x, y;
    float velocity;
    float gravity = -1300.0f;

    Collider* collider;
    Circle* circle;
};

#endif //FLAPPYBIRD_CHARACTER_H
