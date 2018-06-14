//
// Created by Laura Ripoll on 13/06/2018.
//

#include "Tube.h"
#include "Collider.h"
#include "Shapes.h"

Tube::Tube(float d, float x, float y, float w, float h) {
    dist = d;

    pos_x = x;
    pos_y = y;

    up_collider = new Collider(x, -1 + y + (h + dist), w, 1 - (-1 + y + (h + dist)));
    down_collider = new Collider(x, -1 + y, w, h);

    up_quad = new Quad(x, -1 + y + (h + dist), w, 1 - (-1 + y + (h + dist)));
    down_quad = new Quad(x, -1 + y, w, h);
}

Tube::~Tube()
{
    delete up_collider;
    delete down_collider;
    delete up_quad;
    delete down_quad;

    up_collider = nullptr;
    down_collider = nullptr;
    up_quad = nullptr;
    down_quad = nullptr;
}

void Tube::Update(float dt)
{
    pos_x = pos_x - (1.0f * dt);

    up_quad->Move(-(1.0f * dt), 0);
    down_quad->Move(-(1.0f * dt), 0);

    up_collider->Move(-(1.0f * dt), 0);
    down_collider->Move(-(1.0f * dt), 0);
}