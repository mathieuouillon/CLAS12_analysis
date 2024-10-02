#include <iostream>

#include <TCanvas.h>
#include <TH1D.h>
#include <TLine.h>
#include <TROOT.h>

#include <hipo4/reader.h>
#include <study1/Reader.hpp>
#include <thread_pool/multi_thread.hpp>

int main(int argc, char* argv[]) {
    ROOT::EnableThreadSafety();  // To stop random errors in multithread mode

    std::vector<std::string> files = {"../data/mydatafile.hipo"};
    study1::Reader reader;
    multithread_reader(reader, files, 1);

    return EXIT_SUCCESS;
}
