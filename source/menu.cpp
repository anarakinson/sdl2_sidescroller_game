#include <menu.h>


void menu::Menu::init() {

}


void menu::Menu::update() {



}


void menu::Menu::render() {

    start_button->render();
    resume_button->render();
    exit_button->render();
    arrow->render();

    SDL_RenderPresent(TextureManager::renderer);

}

