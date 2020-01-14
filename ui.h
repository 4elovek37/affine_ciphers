//
// Created by Богдан Василенко on 21/12/2019.
//

#ifndef AFFINE_CIPHERS_UI_H
#define AFFINE_CIPHERS_UI_H

#include "io_helper.h"
#include "literals.h"
#include <unordered_map>

namespace affine_ciphers_ns {
    using int_ansv_t = const utils_ns::io_helper::ask_and_options<int>;

    static const std::string hello_text = HELLO;
    int_ansv_t main_menu_text = {
            MAIN_MENU,
            {0, 1, 2, 3, 4, 5}
    };
    int_ansv_t settings_main_text = {
            SETTINGS_MAIN,
            {0, 1}
    };
    int_ansv_t settings_set_lang = {
            SETTINGS_SET_LANG,
            {1, 2}
    };
    int_ansv_t settings_set_non_dict_char_rule = {
            SETTINGS_NON_DICT_RULE,
            {1, 2}
    };
    int_ansv_t settings_upper_lower_rule = {
            SETTINGS_UPPER_LOWER_RULE,
            {1, 2, 3}
    };
}

#endif //AFFINE_CIPHERS_UI_H
