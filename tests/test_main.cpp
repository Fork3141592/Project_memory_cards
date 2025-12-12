#include <iostream>

// проверки
int main_test_card_actions();
void test_card_matching_logic();
void test_card_non_matching_logic();
void test_attempts_counter();

int main() {
    std::cout << "Running tests...\n";

    if (main_test_card_actions() != 0) return 1;
    test_card_matching_logic();
    test_card_non_matching_logic();
    test_attempts_counter();

    std::cout << "All tests passed!!! /(*^ U ^*)/  \n";
    return 0;
}
