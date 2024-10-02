#pragma once

#include <TH1.h>
#include <TH2.h>
#include <ROOT/TThreadedObject.hxx>

using TTO_TH1D = ROOT::TThreadedObject<TH1D>;
using TTO_TH2D = ROOT::TThreadedObject<TH2D>;
using up_TTO_TH1D = const std::unique_ptr<TTO_TH1D>;
using up_TTO_TH2D = const std::unique_ptr<TTO_TH2D>;

namespace study1 {

struct Histograms {
    up_TTO_TH1D hist = std::make_unique<TTO_TH1D>("vz", "", 200, -20, 20);
};

}  // namespace study1