#include <iostream>

#include <hipo4/reader.h>
#include <thread_pool/BS_thread_pool.hpp>

auto main(int argc, char *argv[]) -> int {

   BS::thread_pool pool;
     
   std::string file = "../data/mydatafile.hipo";

   hipo::reader   r(file.c_str());
   hipo::banklist list = r.getBanks({"REC::Particle","REC::Event"});
   int counter = 0;
   while( r.next(list)&&counter<350){ counter++; list[0].show(); list[1].show();}

}
