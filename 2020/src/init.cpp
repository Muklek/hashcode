#include<array>

#include "booksorter.hpp"
#include "readfile.hpp"
#include "writefile.hpp"

int main(){
  std::array<std::string, 6> files{"a_example.txt",
                                   "b_read_on.txt",
                                   "c_incunabula.txt",
                                   "d_tough_choices.txt",
                                   "e_so_many_books.txt",
                                   "f_libraries_of_the_world.txt"};

  std::array<std::string, 6> outfile{"a.txt","b.txt","c.txt",
                                     "d.txt","e.txt","f.txt"};

  for(int i{0}; i<6; i++){

    readfile::parser file{files[i]};
    int* numLibrary{file.getNumLibraries()};
    int* numBooks{file.getNumBooks()};
    int* deadline{file.getNumScanning()};
    std::vector<int>* scores{file.getScores()};
    std::unordered_map<int, std::vector<int>>* properties{file.getLibraries()};
    std::unordered_map<int, std::vector<int>>*  books{file.getBooks()};

    BookSorter bs{numLibrary, numBooks, deadline, scores, properties, books};
    bs.processLibraries();
    std::vector<int>* libIndex{bs.getLibraries()};

    writefile::stream print{outfile[i], books, properties, libIndex};
    print.output();
  }
};
