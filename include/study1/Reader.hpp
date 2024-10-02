#pragma once

#include <string>

#include <hipo4/reader.h>

namespace study1 {

class Reader {
   private:
    /* data */
   public:
    // ****** constructors and destructor
    Reader(/* args */);
    ~Reader();

    // ****** public methods
    auto operator()(const std::string& file) -> void;
};

}  // namespace study1