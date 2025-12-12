#include "game_card.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace Graph_lib;

// Определение глобальных переменных
Graph_lib::Window* main_window = nullptr;
std::vector<Shape*> shapes_to_delete;
std::vector<Widget*> widgets_to_delete;
std::vector<CardState> cards;
std::vector<int> selected_cards;
bool can_flip = true;
int attempts_counter = 0;
bool showing_initial_twos = false;

// Реализация CardButton
CardButton::CardButton(Point xy, int w, int h, int idx)
    : Button(xy, w, h, "", CardButton::cb_static), index(idx)
{}

void CardButton::cb_static(Address, Address pw)
{
    reference_to<CardButton>(pw).cb_pressed();
}

void CardButton::cb_pressed()
{
    handle_card_click(index);
}

// Функция: Обновление отображения карточки
void update_card_display(int card_index)
{
    if (card_index < 0 || static_cast<size_t>(card_index) >= cards.size()) return;
    
    CardState& card = cards[card_index];
    
    if (card.removed) {
        // Удаленная карточка
        card.rect->set_fill_color(Color::green);
        card.rect->set_color(Color::green);
        if (card.image_attached && card.img) {
            main_window->detach(*card.img);
            card.image_attached = false;
        }
        if (card.button) card.button->hide();
    } else if (card.flipped) {
        // Открытая карточка
        card.rect->set_fill_color(Color::white);
        card.rect->set_color(Color::black);
        
        // Прикрепляем изображение, если оно еще не прикреплено
        if (!card.image_attached && card.img) {
            try {
                main_window->attach(*card.img);
                card.image_attached = true;
            } catch (...) {
                std::cerr << "Ошибка прикрепления изображения для карточки " << card_index << std::endl;
            }
        }
    } else {
        // Закрытая карточка
        card.rect->set_fill_color(Color::blue);
        card.rect->set_color(Color::dark_blue);
        
        // Отсоединяем изображение, если оно прикреплено
        if (card.image_attached && card.img) {
            main_window->detach(*card.img);
            card.image_attached = false;
        }
        if (card.button) card.button->show();
    }
    
    if (main_window) main_window->redraw();
}

// Вспомогательная функция для обработки клика по карточке
void handle_card_click(int card_index)
{
    if (!can_flip || static_cast<size_t>(card_index) >= cards.size() || cards[card_index].flipped || cards[card_index].removed) {
        return;
    }
    
    flip_card_down(card_index);
    
    if (cards[card_index].value == 2) {
        can_flip = false;
        attempts_counter++;
        int* card_index_ptr = new int(card_index);
        Fl::add_timeout(1.0, remove_single_two_callback, card_index_ptr);
    } else {
        selected_cards.push_back(card_index);
        
        if (selected_cards.size() == 2) {
            can_flip = false;
            attempts_counter++;
            Fl::add_timeout(1.0, check_match_callback, nullptr);
        }
    }
}

// Функция для сброса игрового состояния
void reset_game_state()
{
    selected_cards.clear();
    can_flip = true;
    attempts_counter = 0;
    showing_initial_twos = false;
}

// Игра заканчивается, когда остались только двойки
bool should_game_end()
{
    for (const auto& card : cards) {
        if (!card.removed && card.value != 2) {
            return false;
        }
    }
    return true;
}

// Функция для проверки завершения игры
void check_game_completion()
{
    if (should_game_end()) {
        Fl::add_timeout(1.0, show_score_callback, nullptr);
    }
}

void flip_card_down(int card_index)
{
    if (card_index >= 0 && static_cast<size_t>(card_index) < cards.size() && !cards[card_index].removed) {
        cards[card_index].flipped = true;
        update_card_display(card_index);
    }
}

void remove_card(int card_index)
{
    if (card_index >= 0 && static_cast<size_t>(card_index) < cards.size()) {
        cards[card_index].removed = true;
        update_card_display(card_index);
        
        check_game_completion();
    }
}

// Функция для удаления одиночной двойки через 1 секунду
void remove_single_two_callback(void* card_index_ptr)
{
    int card_index = *static_cast<int*>(card_index_ptr);
    delete static_cast<int*>(card_index_ptr);
    
    if (card_index >= 0 && static_cast<size_t>(card_index) < cards.size()) {
        remove_card(card_index);
        
        selected_cards.clear();
        
        shuffle_remaining_cards();
        
        can_flip = true;
    }
}

void check_match_callback(void*)
{
    if (selected_cards.size() == 2) {
        int card1 = selected_cards[0];
        int card2 = selected_cards[1];
        
        if (cards[card1].value == cards[card2].value) {
            if (cards[card1].value != 2) {
                remove_card(card1);
                remove_card(card2);
            } else {
                cards[card1].flipped = false;
                cards[card2].flipped = false;
                update_card_display(card1);
                update_card_display(card2);
            }
        } else {
            cards[card1].flipped = false;
            cards[card2].flipped = false;
            update_card_display(card1);
            update_card_display(card2);
        }
        
        selected_cards.clear();
        can_flip = true;
    }
}

// Функция для перемешивания оставшихся карточек
void shuffle_remaining_cards()
{
    std::vector<int> remaining_values;
    
    for (const auto& card : cards) {
        if (!card.removed) {
            remaining_values.push_back(card.value);
        }
    }
    
    std::random_shuffle(remaining_values.begin(), remaining_values.end());
    
    size_t value_index = 0;
    for (auto& card : cards) {
        if (!card.removed) {
            card.value = remaining_values[value_index++];
            card.flipped = false;
            
            // Обновляем изображение для новой карточки
            if (card.img) {
                // Удаляем старое изображение
                if (card.image_attached) {
                    main_window->detach(*card.img);
                }
                delete card.img;
                
                // Создаем новое изображение
                std::string image_path = get_image_path(card.value);
                try {
                    card.img = new Image(card.rect->point(0), image_path);
                    card.image_attached = false;
                } catch (...) {
                    std::cerr << "Не удалось загрузить изображение: " << image_path << std::endl;
                    card.img = nullptr;
                }
            }
            
            int idx = &card - &cards[0];
            update_card_display(idx);
        }
    }
    
    check_game_completion();
}