#pragma once
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<unordered_map>

namespace readfile {
  class parser {
    public:
      parser(const std::string&);
      parser(const parser&) = delete;
      parser(const parser&&) = delete;
      parser& operator=(const parser&) = delete;
      parser& operator=(const parser&&) = delete;
      ~parser() = default;

      int* getNumLibraries();
      int* getNumBooks();
      int* getNumScanning();
      std::vector<int>* getScores();
      std::unordered_map<int, std::vector<int>>* getLibraries();
      std::unordered_map<int, std::vector<int>>* getBooks();

    private:
      std::unordered_map<int, std::vector<int>> libraries;
      std::unordered_map<int, std::vector<int>> books;
      std::vector<int> scores;
      std::string fileName{""};
      int numLibrary{0}, numBooks{0}, numScanning{0};

      void parseInitial(std::string&);
      void parseScores(std::string&);
      void parseLibraryBooks(std::unordered_map<int, std::vector<int>>&, std::string&, const int&);

      void computeProcessDay();
      void computeWeight();

      void processFile();
  };
};

