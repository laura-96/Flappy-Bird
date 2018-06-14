//
// Created by Laura on 13/06/2018.
//

#include "ModuleMainScene.h"
#include "Application.h"
#include "ModuleRenderer.h"
#include "ModuleCollision.h"

#include <iostream>
#include <cstdlib>
#include <random>

#include "Collider.h"
#include "Shapes.h"
#include "Tube.h"
#include "Character.h"


ModuleMainScene::ModuleMainScene(Application *app) : Module(app),
                                                     game_state(BEGIN),
                                                     last_frame(0){}

ModuleMainScene::~ModuleMainScene()
{
}

bool ModuleMainScene::Init() {

    App->module_renderer->GetViewportSize(screen_x, screen_y);

    InstantiateTubes(screen_x + (screen_x / 4));

    float char_size = screen_x / 9;

    //Instantiate in the middle of the screen
    float screen_pos_x = screen_x / 2;
    float screen_pos_y = screen_y / 2;

    Circle* char_circle = App->module_renderer->CreateCircle(char_size, screen_pos_x, screen_pos_y);

    ball = new Character(char_size, screen_pos_x, screen_pos_y, char_circle);
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

        if((tubes[i]->pos_x + tubes[i]->width) <= 0)
        {
            App->module_collision->RemoveCollider(tubes[i]->up_collider);
            App->module_collision->RemoveCollider(tubes[i]->down_collider);

            App->module_renderer->RemoveQuad(tubes[i]->up_quad);
            App->module_renderer->RemoveQuad(tubes[i]->down_quad);

            tubes[i]->SetToDelete();
        }

    }

    if((*tubes.back()).pos_x <= (screen_x + (*tubes.back()).width))
        InstantiateTubes((*tubes.back()).pos_x + (screen_x / 1.5f));

    if(ball->y < 0)
        game_state = END;
    
    return true;

}
void ModuleMainScene::OnCollision(Collider *c1, Collider *c2) {
    if(game_state == PLAY)
        game_state = END;
}

void ModuleMainScene::InstantiateTubes(float pos_x)
{

    for (float sx = pos_x ; sx < (pos_x + (2 * screen_x)); sx += (screen_x / 1.5f))// distance between tubes
    {

        std::random_device rnd;

        std::uniform_real_distribution<float> dist(0.0f, (float) (screen_y / 2));
        float rand_h = dist(rnd);
        float distance = screen_y / 2;

        Tube* tube = new Tube(distance, sx, 0, screen_x / 4, rand_h, screen_y - (rand_h + distance));

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

    InstantiateTubes(screen_x + (screen_x / 4));

    float char_size = screen_x / 9; //A quarter of the screen in x axis

    //Instantiate in the middle of the screen
    float screen_pos_x = screen_x / 2;
    float screen_pos_y = screen_y / 2;

    Circle* char_circle = App->module_renderer->CreateCircle(char_size, screen_pos_x, screen_pos_y);

    ball = new Character(char_size, screen_pos_x, screen_pos_y, char_circle);
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
    return true;
}