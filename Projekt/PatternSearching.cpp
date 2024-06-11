#include "PatternSearching.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void PatternSearching::fillLast()
{
    int n = pattern.size();
    last.resize(26, -1);  // Utworzenie wektora last wype³nionego -1; 26, bo jest 26 ma³ych liter alfabetu angielskiego
    for (int i = 0; i < n; i++)
    {
        last[pattern[i] - 'a'] = i;  // Ustawia ostatnie po³o¿enie ka¿dego znaku
    }
}

void PatternSearching::fillBMNext()
{
    int n = pattern.size();
    bmnext.resize(n + 1, n);  // Utworzenie wektora bmnext
    std::vector<int> Pi(n + 1, 0); // Wektor pomocniczy do bmnext
    Pi[n] = n + 1;  // Ustawia ostatni¹ wartoœæ na o 1 wiêksz¹ ni¿ d³ugoœæ wzorca

    int i = n, j = n + 1;
    while (i > 0)
    {
        while ((j <= n) && (pattern[i - 1] != pattern[j - 1])) // Gdy bie¿¹cy prefikso-sufiks istnieje i nie daje siê rozszerzyæ w lewo
        {
            if (bmnext[j] == n)
            {
                bmnext[j] = j - i; // Przesuniêcie dla niepasuj¹cego sufiksu
            }
            j = Pi[j]; // W j umieszczone jest po³o¿enie prefikso-sufiksu wewnêtrznego
        }
        j--; // Prefikso-sufiks rozszerzany albo nie istnieje
        i--; // Przesuniêcie siê na kolejn¹ pozycjê w lewo
        Pi[i] = j; // Zapisanie po³o¿enia prefikso-sufiksu w wektorze
    }

    j = Pi[0]; // Najd³u¿szy prefikso-sufiks
    for (i = 0; i <= n; i++)
    {
        if (bmnext[i] == n)
        {
            bmnext[i] = j; // W wolnych miejscach umieszczenie po³o¿enia prefikso-sufiksu
        }
        if (i == j)
        {
            j = Pi[j]; // Jak sufiks go nie mieœci, to brany jest kolejny prefikso-sufiks
        }
    }
}

void PatternSearching::setPattern(const std::string& pat)
{
    pattern = pat;
    fillLast();
    fillBMNext();
}

std::vector<int> PatternSearching::search(const std::string& text)
{
    std::vector<int> matches; // Wektor przechowuj¹cy wyst¹pienia wzorca w tekœcie
    int m = text.size();
    int n = pattern.size();
    int i = 0, j;

    while (i <= m - n) // Inaczej: dopóki okno wzorca mieœci siê wewn¹trz tekstu
    {
        j = n - 1; // Porównywanie wzorca z tekstem zaczyna siê od koñca
        while ((j > -1) && (pattern[j] == text[i + j])) // Dopóki znak wzorca pasuje do znaku okna wzorca w tekœcie
        {
            j--;
        }
        if (j == -1)  // Ca³y wzorzec pasuje do okna
        {
            matches.push_back(i);
            i += bmnext[0]; // Przesuniêcie okna na kolejn¹ mo¿liw¹ pozycjê
        }
        else
        {
            // Poprawiona inicjalizacja badCharacter
            int badCharacter = last[text[i + j] - 'a'];
            if (badCharacter == -1)
            {
                badCharacter = j + 1; // Jeœli znak nie wystêpuje w pattern, przesuwamy za ca³e okno
            }
            else
            {
                badCharacter = j - badCharacter; // Obliczamy przesuniêcie na podstawie ostatniego wyst¹pienia znaku
            }
            // Poprawione obliczanie goodSuffix
            int goodSuffix = bmnext[j + 1];
            i += std::max(badCharacter, goodSuffix); // Przesuniêcie pozycji okna wzorca
        }
    }

    return matches;
}
