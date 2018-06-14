//
// Created by Laura on 13/06/2018.
//

#include "ModuleMainScene.h"
#include "Application.h"

#include <iostream>
#include <cstdlib>
#include <random>

#include "Collider.h"
#include "Shapes.h"
#include "Tube.h"
#include "Character.h"



#define DISTANCE_TUBES 1.0F

ModuleMainScene::ModuleMainScene(Application *app) : Module(app),
                                                     game_state(BEGIN),
                                                     last_frame(0){}

ModuleMainScene::~ModuleMainScene()
{
}

bool ModuleMainScene::Init() {

    InstantiateTubes(1.0f);

    Circle* char_circle = App->module_renderer->CreateCircle(0.1f, 0.0f, 0.0f);

    int scr_x, scr_y;

    App->module_renderer->GetViewportSize(scr_x, scr_y);
    float ar = (float)scr_x / (float)scr_y;

    ball = new Character(ar, 0.1f, 0.0f, 0.0f, char_circle);
    App->module_collision->AddCollider(ball->collider);

    return true;
}

void ModuleMainScene::Input() {

    if(game_state == BEGIN)
        game_state = PLAY;

    if(game_state == END)
    {
        RestartGame();
        game_state = PLAY;
    }

    ball->ApplyForce();

}

bool ModuleMainScene::Update() {

    timespec nowtimespec;
    clock_gettime(CLOCK_MONOTONIC, &nowtimespec);
    auto now = nowtimespec.tv_sec*1000000000ull + nowtimespec.tv_nsec;
    float dt = 0;

    if (last_frame > 0) {
        dt = float(now - last_frame) * 0.000000001f;
    }

    last_frame = now;

    if(game_state != PLAY)
        return false;

    ball->Update(dt);

    for (int i = 0; i < tubes.size(); ++i) {

        if(tubes[i]->GetToDelete())
        {
            std::vector<Tube*>::iterator it = tubes.begin() + i;
            delete(*it);
            tubes.erase(it);
        }

        tubes[i]->Update(dt);

        if((tubes[i]->pos_x + 0.25f) <= (-1.0f))
        {
            App->module_collision->RemoveCollider(tubes[i]->up_collider);
            App->module_collision->RemoveCollider(tubes[i]->down_collider);

            App->module_renderer->RemoveQuad(tubes[i]->up_quad);
            App->module_renderer->RemoveQuad(tubes[i]->down_quad);

            tubes[i]->SetToDelete();
        }

    }

    if(tubes.back()->pos_x <= 1.25f)
        InstantiateTubes(tubes.back()->pos_x + DISTANCE_TUBES);

    return true;

}
void ModuleMainScene::OnCollision(Collider *c1, Collider *c2) {
    if(game_state == PLAY)
        game_state = END;
}

void ModuleMainScene::InstantiateTubes(float pos_x)
{

    for (float sx = pos_x ; sx < (pos_x + 2); sx += DISTANCE_TUBES)// distance between tubes
    {

        std::random_device rnd;

        std::uniform_real_distribution<float> dist(0.0, 1.0);

        float rand_h = dist(rnd);

        Tube* tube = new Tube(0.75f, sx, 0, 0.25f, rand_h);

        App->module_renderer->AddQuad(tube->up_quad);
        App->module_renderer->AddQuad(tube->down_quad);

        App->module_collision->AddCollider(tube->up_collider);
        App->module_collision->AddCollider(tube->down_collider);

        tubes.push_back(tube);
    }

}

void ModuleMainScene::RestartGame() {


    delete ball;
    App->module_collision->RemoveCollider(ball->collider);

    if(tubes.size() > 0)
    {
        for(int i = 0; i < tubes.size(); ++i)
        {
            App->module_collision->RemoveCollider(tubes[i]->up_collider);
            App->module_collision->RemoveCollider(tubes[i]->down_collider);

            App->module_renderer->RemoveQuad(tubes[i]->up_quad);
            App->module_renderer->RemoveQuad(tubes[i]->down_quad);

            delete tubes[i];
        }
    }

    tubes.clear();

    InstantiateTubes(1.0f);

    Circle* char_circle = App->module_renderer->CreateCircle(0.1f, 0.0f, 0.0f);

    int scr_x, scr_y;

    App->module_renderer->GetViewportSize(scr_x, scr_y);
    float ar = (float)scr_x / (float)scr_y;

    ball = new Character(ar, 0.1f, 0.0f, 0.0f, char_circle);
    App->module_collision->AddCollider(ball->collider);

}

bool ModuleMainScene::CleanUp() {

    delete ball;

    if(tubes.size() > 0)
    {
        for(int i = 0; i < tubes.size(); ++i)
        {
            delete tubes[i];
        }
    }

    tubes.clear();
}