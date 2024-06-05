#pragma once
#include <vector>
#include <string>

// klasa do szukania wzorca w tekscie pelnym algorytmem Boyera-Moore'a

class PatternSearching
{
private:
    std::string pattern;
    std::vector<int> Last;
    std::vector<int> BMNext;

    // wypelnienie wektora Last - wyznacza ostanie po�o�enia znak�w alfabetu we wzorcu
    void fillLast();

    // wypelnianie wektora BMNext - zawiera wartosci przesuniec dla poszczegolnych sufiksow wzorca
    void fillBMNext();

public:
    // ustawianie wzorca + przygotowanie wektorow Last i BMNext
    void setPattern(const std::string& pat);

    //wyszukiwanie wzorca
    std::vector<int> search(const std::string& text);
};
