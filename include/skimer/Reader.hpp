#pragma once

#include <string>
#include <iostream>
#include <filesystem>

#include <hipo4/reader.h>
#include <hipo4/writer.h>

namespace skimer {

class Reader {
        public:
            // ****** constructors and destructor
            Reader(const std::string &output_folder);

            // ****** public methods
            auto operator()(const std::string &file) -> void;

        private:
            // ****** private members
            const std::string target_type_;
            const std::string m_output_folder;

            // ****** private methods
    };
}