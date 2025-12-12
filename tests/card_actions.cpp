#include "mocks.h"
#include <iostream>
#include <cassert> //для проверок


int main_test_card_actions() { //создаем фейковое исходное поле
    init_cards_for_image_test();

    std::string p0 = get_fake_image_path(cards[0].value);
    if (p0.empty()) { std::cerr << "image path empty\n"; return 1; } //находит ли картинку

    cards[0].flipped = true; //берем пару
    cards[5].flipped = true;
    if (cards[0].value == cards[5].value) { //должны удалиться
        cards[0].removed = cards[5].removed = true;
    } else {
        cards[0].flipped = cards[5].flipped = false;
    }
    ++attempts_counter;

    if (!((cards[0].removed && cards[5].removed) || (!cards[0].flipped && !cards[5].flipped))) {
        std::cerr << "logic mismatch\n"; return 2; //сработало ли
    }

    cards[1].flipped = true; //берем не пару
    cards[2].flipped = true;
    if (cards[1].value == cards[2].value) { //должны перевернуться обратно
        cards[1].removed = cards[2].removed = true;
    } else {
        cards[1].flipped = cards[2].flipped = false;
    }
    ++attempts_counter;


    if (!((cards[1].removed && cards[2].removed) || (!cards[1].flipped && !cards[2].flipped))) {
        std::cerr << "logic mismatch\n"; return 2;
    }


    fake_clear_window();
    if (!cards.empty()) { std::cerr << "fake_clear_window failed\n"; return 3; }
    //всё очистили, сбросили карты

    std::cout << "card_actions: tests passed\n";
    return 0;
}
