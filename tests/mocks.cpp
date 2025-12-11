#include "mocks.h"
#include <algorithm>

// переменные
std::vector<CardState> cards; //все карточки
std::vector<int> selected_cards; //открытые в этой попытке
bool can_flip = true; //можно ли переворачивать
int attempts_counter = 0; //очки
bool showing_twos = false; //отображение пары

// создаём фейковое поле
void fake_clear_window() {
    cards.clear(); 
    selected_cards.clear(); 
    can_flip = true; 
    attempts_counter = 0; 
    showing_twos = false; 
}

std::string get_fake_image_path(int value) {
    if (value == 2) {
        return "images/im6.jpg";  // Для двойки используем особую картинку
    } else if (value >= 1 && value <= 10 && value != 6) {
        return "images/im" + std::to_string(value) + ".jpg";
    } else {
        return "images/im2.jpg";  // Запасной вариант
    }
}


//чистое поле
void reset_game_state() {
    cards.clear();
    selected_cards.clear();
    can_flip = true;
    attempts_counter = 0;
    showing_twos = false;
}

//карточки
void init_cards_for_image_test() {
    cards.clear();
    selected_cards.clear();
    attempts_counter = 0;
    can_flip = true;
    showing_twos = false;
    int values[TOTAL_CARDS] = {1,2,3,4,5,1,2,3,4,5,6,7,6,7,8,8,9,9,10,10};
    for (int i = 0; i < TOTAL_CARDS; ++i) {
        CardState c{};
        c.flipped = false; //не перевёрнуты
        c.removed = false; //не удалены
        c.value = values[i]; //номер карточки
        c.rect = nullptr; //заглушки
        c.img = nullptr;
        c.button = nullptr;
        c.image_attached = false; //картинка не видна
        cards.push_back(c);
    }
}

struct FakeImage { std::string path; }; //структура заглушки

//фейковые действия с карточками
std::string simulate_flip_and_attach_image(int index) {
    if (index < 0 || index >= (int)cards.size()) return "";
    CardState &c = cards[index]; //проверка индекса
    c.flipped = true; //переворачивает
    std::string expected_path = get_fake_image_path(c.value);  //находит  фейковую картинку
    FakeImage* fi = new FakeImage{expected_path};
    c.img = reinterpret_cast<Graph_lib::Image*>(fi); //превращает fakeimage просто в image для компилятора
    c.image_attached = true;
    return expected_path;
}

//чистим
void cleanup_fake_images() {
    for (auto &c : cards) {
        if (c.img) {
            FakeImage* fi = reinterpret_cast<FakeImage*>(c.img);
            delete fi;
            c.img = nullptr;
            c.image_attached = false;
        }
    }
}



