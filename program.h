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
        struct settings {
            enum text_lang_t { Eng = 1, Rus } text_lang = text_lang_t::Eng;
            enum non_dict_rule_t { Ignore = 1, Keep } non_dict_rule = non_dict_rule_t::Keep;

            std::string to_string() const;
        };

        struct key
        {
            std::uint8_t a;
            std::uint8_t b;
        };

    public:
        std::pair<std::string, key> encrypt(const std::string& i_str) const;
        std::string decrypt(const std::string& i_str, key i_key) const;

        void set_settings(const settings& i_settings) { m_settings = i_settings; }
        const settings& get_settings() const { return m_settings; }

    private:
        key gen_key() const;

        using translate_fn = std::function<size_t (size_t)>;
        std::string translate_msg(std::string i_str, translate_fn i_translate_fn) const;

        std::pair<const std::wstring&, std::size_t> find_ch_in_dict(wchar_t i_ch) const;

    private:
        settings m_settings;

        const static std::wstring eng_dict;
        const static std::wstring eng_upper_dict;
        const static std::vector<std::uint8_t> possible_a_eng;

        const static std::wstring rus_dict;
        const static std::wstring rus_upper_dict;
        const static std::vector<std::uint8_t> possible_a_rus;
    };
}

#endif //AFFINE_CIPHERS_PROGRAM_H
