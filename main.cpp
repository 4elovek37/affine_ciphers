#include <iostream>
#include <sstream>



#include "ui.h"
#include "io_helper.h"
#include "program.h"

using namespace affine_ciphers_ns;



void change_settings(program& io_program)
{
    std::cout << "Текущие настройки" << std::endl << io_program.get_settings().to_string();

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

            io_program.set_settings(new_settings);
            std::cout << "Настройки сохранены" << std::endl;
        }
    }
}

int main() {
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
                const auto text = utils_ns::io_helper::get_wstring("Введите сообщение");
                const auto res = aff_program.encrypt(text);
                std::cout << "Ключ: " << std::to_string(res.second.a) << ", " <<
                          std::to_string(res.second.b) << std::endl;
                std::cout << "Выходной шифротекст: " << res.first << std::endl;
                break;
            }
            case 3:
            {
                const auto text = utils_ns::io_helper::get_wstring("Введите шифротекст");
                std::cout << "Ввод ключа формата f = ax + b" << std::endl;
                program::key enc_key;
                enc_key.a = utils_ns::io_helper::get_input<int>("Введите a");
                enc_key.b = utils_ns::io_helper::get_input<int>("Введите b");
                std::cout << "Расшифрованное сообщение: " << aff_program.decrypt(text, enc_key)
                          << std::endl;
                break;
            }
            case 4:

                break;
            case 0:
                return 0;
        }
    }
}