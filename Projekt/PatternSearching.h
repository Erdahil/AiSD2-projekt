#pragma once
#include <vector>
#include <string>

// klasa do szukania wzorca w tekscie pelnym algorytmem Boyera-Moore'a

class PatternSearching
{
private:
    std::string pattern;
    std::vector<int> last;
    std::vector<int> bmnext;

    // wypelnienie wektora last - wyznacza ostanie po³o¿enia znaków alfabetu we wzorcu
    void fillLast();

    // wypelnianie wektora bmnext - zawiera wartosci przesuniec dla poszczegolnych sufiksow wzorca
    void fillBMNext();

public:
    // ustawianie wzorca + przygotowanie wektorow last i bmnext
    void setPattern(const std::string& pat);

    //wyszukiwanie wzorca
    std::vector<int> search(const std::string& text);
};
