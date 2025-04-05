#include <iostream>
#include <cmath>
#include "windows.h"

int simple_string_hash(const std::string& s, const int size);
int find_substring_light_rabin_karp(const std::string& sorce, const std::string& substring);
int main()
{
    SetConsoleOutputCP(1251);

    std::cout << "Введите строку, в которой будет осуществляться поиск: ";
    std::string str, substring;
    std::cin >> str;
    do {
        std::cout << "Введите подстроку, которую нужно найти: ";
        std::cin >> substring;       
        int result = find_substring_light_rabin_karp(str, substring); 
        std::cout << "Подстрока " << substring;
        if (result >= 0) {
            std::cout << " найдена по индексу " << result << std::endl;
        }
        else {
            std::cout << " не найдена" << std::endl;
        }
    } while (substring != "exit");
    return 0;
}

int find_substring_light_rabin_karp(const std::string& sorce, const std::string& substring) {
    int substrSize = substring.size();
    int hashSubstr = simple_string_hash(substring, substrSize);
    int sorceSubHash;
    for (int i = 0; i <= (sorce.size() - substrSize); ++i) {
        if (i == 0) sorceSubHash = simple_string_hash(&sorce[i], substrSize);
        if (hashSubstr != sorceSubHash) {
            sorceSubHash = sorceSubHash - static_cast<int>(sorce[i]) + static_cast<int>(sorce[i + substrSize]);
        }
        else {
            int j;
            for (j = 0; j < substrSize; ++j) {
                if (substring[j] != sorce[j + i]) {
                    break;
                }
            }
            if (j == substrSize) {
                return i;
            }
        }
    }
    return -1;
}

int simple_string_hash(const std::string& s, const int size) {
    int summ{ 0 };
    for (int i = 0; i < size; ++i) {
        summ += static_cast<int>(s[i]);
    }    
    return summ;
}
