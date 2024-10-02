#include <study1/Reader.hpp>

namespace study1 {

Reader::Reader(Histograms& histograms_)
    : histograms(histograms_) {
}

Reader::~Reader() {
}

auto Reader::operator()(const std::string& file) -> void {

    auto dict = hipo::dictionary();
    auto reader = hipo::reader(file, dict);
    auto hipo_event = hipo::event();

    std::cout << "entries : " << reader.getEntries() << std::endl;

    auto REC_Particle = hipo::bank(dict.getSchema("REC::Particle"));

    int counter = 0;
    while (reader.next(hipo_event, REC_Particle) /*&& counter < 10*/) {
        counter++;
        // REC_Particle.show(); // Display the bank

        for (int i = 0; i < REC_Particle.getRows(); i++) {
            int charge = REC_Particle.get<int>("charge", i);
            double vz = REC_Particle.get<double>("vz", i);

            if (charge != 0)
                histograms.hist->Get()->Fill(vz);
        }
    }
}
}  // namespace study1