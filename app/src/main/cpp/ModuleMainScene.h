//
// Created by Laura on 13/06/2018.
//

#ifndef FLAPPYBIRD_MODULEMAINSCENE_H
#define FLAPPYBIRD_MODULEMAINSCENE_H

#include "Module.h"

#include <vector>

class Application;

class Tube;
class Character;
class Quad;
class Collider;

enum GameState
{
    BEGIN,
    PLAY,
    END
};



class ModuleMainScene : public Module
{
public:

    ModuleMainScene(Application* app);
    ~ModuleMainScene();

    bool Init();
    bool Update();
    bool CleanUp();

    void Input();
    void OnCollision(Collider* c1, Collider* c2);

    void RestartGame();

private:
    void InstantiateTubes(float pos_x);

private:
    std::vector<Tube*> tubes;
    Character* ball;

    GameState game_state;
    float last_frame;


};
#endif //FLAPPYBIRD_MODULEMAINSCENE_H
