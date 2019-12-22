//
// Created by Богдан Василенко on 21/12/2019.
//

#include "program.h"

#include <iostream>
#include <codecvt>
#include <locale>
#include <random>
#include <unordered_map>

namespace affine_ciphers_ns {


    const std::wstring program::eng_dict = L"abcdefghijklmnopqrstuvwxyz";
    const std::wstring program::eng_upper_dict = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::vector<std::uint8_t> program::possible_a_eng = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

    const std::wstring program::rus_dict = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    const std::wstring program::rus_upper_dict = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const std::vector<std::uint8_t> program::possible_a_rus = {1, 2, 4, 5, 7, 8, 10, 13, 14, 16, 17, 19, 20, 23, 25, 26, 28, 29, 31, 32};

    std::pair<std::string, program::key> program::encrypt(const std::string& i_str) const
    {
        const auto enc_key = gen_key();

        const std::size_t dict_size = (m_lang == Eng ? eng_dict.size() : rus_dict.size());
        auto enc_fn = [&enc_key, dict_size](std::size_t i_curr_pos)
        {
            return (i_curr_pos * enc_key.a + enc_key.b) % dict_size;
        };

        return { translate_msg(i_str, enc_fn), enc_key };
    };

    std::string program::decrypt(const std::string& i_str, key i_key) const
    {
        const std::size_t dict_size = (m_lang == Eng ? eng_dict.size() : rus_dict.size());
        std::uint8_t a_inv = i_key.a % dict_size;
        for(std::uint8_t x = 1; x < dict_size; ++x)
        {
            if((a_inv * x) % dict_size == 1)
            {
                a_inv = x;
                break;
            }
        }

        auto dec_fn = [&i_key, a_inv, dict_size](std::size_t i_curr_pos)
        {
            return (a_inv * (i_curr_pos + dict_size - i_key.b)) % dict_size;
        };

        return translate_msg(i_str, dec_fn);
    }

    std::string program::translate_msg(std::string i_str, translate_fn i_translate_fn) const
    {
        using wstr_convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<wstr_convert_type, wchar_t> cvt;
        const auto wide_str = cvt.from_bytes(i_str);

        std::unordered_map<wchar_t, wchar_t> translation_table;
        std::wstring res_str;
        for(const auto ch : wide_str) {
            const auto trans_it = translation_table.find(ch);
            if (trans_it != translation_table.end()) {
                res_str.push_back(trans_it->second);
            }
            else
            {
                wchar_t translated_ch = ch;
                const auto found_ch = find_ch_in_dict(ch);
                if (found_ch.second != std::wstring::npos)
                {
                    const auto translated_pos = i_translate_fn(found_ch.second);
                    translated_ch = found_ch.first[translated_pos];
                }

                res_str.push_back(translated_ch);
                translation_table[ch] = translated_ch;
            }
        }

        return cvt.to_bytes(res_str);
    }

    std::pair<const std::wstring&, std::size_t> program::find_ch_in_dict(wchar_t i_ch) const
    {
        const auto& lower_dict = m_lang == Eng ? eng_dict : rus_dict;
        const auto& upper_dict = m_lang == Eng ? eng_upper_dict : rus_upper_dict;

        const auto pos = lower_dict.find(i_ch);
        if (pos != std::wstring::npos)
            return {lower_dict, pos};
        else
            return {upper_dict, upper_dict.find(i_ch)};
    }

    program::key program::gen_key() const
    {
        key o_key;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<std::size_t> a_dist(0
                , (m_lang == Eng ? possible_a_eng.size() : possible_a_rus.size()));
        std::uniform_int_distribution<std::uint8_t > b_dist(1
                , (m_lang == Eng ? eng_dict.size() + 1 : rus_dict.size() + 1));

        const auto a_idx = a_dist(mt);
        o_key.a = (m_lang == Eng ? possible_a_eng[a_idx] : possible_a_rus[a_idx]);
        o_key.b = b_dist(mt);

        return o_key;
    }

}