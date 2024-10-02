#include <study1/Reader.hpp>

namespace study1 {

Reader::Reader(/* args */) {
}

Reader::~Reader() {
}

auto Reader::operator()(const std::string& file) -> void {

    auto dict = hipo::dictionary();
    auto reader = hipo::reader(file, dict);
    auto hipo_event = hipo::event();

    auto REC_Particle = hipo::bank(dict.getSchema("REC::Particle"));

    int counter = 0;
    while (reader.next(hipo_event, REC_Particle) && counter < 10) {
        counter++;
        REC_Particle.show();
    }
}
}  // namespace study1