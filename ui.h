//
// Created by ������ ��������� on 21/12/2019.
//

#ifndef AFFINE_CIPHERS_UI_H
#define AFFINE_CIPHERS_UI_H

#include "io_helper.h"
#include <unordered_map>

namespace affine_ciphers_ns {
    using int_ansv_t = const utils_ns::io_helper::ask_and_options<int>;

    static const std::string hello_text =
            "��������� ��� ���������� ������� ������";
    static const std::string decoding_eq = "��������� �������������";
    int_ansv_t main_menu_text = {
            "�������� ����� (1 - ���������, 2 - ����������, 3 - �����������, 4 - ��������� ������, 5 - ���������� �� ��������� �����, 0 - �����)",
            {0, 1, 2, 3, 4, 5}
    };
    int_ansv_t settings_main_text = {
            "�������� ����� (1 - ������� ���������, 0 - �����)",
            {0, 1}
    };
    int_ansv_t settings_set_lang = {
            "�������� ���� ������������ (1 - ����������, 2 - �������)",
            {1, 2}
    };
    int_ansv_t settings_set_non_dict_char_rule = {
            "�������� ��� ��������� ��������, �� �������� � �������: (1 - ������������, 2 - ���������)",
            {1, 2}
    };
    int_ansv_t settings_upper_lower_rule = {
            "�������� ������� ����������: (1 - ���������, 2 - �������, 3 - ������)",
            {1, 2, 3}
    };
}

#endif //AFFINE_CIPHERS_UI_H
