// std includes
#include <iostream>

// fmt includes
#include <fmt/core.h>

// ROOT includes
#include <TCanvas.h>
#include <TH1D.h>
#include <TLine.h>
#include <TROOT.h>

// Core includes
#include <hipo4/reader.h>
#include <thread_pool/multi_thread.hpp>

// Study 1 includes
#include <study1/Reader.hpp>
#include <study1/Histograms.hpp>

int main(int argc, char* argv[]) {
    fmt::println("Start program!");
    ROOT::EnableThreadSafety();  // To stop random errors in multithread mode

    std::vector<std::string> files = {"../data/mydatafile.hipo"};
    
    auto histograms = study1::Histograms();

    study1::Reader reader(histograms);
    multithread_reader(reader, files, 1);

    const std::shared_ptr<TH1D> hist = histograms.hist->Merge();

    TCanvas canvas("c1", "", 800, 600);
    hist->Draw();
    canvas.SaveAs("hist.pdf");

    return EXIT_SUCCESS;
}
