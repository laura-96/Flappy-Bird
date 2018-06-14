//
// Created by Laura on 13/06/2018.
//

#ifndef FLAPPYBIRD_MODULECOLLISION_H
#define FLAPPYBIRD_MODULECOLLISION_H

#include <stdio.h>
#include <vector>

#include "Module.h"

class Application;


class ModuleCollision : public Module {

public:
    ModuleCollision(Application* app);
    ~ModuleCollision();


    void RemoveCollider(Collider* toRemove);
    bool Update();

    bool CleanUp();

    void AddCollider(Collider* col);

private:
    std::vector<Collider*> rec_colliders;
    Collider* collider;
};

#endif //FLAPPYBIRD_MODULECOLLISION_H
