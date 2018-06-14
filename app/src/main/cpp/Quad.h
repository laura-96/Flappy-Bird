//
// Created by Laura on 13/06/2018.
//

#ifndef FLAPPYBIRD_QUAD_H
#define FLAPPYBIRD_QUAD_H


#include <math.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

struct Vertex {
    GLfloat pos[2];
    GLubyte rgba[4];
};

class Circle {

public:
    Circle(float aspect, float rad, float x, float y)
    {
        radius = rad;
        ar = aspect;

        this->x = x;
        this->y = y;

        float delta = 2.0f * (float)M_PI / 20.0f;

        for (int i = 0; i < 20; ++i)
        {
            vertices[i] = {{x + radius * cos(i * delta), ar * (y + radius * sin(i * delta))} , {0x00, 0xFF, 0x00}};
        }

    }

    ~Circle(){
    }

    void Move(float move_x, float move_y)
    {
        float delta = 2.0f * (float)M_PI / 20.0f;

        for (int i = 0; i < 20; ++i)
        {
            vertices[i] = {{x + move_x + radius * cos(i * delta), ar * (y + move_y + radius * sin(i * delta))} , {0x00, 0xFF, 0x00}};
        }

        x = x + move_x;
        y = y + move_y;
    }

public:
    Vertex vertices[20];
    float radius;
    float ar;
private:
    float x, y;
};


class Quad {

public:
    Quad(float x, float y, float w, float h)
    {
        width = w;
        height = h;

        this->x = x;
        this->y = y;

        vertices[0] = {{x + width, y}, {0x00, 0xFF, 0x00}};
        vertices[1] = {{x + width, y + height}, {0x00, 0x00, 0xFF}};
        vertices[2] = {{x, y + height}, {0xFF, 0x00, 0x00}};
        vertices[3] = {{x, y + height}, {0xFF, 0x00, 0x00}};
        vertices[4] = {{x, y}, {0xFF, 0x00, 0x00}};
        vertices[5] = {{x + width, y}, {0x00, 0xFF, 0x00}};
    }

    ~Quad(){
    }

    void Move(float move_x, float move_y)
    {
        vertices[0] = {{x + move_x + width, y + move_y}, {0x00, 0xFF, 0x00}};
        vertices[1] = {{x + move_x + width, y + move_y + height}, {0x00, 0x00, 0xFF}};
        vertices[2] = {{x + move_x, y + move_y + height}, {0xFF, 0x00, 0x00}};
        vertices[3] = {{x + move_x, y + move_y + height}, {0xFF, 0x00, 0x00}};
        vertices[4] = {{x + move_x, y + move_y}, {0xFF, 0x00, 0x00}};
        vertices[5] = {{x + move_x + width, y + move_y}, {0x00, 0xFF, 0x00}};

        x = x + move_x;
        y = y + move_y;
    }

public:
    Vertex vertices[6];
    float width;
    float height;
private:
    float x, y;
};

#endif //FLAPPYBIRD_QUAD_H
