#include<iostream>
#include<fstream>
#include<cmath>

#include "readfile.hpp"

using namespace readfile;
using namespace std;

typedef std::vector<int> vi;
typedef std::pair<int, vi> pivi;
typedef std::unordered_map<int, vi> uivi;


parser::parser(const string& name):fileName(name){
  processFile();
}

int* parser::getNumLibraries(){
  return &numLibrary;
}

int* parser::getNumBooks(){
  return &numBooks;
}

int* parser::getNumScanning(){
  return &numScanning;
}

vi* parser::getScores(){
  return &scores;
}

uivi* parser::getLibraries(){
  return &libraries;
}

uivi* parser::getBooks(){
  return &books;
}

void parser::parseInitial(string& line){
  static int numCount{0}, parsedValue{0};
  string number{""};

  istringstream sline(line);

  while(getline(sline, number, ' ')){
    parsedValue = stoi(number);

    switch(numCount){
      case 0:
        numBooks = parsedValue;
        break;
      case 1:
        numLibrary = parsedValue;
        break;
      case 2:
        numScanning = parsedValue;
        break;
    }
    ++numCount;
  }
}

void parser::parseScores(string& line){
  string number{""};
  static int parsedValue{0};

  istringstream sline(line);

  while(getline(sline, number, ' ')){
    parsedValue = stoi(number);
    scores.emplace_back(parsedValue);
  }
}

void parser::parseLibraryBooks(uivi& map, string& line, const int& library){
  string number{""};
  int parsedValue{0};

  map.insert({library, {}});

  istringstream sline(line);

  while(getline(sline, number, ' ')){
    parsedValue = stoi(number);
    map.at(library).push_back(parsedValue);
  }
}

inline void parser::computeProcessDay(){
  static int process{0}, totalDays{0}, libID{0};
  static double numDays{0}, numBooks{0};

  for(const pivi& lib : libraries){
    const vi* const libVal{&lib.second};
    libID = lib.first;

    numBooks = static_cast<double>(libVal->at(0));
    numDays = static_cast<double>(libVal->at(2));

    process = std::ceil(numBooks / numDays);
    totalDays = process + libVal->at(1);

    libraries.at(libID).emplace_back(totalDays);
  }
}

inline void parser::computeWeight(){
  static int weight{0}, localWeight{0}, library{0};

  for(const pivi& libBooks : books){
    library = libBooks.first;
    const vi& bookList{libBooks.second};

    for(const int& book : bookList){
      localWeight = scores[book];
      weight += localWeight;
    }

    libraries.at(library).emplace_back(weight);
    weight = 0;
  }
}

void parser::processFile(){
  fstream file;
  string const fileDir{"./input/" + fileName};
  file.open(fileDir);

  int lineCount{0}, library{0};
  string line{""};

  while(std::getline(file, line)){

    switch(lineCount){
      case 0:
        parseInitial(line);
        break;
      case 1:
        parseScores(line);
        break;
      default:
        if(lineCount % 2 == 0)
          parseLibraryBooks(libraries, line, library);
        else {
          parseLibraryBooks(books, line, library);
          ++library;
        }
        break;
    }
    ++lineCount;
  }
  file.close();

  computeProcessDay();
  computeWeight();
}

