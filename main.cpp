#include <iostream>
#include <sstream>



#include "ui.h"
#include "io_helper.h"
#include "program.h"

using namespace affine_ciphers_ns;

struct settings {
    using text_lang_t = program::text_lang_t;
    text_lang_t text_lang = text_lang_t::Eng;

    std::string to_string() const
    {
        std::ostringstream str;
        str << "Язык шифротекстов: "
            << (text_lang == text_lang_t::Eng ? "Английский" : "Русский")
            << std::endl;

        return str.str();
    }
};

void change_settings(settings& io_settings)
{
    std::cout << "Текущие настройки" << std::endl << io_settings.to_string();

    int ans = utils_ns::io_helper::get_input(settings_main_text);

    switch (ans)
    {
        case 0:
            return;
        case 1:
        {
            io_settings.text_lang = static_cast<settings::text_lang_t>(utils_ns::io_helper::get_input(settings_set_lang));
            std::cout << "Настройки сохранены" << std::endl;
        }
    }
}

int main() {
    settings setts;
    affine_ciphers_ns::program aff_program;
    aff_program.set_lang(setts.text_lang);

    std::cout << hello_text;

    //main loop
    while (true)
    {
        int ans = utils_ns::io_helper::get_input(main_menu_text);
        switch (ans)
        {
            case 1:
                change_settings(setts);
                aff_program.set_lang(setts.text_lang);
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