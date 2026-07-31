#pragma once 

#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <thread_pool/BS_thread_pool.hpp>
#include <thread_pool/BS_thread_pool_utils.hpp>

template<typename T>
auto format_string(const T a, int precision = 2) -> std::string {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << a;
    return stream.str();
}

template<class Reader>
auto multi_thread_reader(Reader &reader, const std::vector<std::string> &files, const int cores = 6) -> void {
    auto begin = std::chrono::high_resolution_clock::now();
    BS::synced_stream sync_out;
    BS::thread_pool pool(cores);
    for (auto &file: files) pool.detach_task([&reader, &file]
            {
                reader(file);
            }
        );

    auto total = static_cast<float>(pool.get_tasks_total());

    while (true) {
        pool.wait_for(std::chrono::seconds(5));
        if (pool.get_tasks_total() > 0) std::cout << "Process : " << format_string((1. - static_cast<double>(pool.get_tasks_total()) / total) * 100)
                                                  << "% " << pool.get_tasks_total() << " tasks total." << std::endl;
        else break;
    }
    pool.wait();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Process : " << format_string((1. - static_cast<double>(pool.get_tasks_total()) / total) * 100) << "% " << pool.get_tasks_total() << " tasks total." << std::endl;
    std::cout << "Done in " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "s" << std::endl;
}