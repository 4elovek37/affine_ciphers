//
// Created by Богдан Василенко on 21/12/2019.
//

#ifndef AFFINE_CIPHERS_UI_H
#define AFFINE_CIPHERS_UI_H

#include "io_helper.h"
#include <unordered_map>

namespace affine_ciphers_ns {
    using int_ansv_t = const utils_ns::io_helper::ask_and_options<int>;

    static const std::string hello_text =
            "Программа для применения афинных шифров";
    int_ansv_t main_menu_text = {
            "Веберите опцию (1 - Настройки, 2 - Шифрование, 3 - Дешифрование, 4 - Частотный анализ, 0 - Выход)",
            {0, 1, 2, 3, 4}
    };
    int_ansv_t settings_main_text = {
            "Выберите опцию (1 - Сменить настройки, 0 - Выход)",
            {0, 1}
    };
    int_ansv_t settings_set_lang = {
            "Выберите язык шифротекстов (1 - Английский, 2 - Русский)",
            {1, 2}
    };
    int_ansv_t settings_set_non_dict_char_rule = {
            "Выберите тип обработки символов, не входящих в алфавит: (1 - Игнорировать, 2 - Сохранать)",
            {1, 2}
    };
}

#endif //AFFINE_CIPHERS_UI_H
