//
// Created by Богдан Василенко on 21/12/2019.
//

#ifndef AFFINE_CIPHERS_PROGRAM_H
#define AFFINE_CIPHERS_PROGRAM_H

#include <string>
#include <utility>
#include <cstdint>
#include <vector>
#include <functional>

namespace affine_ciphers_ns {

    class program {
    public:
        enum text_lang_t { Eng = 1, Rus };

        struct key
        {
            std::uint8_t a;
            std::uint8_t b;
        };

    public:
        std::pair<std::string, key> encrypt(const std::string& i_str) const;
        std::string decrypt(const std::string& i_str, key i_key) const;

        void set_lang(text_lang_t i_lang) { m_lang = i_lang; }

    private:
        key gen_key() const;

        using translate_fn = std::function<size_t (size_t)>;
        std::string translate_msg(std::string i_str, translate_fn i_translate_fn) const;

        std::pair<const std::wstring&, std::size_t> find_ch_in_dict(wchar_t i_ch) const;

    private:
        text_lang_t m_lang = Eng;

        const static std::wstring eng_dict;
        const static std::wstring eng_upper_dict;
        const static std::vector<std::uint8_t> possible_a_eng;

        const static std::wstring rus_dict;
        const static std::wstring rus_upper_dict;
        const static std::vector<std::uint8_t> possible_a_rus;
    };
}

#endif //AFFINE_CIPHERS_PROGRAM_H
