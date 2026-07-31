#include <skimer/Reader.hpp>

skimer::Reader::Reader(const std::string &output_folder) : m_output_folder(output_folder)
{
}

auto skimer::Reader::operator()(const std::string &run) -> void
{

    std::vector<std::string> files;
    for (const auto &entry : std::filesystem::directory_iterator(run))
    {
        files.push_back(std::string(entry.path()));
    }

    const std::filesystem::path path = run;
    const std::string run_folder = path.filename().string();
    std::cout << "run_folder : " << run_folder << std::endl;

    hipo::reader r1(files[0].c_str());
    auto writer = hipo::writer();

    auto dict1 = hipo::dictionary();
    r1.readDictionary(dict1);

    for (const std::string &s : dict1.getSchemaList())
            writer.getDictionary().addSchema(dict1.getSchema(s.c_str()));

    std::vector<std::string> dst_schema = {"RUN::config","RUN::scaler","REC::Event","REC::Particle","REC::Calorimeter",
    "REC::ForwardTagger", "REC::Scintillator", "REC::Track", "REC::CovMat", "REC::Traj", "REC::Cherenkov", "RUN::config", "RUN::rf"};

    writer.open(std::string("" + m_output_folder + "/skim_run_" + run_folder + ".hipo").c_str());

    for (auto &f : files)
    {
        std::cout << f << std::endl;

        hipo::reader r(f.c_str());
        hipo::banklist list = r.getBanks({"REC::Particle", "REC::Event"});

        auto dict = hipo::dictionary();
        auto hipo_event = hipo::event();
        r.readDictionary(dict);


        
        

        int counter = 0;
        while (r.next(list))
        {
            // outEvent.reset();
            hipo::bank REC_Particle = list[0];
            hipo::bank REC_Event = list[1];
            if (REC_Particle.getRows() < 1)
                continue;

            

            // Check if electron is present :
            bool good_electron_is_present = false;
            for (int i = 0; i < REC_Particle.getRows(); i++)
            {
                int pid = REC_Particle.get<int>("pid", i);
                int status = REC_Particle.get<int>("status", i);
                double chi2pid = REC_Particle.get<double>("chi2pid", i);

                if (pid == 11 && status < 0 && -10 < chi2pid && chi2pid < 10)
                    good_electron_is_present = true;
            }
            if (!good_electron_is_present)
                continue;

            
            counter++;
            r.read(hipo_event);

            hipo::event outEvent = hipo_event;
            outEvent.reset();

            for (const std::string &s: dst_schema) {
                auto bank = hipo::bank(dict.getSchema(s.c_str()));
                hipo_event.getStructure(bank);
                if (bank.getRows() > 0) {
                    outEvent.addStructure(bank);
                }
            }

            writer.addEvent(outEvent);
        }
    }
    
    writer.close();
    writer.showSummary();
}
