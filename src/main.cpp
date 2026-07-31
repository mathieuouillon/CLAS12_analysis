#include <algorithm>
#include <filesystem>
#include <iostream>
#include <ranges>

#include <hipo4/reader.h>
#include <skimer/Reader.hpp>
#include <thread_pool/multi_thread.hpp>

auto read_folder_in_directory(const std::filesystem::path& directory)
    -> std::vector<std::string> {
    auto f = [](const std::filesystem::directory_entry& entry) {
        return std::string(entry.path());
    };
    auto pred = [](std::string_view fileName) {
        return !(fileName.find(".") != std::string::npos);
    };

    std::vector<std::string> fileNames;
    std::vector<std::string> output;
    std::vector<std::string> reduceFiles;
    auto iterator = std::filesystem::directory_iterator{directory};
    std::transform(begin(iterator), end(iterator), std::back_inserter(fileNames), f);
    std::ranges::copy_if(fileNames, std::back_inserter(output), pred);
    std::ranges::sort(output);
    return output;
}

auto main(int argc, char* argv[]) -> int {
    std::vector<std::string> target_types = {"CuSn"};
    
    for (const auto& target_type : target_types) {
        std::cout << "Target: " << target_type << std::endl;
        std::vector<std::string> runs = read_folder_in_directory("/cache/clas12/rg-d/production/pass1/recon/" + target_type + "/dst/recon/");
        std::cout << "nb runs: " << runs.size() << std::endl;

        for (const auto& s : runs)
            std::cout << "Runs process: " << s << std::endl;

        skimer::Reader reader("/volatile/clas12/ouillon/skim_pass1_RGD/" + target_type);

        multi_thread_reader(reader, runs, 40);
    }
}
