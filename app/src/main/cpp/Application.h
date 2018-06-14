//
// Created by Laura on 13/06/2018.
//

#ifndef FLAPPYBIRD_APPLICATION_H
#define FLAPPYBIRD_APPLICATION_H

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <time.h>

class Module;
class ModuleCollision;
class ModuleRenderer;
class ModuleMainScene;

class Collider;

class Application {

public:
    Application();
    ~Application();

    bool Init();
    bool Update();
    bool CleanUp();

    void Input();
    void OnCollision(Collider* c1, Collider* c2);

private:
    void AddModule(Module* mod);

public:
    ModuleRenderer* module_renderer;
    ModuleCollision* module_collision;
    ModuleMainScene* module_main_scene;

private:
    std::vector<Module*> modules;

};

#endif //FLAPPYBIRD_APPLICATION_H
