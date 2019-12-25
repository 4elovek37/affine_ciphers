//
// Created by Богдан Василенко on 21/12/2019.
//

#include "program.h"

#include <codecvt>
#include <locale>
#include <random>
#include <sstream>



namespace affine_ciphers_ns {


    const std::wstring program::eng_dict = L"abcdefghijklmnopqrstuvwxyz";
    const std::wstring program::eng_upper_dict = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::vector<double> program::eng_stats =
            { 0.08167, 0.01492, 0.02202, 0.04253, 0.012702, 0.02228, 0.02015, 0.06094,
              0.06966, 0.00153, 0.01292, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
              0.00095, 0.05987, 0.06327, 0.09356, 0.02758, 0.00978, 0.02560, 0.00150,
              0.01994, 0.00077
            };
    const std::vector<std::uint8_t> program::possible_a_eng = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};

    const std::wstring program::rus_dict = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    const std::wstring program::rus_upper_dict = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const std::vector<double> program::rus_stats =
            { 0.07998, 0.01592, 0.04533, 0.01687, 0.02977, 0.08483, 0.00013, 0.0094,
              0.01641, 0.07367, 0.01208, 0.03486, 0.04343, 0.03203, 0.067, 0.10983,
              0.02804, 0.04746, 0.05473, 0.06318, 0.02615, 0.00267, 0.00966, 0.00486,
              0.0145, 0.00718, 0.00361, 0.00037, 0.01898, 0.01735, 0.00331, 0.00639, 0,02001
            };
    const std::vector<std::uint8_t> program::possible_a_rus = {1, 2, 4, 5, 7, 8, 10, 13, 14, 16, 17, 19, 20, 23, 25, 26, 28, 29, 31, 32};


    std::string program::translate_msg(const std::string& i_str, translate_fn i_translate_fn) const
    {
        using wstr_convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<wstr_convert_type, wchar_t> cvt;
        const auto wide_str = cvt.from_bytes(i_str);

        return cvt.to_bytes(translate_msg(wide_str, i_translate_fn));
    }

    std::wstring program::translate_msg(const std::wstring& i_str, translate_fn i_translate_fn) const
    {
        std::unordered_map<wchar_t, wchar_t> translation_table;
        std::wstring res_str;
        const auto& lower_dict = m_settings.text_lang == settings::Eng ? eng_dict : rus_dict;
        const auto& upper_dict = m_settings.text_lang == settings::Eng ? eng_upper_dict : rus_upper_dict;

        for(const auto ch : i_str) {
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

                    if (m_settings.upper_lower_rule == settings::upper_lower_rule_t::Only_lower)
                        translated_ch = lower_dict[translated_pos];
                    else if (m_settings.upper_lower_rule == settings::upper_lower_rule_t::Only_upper)
                        translated_ch = upper_dict[translated_pos];
                    else
                        translated_ch = found_ch.first[translated_pos];
                }
                else if(m_settings.non_dict_rule == settings::non_dict_rule_t::Ignore)
                {
                    continue;
                }

                res_str.push_back(translated_ch);
                translation_table[ch] = translated_ch;
            }
        }

        return res_str;
    }

    std::pair<const std::wstring&, std::size_t> program::find_ch_in_dict(wchar_t i_ch) const
    {
        const auto& lower_dict = m_settings.text_lang == settings::Eng ? eng_dict : rus_dict;
        const auto& upper_dict = m_settings.text_lang == settings::Eng ? eng_upper_dict : rus_upper_dict;

        const auto pos = lower_dict.find(i_ch);
        if (pos != std::wstring::npos)
            return {lower_dict, pos};
        else
            return {upper_dict, upper_dict.find(i_ch)};
    }

    key program::gen_key() const
    {
        key o_key;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<std::size_t> a_dist(0
                , (m_settings.text_lang == settings::Eng ? possible_a_eng.size() : possible_a_rus.size()));
        std::uniform_int_distribution<std::uint8_t > b_dist(1
                , (m_settings.text_lang == settings::Eng ? eng_dict.size() + 1 : rus_dict.size() + 1));

        const auto a_idx = a_dist(mt);
        o_key.a = (m_settings.text_lang == settings::Eng ? possible_a_eng[a_idx] : possible_a_rus[a_idx]);
        o_key.b = b_dist(mt);

        return o_key;
    }

    std::string program::settings::to_string() const
    {
        std::ostringstream str;
        str << "Язык шифротекстов: "
            << (text_lang == text_lang_t::Eng ? "Английский" : "Русский")
            << std::endl;
        str << "Символы, не входящие в алфавит: "
            << (non_dict_rule == non_dict_rule_t::Keep ? "Сохранять" : "Игнорировать")
            << std::endl;
        str << "Регистр шифрования: ";
        if (upper_lower_rule == upper_lower_rule_t::Mix)
            str << "Смешанный";
        else if(upper_lower_rule == upper_lower_rule_t::Only_lower)
            str << "Нижний";
        else
            str << "Верхний";

        str << std::endl;
        return str.str();
    }

    std::string key::to_string() const
    {
        std::ostringstream str;
        str << "Ключ " << std::to_string(a) + ":" + std::to_string(b) << std::endl;
        return str.str();
    }

    std::unordered_map<wchar_t, double> program::analyze_freqs(const std::wstring& i_str) const
    {
        std::unordered_map<wchar_t, double> res;
        std::unordered_map<wchar_t, int> tmp_stat;
        std::size_t effective_cnt = 0;

        for(const auto ch : i_str)
        {
            auto ch_pair = tmp_stat.find(ch);
            if (ch_pair != std::end(tmp_stat))
            {
                effective_cnt += 1;
                ch_pair->second++;
            }
            else
            {
                const auto found_ch = find_ch_in_dict(ch);
                if (found_ch.second != std::wstring::npos)
                {
                    effective_cnt += 1;
                    tmp_stat[ch] = 1;
                }
            }
        }

        const auto& lower_dict = m_settings.text_lang == settings::Eng ? eng_dict : rus_dict;
        const auto& upper_dict = m_settings.text_lang == settings::Eng ? eng_upper_dict : rus_upper_dict;

        for(std::size_t i = 0; i < lower_dict.size(); ++i)
        {
            auto lower_it = tmp_stat.find(lower_dict[i]);
            if (lower_it != std::end(tmp_stat))
                res[lower_it->first] = lower_it->second;
            auto upper_it = tmp_stat.find(upper_dict[i]);
            if(upper_it != std::end(tmp_stat))
            {
                if (lower_it != std::end(tmp_stat))
                    res[lower_it->first] += upper_it->second;
                else
                    res[lower_dict[i]] = upper_it->second;
            }
        }

        for (auto& res_stat : res)
            res_stat.second /= static_cast<double >(effective_cnt);

        return res;
    };

    std::vector<program::hack_res> program::hack(const std::string& i_str) const
    {
        using wstr_convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<wstr_convert_type, wchar_t> cvt;

        const auto wide_input_str = cvt.from_bytes(i_str);

        const auto& lower_dict = m_settings.text_lang == settings::Eng ? eng_dict : rus_dict;
        const auto& possible_a_vect = m_settings.text_lang == settings::Eng ? possible_a_eng : possible_a_rus;
        const auto& ref_stats = m_settings.text_lang == settings::Eng ? eng_stats : rus_stats;

        std::vector<program::hack_res> res_stats;

        for(const auto a : possible_a_vect)
        {
            for(std::uint8_t b = 1; b <= lower_dict.size(); ++b)
            {
                const key curr_key(a, b);
                hack_res curr_hack;
                curr_hack.hacked_key = curr_key;

                const auto decrypted_str = decrypt(wide_input_str, curr_key);
                const auto stats = analyze_freqs(decrypted_str);

                for (std::size_t i = 0; i < lower_dict.size(); ++i)
                {
                    auto ch_stat = stats.find(lower_dict[i]);
                    if (ch_stat != std::end(stats))
                        curr_hack.standard_deviation += (pow(ref_stats[i] - ch_stat->second, 2));
                }

                curr_hack.decrypted_str = cvt.to_bytes(decrypted_str);
                curr_hack.standard_deviation = sqrtf(curr_hack.standard_deviation);
                res_stats.emplace_back(std::move(curr_hack));
            }
        }

        return res_stats;
    };

}