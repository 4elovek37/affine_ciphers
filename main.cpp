#include <iostream>
#include <sstream>
#include <algorithm>

#ifdef _WIN32
#include<windows.h>
#endif

#include "ui.h"
#include "io_helper.h"
#include "program.h"

using namespace affine_ciphers_ns;

void change_settings(program& io_program)
{
    std::cout << "������� ���������" << std::endl << io_program.get_settings().to_string();

    int ans = utils_ns::io_helper::get_input(settings_main_text);

    switch (ans)
    {
        case 0:
            return;
        case 1:
        {
            program::settings new_settings;
            new_settings.text_lang =
                    static_cast<program::settings::text_lang_t>(utils_ns::io_helper::get_input(settings_set_lang));
            new_settings.non_dict_rule =
                    static_cast<program::settings::non_dict_rule_t >(utils_ns::io_helper::get_input(settings_set_non_dict_char_rule));
            new_settings.upper_lower_rule =
                    static_cast<program::settings::upper_lower_rule_t >(utils_ns::io_helper::get_input(settings_upper_lower_rule));


            io_program.set_settings(new_settings);
            std::cout << "��������� ���������" << std::endl;
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    affine_ciphers_ns::program aff_program;

    std::cout << hello_text << std::endl;

    //main loop
    while (true)
    {
        int ans = utils_ns::io_helper::get_input(main_menu_text);
        switch (ans)
        {
            case 1:
                change_settings(aff_program);
                break;
            case 2:
            {
                const auto text = utils_ns::io_helper::get_wstring("������� ���������");
                const auto res = aff_program.encrypt(text);
                std::cout << res.second.to_string();
                std::cout << "�������� ����������: " << res.first << std::endl;
                break;
            }
            case 3:
            {
                const auto text = utils_ns::io_helper::get_wstring("������� ����������");
                std::cout << "���� ����� ������� f = ax + b" << std::endl;
                const auto a = utils_ns::io_helper::get_input<int>("������� a");
                const auto b = utils_ns::io_helper::get_input<int>("������� b");
                key enc_key(a, b);
                std::cout << "�������������� ���������: " << aff_program.decrypt(text, enc_key)
                          << std::endl;
                break;
            }
            case 4:
            {
                const auto text = utils_ns::io_helper::get_wstring("������� ����������");
                auto hack_stats = aff_program.hack(text);
                std::sort(std::begin(hack_stats), std::end(hack_stats), [](const auto& i_lhs, const auto& i_rhs)
                {
                    return i_lhs.standard_deviation < i_rhs.standard_deviation;
                });

                for(std::size_t i = 0; i < 3; ++i)
                {
                    std::cout << std::to_string(i+1) << ". ����: " << hack_stats[i].hacked_key.to_string() <<
                              "���: " << std::to_string(hack_stats[i].standard_deviation) <<
                              " �������� ������: " << std::endl;
                    std::cout << hack_stats[i].decrypted_str << std::endl;
                }

                break;
            }
            case 5:
            {
                const auto text = utils_ns::io_helper::get_wstring("������� ���������");
                const auto a = utils_ns::io_helper::get_input<int>("������� a");
                const auto b = utils_ns::io_helper::get_input<int>("������� b");
                key enc_key(a, b);

                const auto res = aff_program.encrypt_by_key(text, enc_key);
                std::cout << "�������� ����������: " << res.first << std::endl;

                break;
            }
            case 0:
                return 0;
        }
    }
}