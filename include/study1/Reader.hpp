#pragma once

#include <string>

#include <hipo4/reader.h>
#include <study1/Histograms.hpp>

namespace study1 {

class Reader {
   private:
    Histograms &histograms;
   public:
    // ****** constructors and destructor
    explicit Reader(Histograms &histograms_);
    ~Reader();

    // ****** public methods
    auto operator()(const std::string& file) -> void;
};

}  // namespace study1