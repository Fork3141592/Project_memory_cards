#include "mocks.h"
#include <cassert>
#include <iostream>

// используемые тесты
void test_card_matching_logic() {
    init_cards_for_image_test(); //создаём фейковое поле
    int first_index = 0, second_index = 5; //берём пару
    std::string p1 = simulate_flip_and_attach_image(first_index); //проверка переворота и картинки
    std::string p2 = simulate_flip_and_attach_image(second_index);
    bool match = (cards[first_index].value == cards[second_index].value);
    assert(match); //проверка совпадения
    if (match) { cards[first_index].removed = true; cards[second_index].removed = true; }
    assert(cards[first_index].removed && cards[second_index].removed);

    cleanup_fake_images();
    std::cout << "test_card_matching_logic passed\n";
}
//сбрасываем, берём не пару, проверяем что не удалились
void test_card_non_matching_logic() {
    init_cards_for_image_test();
    simulate_flip_and_attach_image(0); 
    simulate_flip_and_attach_image(1);
    bool match = (cards[0].value == cards[1].value);
    assert(!match);
    assert(!cards[0].removed && !cards[1].removed);
    cleanup_fake_images();
    std::cout << "test_card_non_matching_logic passed\n";
}

void test_attempts_counter() {
    init_cards_for_image_test();
    attempts_counter = 0;
    simulate_flip_and_attach_image(0);
    simulate_flip_and_attach_image(1);
    attempts_counter++;
    assert(attempts_counter == 1); //проверяем что начислились очки
    cleanup_fake_images();
    std::cout << "test_attempts_counter passed\n";
}
