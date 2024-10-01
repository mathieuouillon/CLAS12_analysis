#include <iostream>

#include <TH1D.h>
#include <TCanvas.h>

#include <hipo4/reader.h>
#include <thread_pool/BS_thread_pool.hpp>

auto main(int argc, char *argv[]) -> int {

   auto hist = std::make_unique<TH1D>("hist","", 100, -20, 20);

  BS::thread_pool pool;

  std::string file = "../data/mydatafile.hipo";

  hipo::reader r(file.c_str());
  hipo::banklist list = r.getBanks({"REC::Particle", "REC::Event"});
  int counter = 0;
  while (r.next(list) && counter < 350) {
    counter++;
    list[0].show();
    list[1].show();
for(int r = 0; r < list[0].getRows(); r++){
    if(list[0].getInt("charge",r)!=0) hist->Fill(list[0].getFloat("vz",r));
}
  }

  TCanvas canvas("", "", 800, 600);
  hist->Draw();
  canvas.SaveAs("hist.pdf");
}
