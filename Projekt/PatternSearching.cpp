#include "PatternSearching.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void PatternSearching::fillLast()
{
    int n = pattern.size();
    last.resize(26, -1);  // Utworzenie wektora last wype�nionego -1; 26, bo jest 26 ma�ych liter alfabetu angielskiego
    for (int i = 0; i < n; i++)
    {
        last[pattern[i] - 'a'] = i;  // Ustawia ostatnie po�o�enie ka�dego znaku
    }
}

void PatternSearching::fillBMNext()
{
    int n = pattern.size();
    bmnext.resize(n + 1, n);  // Utworzenie wektora bmnext
    std::vector<int> Pi(n + 1, 0); // Wektor pomocniczy do bmnext
    Pi[n] = n + 1;  // Ustawia ostatni� warto�� na o 1 wi�ksz� ni� d�ugo�� wzorca

    int i = n, j = n + 1;
    while (i > 0)
    {
        while ((j <= n) && (pattern[i - 1] != pattern[j - 1])) // Gdy bie��cy prefikso-sufiks istnieje i nie daje si� rozszerzy� w lewo
        {
            if (bmnext[j] == n)
            {
                bmnext[j] = j - i; // Przesuni�cie dla niepasuj�cego sufiksu
            }
            j = Pi[j]; // W j umieszczone jest po�o�enie prefikso-sufiksu wewn�trznego
        }
        j--; // Prefikso-sufiks rozszerzany albo nie istnieje
        i--; // Przesuni�cie si� na kolejn� pozycj� w lewo
        Pi[i] = j; // Zapisanie po�o�enia prefikso-sufiksu w wektorze
    }

    j = Pi[0]; // Najd�u�szy prefikso-sufiks
    for (i = 0; i <= n; i++)
    {
        if (bmnext[i] == n)
        {
            bmnext[i] = j; // W wolnych miejscach umieszczenie po�o�enia prefikso-sufiksu
        }
        if (i == j)
        {
            j = Pi[j]; // Jak sufiks go nie mie�ci, to brany jest kolejny prefikso-sufiks
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
    std::vector<int> matches; // Wektor przechowuj�cy wyst�pienia wzorca w tek�cie
    int m = text.size();
    int n = pattern.size();
    int i = 0, j;

    while (i <= m - n) // Inaczej: dop�ki okno wzorca mie�ci si� wewn�trz tekstu
    {
        j = n - 1; // Por�wnywanie wzorca z tekstem zaczyna si� od ko�ca
        while ((j > -1) && (pattern[j] == text[i + j])) // Dop�ki znak wzorca pasuje do znaku okna wzorca w tek�cie
        {
            j--;
        }
        if (j == -1)  // Ca�y wzorzec pasuje do okna
        {
            matches.push_back(i);
            i += bmnext[0]; // Przesuni�cie okna na kolejn� mo�liw� pozycj�
        }
        else
        {
            // Poprawiona inicjalizacja badCharacter
            int badCharacter = last[text[i + j] - 'a'];
            if (badCharacter == -1)
            {
                badCharacter = j + 1; // Je�li znak nie wyst�puje w pattern, przesuwamy za ca�e okno
            }
            else
            {
                badCharacter = j - badCharacter; // Obliczamy przesuni�cie na podstawie ostatniego wyst�pienia znaku
            }
            // Poprawione obliczanie goodSuffix
            int goodSuffix = bmnext[j + 1];
            i += std::max(badCharacter, goodSuffix); // Przesuni�cie pozycji okna wzorca
        }
    }

    return matches;
}
