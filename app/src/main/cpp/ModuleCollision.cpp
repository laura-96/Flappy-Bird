//
// Created by Laura on 13/06/2018.
//

#include "ModuleCollision.h"
#include "Application.h"
#include "Collider.h"

#include <math.h>


ModuleCollision::ModuleCollision(Application *app) : Module(app) {


}

ModuleCollision::~ModuleCollision()
{
    collider = nullptr;
    rec_colliders.clear();
}

void ModuleCollision::RemoveCollider(Collider* toRemove)
{

    if(collider == toRemove)
    {
        collider = nullptr;
        return;
    }

    for(std::vector<Collider*>::iterator it = rec_colliders.begin(); it != rec_colliders.end() && !rec_colliders.empty(); ++it)
    {
        if((*it) == toRemove)
        {
            rec_colliders.erase(it);
            break;
        }
    }

}


bool ModuleCollision::Update()
{
    for(int i = 0; i < rec_colliders.size(); i++)
    {
        if(collider == nullptr) return true;
        if(collider->CheckCollision(rec_colliders[i]))
        {
            App->OnCollision(collider, rec_colliders[i]);
        }
    }

    return true;
}

bool ModuleCollision::CleanUp()
{
    rec_colliders.clear();
    collider = nullptr;

    return true;
}

void ModuleCollision::AddCollider(Collider* col)
{
    if(col->GetType() == TUBE)
        rec_colliders.push_back(col);

    else if(col->GetType() == CIRCLE)
        collider = col;
}