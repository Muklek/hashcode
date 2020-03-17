#include<iostream>
#include<fstream>

#include "writefile.hpp"

typedef std::vector<int> vi;
typedef std::unordered_map<int, vi> uivi;
typedef std::pair<int, vi> pivi;
typedef std::string st;

using namespace writefile;

stream::stream(st f, uivi* b, uivi* l, vi* i)
  :filename(f), books(b), libraries(l), libIndex(i){};

void stream::output(){
  std::fstream file;
  file.open("./output/" + filename);

  int const size{static_cast<int>(libIndex->size())};
  constexpr int numBooks{0};

  int lib{0}, libSize{0};
  vi* bookList{nullptr};

  file << size;
  file << '\n';

  for(int i{0}; i < size; i++){
    lib = libIndex->at(i);
    libSize = libraries->at(lib).at(numBooks);
    bookList = &books->at(lib);

    file << lib;
    file << " ";
    file << libSize;
    file << '\n';

    for(const int& book : *bookList){
      file << book;
      file << " ";
    }
    file<< '\n';
  }
  file.close();
};

