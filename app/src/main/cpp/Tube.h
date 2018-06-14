//
// Created by Laura Ripoll on 13/06/2018.
//

#ifndef FLAPPYBIRD_TUBE_H
#define FLAPPYBIRD_TUBE_H

class Quad;
class Collider;

class Tube{
public:

    Tube(float d, float x, float y, float w, float h);
    ~Tube();

    void Update(float dt);

    void SetToDelete()
    {
        toDelete = true;
    }

    bool GetToDelete() const
    {
        return toDelete;
    }

    float dist;
    float pos_x, pos_y;
    Collider* up_collider;
    Collider* down_collider;

    Quad* up_quad;
    Quad* down_quad;

private:
    bool toDelete = false;
};

#endif //FLAPPYBIRD_TUBE_H
