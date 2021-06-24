#ifndef READER_HPP_
#define READER_HPP_

#include "network.hpp"
#include "arraylist.hpp"
#include "redblacktree.hpp"

Network* read_file(char* path, ArrayList<Manufacturer>& manufs, ArrayList<Chemists>& chems);

void write(std::ostream& fout, Network& net, ArrayList<Manufacturer>& makers, ArrayList<Chemists>& sellers);

#endif
