#pragma once //для одного вызова (вместо ifndef и define, они не работают)
#include <vector>
#include <string>

//количество карточек
constexpr int TOTAL_CARDS = 20;

namespace Graph_lib {
    struct Image {};     //пустые заглушки
    struct Rectangle {};
    struct Button {};
}


// данные о карточке
struct CardState {
    void* rect;
    Graph_lib::Image* img;
    void* button;
    bool flipped;
    bool removed;
    int value;
    bool image_attached;
};


extern std::vector<CardState> cards; //extern чтобы другие файлы видели эти переменные, иначе ломается
extern std::vector<int> selected_cards;
extern bool can_flip;
extern int attempts_counter;
extern bool showing_initial_twos;

// для создания фейковых окон
void fake_clear_window();
void reset_game_state();
//для действий с карточками
void init_cards_for_image_test();
std::string simulate_flip_and_attach_image(int index);
void cleanup_fake_images();

std::string get_fake_image_path(int value);