#include "PatternSearching.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void PatternSearching::fillLast()
{
	int n = pattern.size();
	last.resize(26, -1);  // utworzenie wektora last wypelnionego -1; 26, bo jest 26 malych liter alfabetu angielskiego
	for (int i = 0; i < n; i++)
	{
		last[pattern[i] - 'a'] = i;  // ustawia ostatnie polozenie kazdego znaku
	}
}

void PatternSearching::fillBMNext()
{
	int n = pattern.size();
	bmnext.resize(n + 1, n);   // utworzenie wektora bmnext
	std::vector<int> Pi(n + 1, 0); // wektor pomocniczy do bmnext
	Pi[n] = n + 1;  // ustawia ostatnia wartosc na o 1 wieksza niz dlugosc wzorca

	int i = n, j = n + 1;
	while (i > 0)
	{
		while ((j <= n) && (pattern[i - 1] != pattern[j - 1])) // gdy biezacy prefikso-sufiks istnieje i nie daje sie rozszerzyc w lewo
		{
			if (bmnext[j] == 0)
			{
				bmnext[j] = j - i; // przesuniecie dla niepasujacego sufiksu
			}
			j = Pi[j]; // w j umieszczone jest polozenie prefikso-sufiksu wewnetrznego
		}
		j--; // prefikso-sufiks rozszerzany albo nie istnieje
		i--; // przesuniecie sie na kolejna pozycje w lewo
		Pi[i] = j; // zapisanie polozenia prefikso-sufiksu w wektorze
	}

	j = Pi[0]; // najdluzszy prefikso-sufiks
	for (i = 0; i <= n; i++)
	{
		if (bmnext[i] == 0)
		{
			bmnext[i] = j; // w wolnych miejscach umieszczenie polozenia prefikso-sufiksu
		}
		if (i == j)
		{
			j = Pi[j]; // jak sufiks go nie miesci, to brany jest kolejny prefikso-sufiks
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
	std::vector<int> matches; // wektor przechowujacy wystapienia wzorca w tekscie
	int m = text.size();
	int n = pattern.size();
	int i = 0, j;

	while (i <= m - n) // inaczej: dopoki okno wzorca miesci sie wewnatrz tekstu
	{
		j = n - 1; // porownywanie wzorca z tekstem zaczyna sie od konca
		while ((j > -1) && (pattern[j] == text[i + j])) // dopoki znak wzorca pasuje do znaku okna wzorca w tekscie
		{
			j--;
		}
		if (j == -1)  // caly wzorzec pasuje do okna
		{
			matches.push_back(i);
			i += bmnext[0]; // przesuniecie okna na kolejna mozliwa pozycje
		}
		else
		{
			int badCharacter = j = last[text[i + j] - 'a'];
			int goodSuffix = bmnext[j + 1];
			i += std::max(badCharacter, goodSuffix); // jesli jednak wzorzec nie pasuje to pozycja okna wzorca zwieksza sie o MAX z: przesuniecie pasujacego sufiksu ; ostania pozycja nie pasujacego znaku
		}
	}

	return matches;


}