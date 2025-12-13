#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

// Первое объявление функций
int choose_difficulty();
vector<char> generate_cards(int total_of_cards);
void board(const vector<char>& cards, const vector<bool>& revealed, int columns = 10);
void game(int total_of_cards);
void statistics(int score, int turns, int pairs_count);

// Функция выбора сложности
int choose_difficulty() {
    int choice;
    string input;
    while (true) {
        cout << "The 'Memory' game'\n";
        cout << "Find all the pairs!\n";
        cout << "Choose the difficulty level:\n";
        cout << "1 - Easy (20 cards = 10 pairs)\n";
        cout << "2 - Normal (50 cards = 25 pairs)\n";
        cout << "3 - Hard (100 cards = 50 pairs)\n";
        cout << "Choice: ";

        getline(cin, input);

        if (input.length() == 1 && input[0] >= '1' && input[0] <= '3') {
            choice = input[0] - '0';

            switch (choice) {
            case 1: return 20;
            case 2: return 50;
            case 3: return 100;
            }
        }

        cout << "Incorrect choice. The default mode is set (20 cards).\n";
        return 20;

    }    
}

// Функция генерации карт
vector<char> generate_cards(int total_of_cards) {
    int pairs_count = total_of_cards / 2;
    string symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    vector<char> cards;
    for (int i = 0; i < pairs_count; ++i) {
        cards.push_back(symbols[i]);
        cards.push_back(symbols[i]);
        // cards.push_back(symbols[i % symbols.size()]);  // Этот вариант подстраховачный.
        // cards.push_back(symbols[i % symbols.size()]);  // Для возможных изменений условия.
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(cards.begin(), cards.end(), g);

    return cards; // более современная версия, старая может не работать с некоторыми компиляторами

    //random_shuffle(cards.begin(), cards.end()); // Пишет что такая версия устаревшая, но она работает
    //return cards;                               // А разбираться в новой мне лень (сорян 2 часа ночи)
}

// Функция отображения поля
void board(vector<char>& cards, vector<bool>& revealed, int columns) {
    for (int i = 0; i < cards.size(); ++i) {
        if (revealed[i]) {
            cout << " " << cards[i] << " ";
        }    
        else {
            cout << " * ";
        }
        if ((i + 1) % columns == 0) {
            cout << "\n";
        }
    } 
    cout << "\n";
}

// Функция описывающая игровой процесс
void game(int total_of_cards) {
    vector<char> cards = generate_cards(total_of_cards);
    vector<bool> revealed(total_of_cards, false);

    int pairs_count = total_of_cards / 2;
    int found_pairs = 0;
    int score = 0;
    int turns = 0;
    cout << "\nThe board is ready. Card numbers: 1.." << total_of_cards << "\n";

    while (found_pairs < pairs_count) {
        board(cards, revealed, 10);

        double first, second; //double не вызовет ошибку если пользователь введет номер 1.5?
        cout << "Select the first card (1-" << total_of_cards << "): ";
        cin >> first;
        cout << "Select the second card (1-" << total_of_cards << "): ";
        cin >> second;

        if (first < 1 || first > total_of_cards || second < 1 || second > total_of_cards || 
            first == second /*|| first % 1 != 0 || second % 1 != 0*/) {
            cout << "Incorrect choice. Try again.\n";
            continue;
        }

        first--; second--;

        if (revealed[first] || revealed[second]) {
            cout << "One of the selected cards is already open!\n";
            continue;
        }

        revealed[first] = true;
        revealed[second] = true;

        board(cards, revealed, 10);
        turns++;

        if (cards[first] == cards[second]) {
            cout << "The pair is found: " << cards[first] << "!\n";
            found_pairs++;
            score += 10;
        } else {
            cout << "It doesn't match.\n";
            revealed[first] = false;
            revealed[second] = false;
            score -= 2;
        }

        cout << "Score: " << score << "\n";
        cout << "Pairs found: " << found_pairs << " / " << pairs_count << "\n";
        cout << "------------------------------\n";
    }

    statistics(score, turns, pairs_count);
}

// Итоговая статистика
void statistics(int score, int turns, int pairs_count) {
    cout << "\nCongratulations! All pairs have been found!\n";
    cout << "Number of moves: " << turns << "\n";
    cout << "Final score: " << score << "\n";

    if (score > pairs_count * 8)
        cout << "Great result!\n";
    else if (score > pairs_count * 5)
        cout << "Well played!\n";
    else
        cout << "As much as possible\n";
}

int main() {
    //srand(static_cast<unsigned>(time(0))); с новым способом рандома она не нужна
    int total_of_cards = choose_difficulty();
    game(total_of_cards);
    return 0;
}
