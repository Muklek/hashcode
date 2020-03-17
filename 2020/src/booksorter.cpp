#include<algorithm>
#include<numeric>
#include<cmath>

#include "booksorter.hpp"

typedef std::vector<int> vi;
typedef std::pair<int, vi> pivi;
typedef std::unordered_map<int, int> uii;
typedef std::unordered_map<int, vi> uivi;


BookSorter::BookSorter(int* l, int* b, int* d,
                       vi* sc, uivi* pr, uivi* bo)
      :numLibrary(l), numBooks(b), deadline(d),
      properties(pr), books(bo), scores(sc){

  libIndex.reserve(*numLibrary);
  for(const pivi& lib : *properties){
    libIndex.emplace_back(lib.first);
  }
};


vi* BookSorter::getLibraries(){
  return &libIndex;
};


inline void BookSorter::sortLibraries(int min, int max, int lookup, auto compare){
  int endPoint{static_cast<int>(libIndex.size())-1 - max};
  std::sort(libIndex.begin() + min,
            libIndex.end() - endPoint,
            [=](const int& a, const int& b){
    return compare(properties->at(a).at(lookup),
                   properties->at(b).at(lookup));
  });
}

inline void BookSorter::sortBooks(int library){
  vi* bookList{&books->at(library)};
  std::sort(bookList->begin(), bookList->end(),
            [=](const int& a, const int& b){
     return scores->at(a) > scores->at(b);
  });
}

inline void BookSorter::storeBookTracker(int min, int max){
  for(int i{min}, libID{0}; i <= max; i++){
    libID = libIndex.at(i);
    for(const int& bookIndex : books->at(libID)){
      if(bookTracker.find(bookIndex) == bookTracker.end()){
        bookTracker.insert({bookIndex, 1});
      }
      else {
        bookTracker.at(bookIndex) += 1;
      }
    }
  }
}

inline void BookSorter::cleanDuplicates(int min, int max){
  storeBookTracker(min, max);

  for(int i{max}, lib{0}, book{0}; i >= min; i--){
    lib = libIndex.at(i);

    for(int j{0}; j<books->at(lib).size();){
      book = books->at(lib).at(j);

      if(bookTracker.find(book) != bookTracker.end() &&
         bookTracker.at(book) > 1){
        books->at(lib).erase(books->at(lib).begin()+j);
        bookTracker.at(book) -= 1;
      }
      else ++j;
    }
    sortBooks(lib);
  }
}


inline void BookSorter::cleanLibraries(){
  for(int i{0}, lib{0}; i<libIndex.size();){
    lib = libIndex[i];
    if(books->at(lib).size() == 0){
      libIndex.erase(libIndex.begin()+i);
    }
    else ++i;
  }
}

inline void BookSorter::updateLibraryProperties(int min, int max){
  static int process{0}, totalDays{0}, lib{0}, sumBooks{0}, sumWeight{0};
  static double numDays{0}, numBook{0};

  vi* bookList{nullptr};

  for(int i{min}; i <= max; i++){
    lib = libIndex[i];
    bookList = &books->at(lib);

    sumBooks = bookList->size();
    numBook = static_cast<double>(sumBooks);
    numDays = static_cast<double>(properties->at(lib).at(indexes::bookProcess));

    process = std::ceil(numBook / numDays);
    totalDays = process + properties->at(lib).at(indexes::signup);

    sumWeight = std::accumulate(bookList->begin(), bookList->end(), 0,
        [=](int acc, const int& bookIndex){
          return acc + scores->at(bookIndex);
        }
    );

    properties->at(lib).at(indexes::totalProcess) = totalDays;
    properties->at(lib).at(indexes::numBook) = sumBooks;
    properties->at(lib).at(indexes::weight) = sumWeight;
  }
}

inline bool BookSorter::hasEqualSignup(const int& indexA, const int& indexB){
  int libA{libIndex[indexA]}, libB{libIndex[indexB]};
  return properties->at(libA).at(indexes::signup) ==
         properties->at(libB).at(indexes::signup);
}

void BookSorter::processLibraries(){
  sortLibraries(0, libIndex.size()-1, indexes::signup,
      [](const int& a, const int& b){ return a < b; });

  for(int min{0}, max{0}; max < libIndex.size(); max++){

    while(max < libIndex.size()-1 && hasEqualSignup(max, max+1)) ++max;

    sortLibraries(min, max, indexes::totalProcess,
        [](const int& a, const int& b){ return a < b; });

    cleanDuplicates(min, max);
    updateLibraryProperties(min, max);

    sortLibraries(min, max, indexes::weight,
        [](const int& a, const int& b){ return a > b; });

    min = max + 1;
  }

  cleanLibraries();
}

