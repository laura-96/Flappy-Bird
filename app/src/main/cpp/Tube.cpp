//
// Created by Laura Ripoll on 13/06/2018.
//

#include "Tube.h"
#include "Collider.h"
#include "Shapes.h"

Tube::Tube(float d, float x, float y, float w, float h_down, float h_up) {
    dist = d;

    pos_x = x;
    width = w;

    up_collider = new Collider(x, y + (h_down + dist), w, h_up);
    down_collider = new Collider(x, y, w, h_down);

    up_quad = new Quad(x, y + (h_down + dist), w, h_up);
    down_quad = new Quad(x, y, w, h_down);
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
    pos_x = pos_x - (650.0f * dt);

    up_quad->Move(-(650.0f * dt), 0);
    down_quad->Move(-(650.0f * dt), 0);

    up_collider->Move(-(650.0f * dt), 0);
    down_collider->Move(-(650.0f * dt), 0);
}