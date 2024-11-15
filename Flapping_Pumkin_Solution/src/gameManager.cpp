#include "gameManager.h"

#include <iostream>
#include "raylib.h"

#include "globals/globals.h"

#include "menu/menu.h"
#include "menu/credits.h"
#include "game/game.h"

using namespace std;


namespace gameManager
{

    static void init();
    static void update();
    static void draw();
    static void close();

    CurrentScreen currentscreen;
    bool isRunning = true;
    bool twoPlayerOn = false;

    int run(void)
    {
        init();


        while (isRunning && !WindowShouldClose())
        {
            gameManager::update();

            gameManager::draw();
        }

        close();

        return 0;
    }

    static void init()
    {
        srand(static_cast<unsigned int>(time(NULL)));
        InitAudioDevice();

        Globals::initGlobals();
        InitWindow(static_cast<int>(Globals::Screen.size.x), static_cast<int>(Globals::Screen.size.y), Globals::Screen.name);

        Menu::initMenu();
        gameManager::currentscreen = menu;
    }

    static void update()
    {
        switch (currentscreen)
        {
        case menu:
            Menu::updateMenu(twoPlayerOn);
            break;
        case game:
            Game::updateGame(twoPlayerOn);
            break;
        case credits:
            Credits::updateCredits();
            break;
        default:
            break;
        }
    }

    static void draw()
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (currentscreen == menu)
        {
            Menu::drawMenu();
        }
        if (currentscreen == game)
        {
            Game::drawGame(twoPlayerOn);
        }
        if (currentscreen == credits)
        {
            Credits::drawCredits();
        }
        EndDrawing();
    }

    static void close()
    {
        CloseAudioDevice();
        Menu::unloadMenu();
        Game::unloadGame();
        Credits::unloadCredits();
        CloseWindow();
    }

    void stop()
    {
        isRunning = false;
    }
}