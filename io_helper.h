//
// Created by Богдан Василенко on 21/12/2019.
//

#ifndef AFFINE_CIPHERS_IO_HELPER_H
#define AFFINE_CIPHERS_IO_HELPER_H

#include "literals.h"

#include <string>
#include <vector>
#include <iostream>
#include <functional>

namespace utils_ns {
    class io_helper {
    public:
        template<typename INPUT_T>
        struct ask_and_options
        {
            const std::string ask;
            std::vector<INPUT_T> options;
        };


        template<typename INPUT_T>
        static INPUT_T get_input(const ask_and_options<INPUT_T>& i_ask_and_options)
        {
            return get_input<INPUT_T>(i_ask_and_options.ask, [&i_ask_and_options](const INPUT_T& inp)
            {
                if(std::find(std::begin(i_ask_and_options.options), std::end(i_ask_and_options.options), inp)
                   != std::end(i_ask_and_options.options))
                    return true;
                else
                    return false;
            });
        }


        template<typename INPUT_T>
        static INPUT_T get_input(const std::string &i_ask,
                                 std::function<bool(const INPUT_T &)> i_check = [](const INPUT_T &) { return true; }) {
            INPUT_T answ;
            std::cout << i_ask << std::endl << "> ";
            std::cout.flush();
            std::cin >> answ;

            while (!std::cin.good()  || !i_check(answ)) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');


                std::cout << INCORRECT_INPUT << std::endl;
                std::cout << i_ask << std::endl << '>';
                std::cin >> answ;
            }


            return answ;
        }

        static std::string get_string(const std::string &i_ask) {
            std::cout << i_ask << std::endl << "> ";
            std::cin.ignore(1);
            std::string answ;
            std::getline(std::cin, answ);
            return answ;
        }
    };
}
#endif //AFFINE_CIPHERS_IO_HELPER_H
