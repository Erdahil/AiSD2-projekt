#include "PatternSearching.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void PatternSearching::fillLast()
{
	int n = pattern.size();
	last.resize(26, -1);  // utworzenie wektora last wype³nionego -1; 26, bo jest 26 ma³ych liter alfabetu angielskiego
	for (int i = 0; i < n; i++)
	{
		last[pattern[i] - 'a'] = i;  // ustawia ostatnie po³o¿enie ka¿dego znaku
	}
}

void PatternSearching::fillBMNext()
{
	int n = pattern.size();
	bmnext.resize(n + 1, n);  // utworzenie wektora bmnext
	std::vector<int> Pi(n + 1, 0); // wektor pomocniczy do bmnext
	Pi[n] = n + 1;  // wstawia ostatni¹ wartoœæ na o 1 wieksza niz d³ugosc wzorca

	int i = n, j = n + 1;
	while (i > 0)
	{
		while ((j <= n) && (pattern[i - 1] != pattern[j - 1])) // gdy bie¿¹cy prefikso-sufiks istnieje i nie daje siê rozszerzyæ w lewo
		{
			if (bmnext[j] == n)
			{
				bmnext[j] = j - i; // przesuniecie dla niepasuj¹cego sufiksu
			}
			j = Pi[j]; // w j umieszczone jest po³o¿enie prefikso-sufiksu wewnêtrznego
		}
		j--; // prefikso-sufiks rozszerzany albo nie istnieje
		i--; // przesuniecie sie na kolejna pozycje w lewo
		Pi[i] = j; // zapisanie po³o¿enia prefikso-sufiksu w wektorze
	}

	j = Pi[0]; // najdluzszy prefikso-sufiks
	for (i = 0; i <= n; i++)
	{
		if (bmnext[i] == n)
		{
			bmnext[i] = j; // w wolnych miejscach umieszczenie po³o¿enia prefikso-sufiksu
		}
		if (i == j)
		{
			j = Pi[j]; // jak sufiks go nie mieœci, to brany jest kolejny prefikso-sufiks
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
	std::vector<int> matches; // wektor przechowuj¹cy wyst¹pienia wzorca w tekœcie
	int m = text.size();
	int n = pattern.size();
	int i = 0, j;

	while (i <= m - n) // inaczej: dopóki okno wzorca mieœci siê wewn¹trz tekstu
	{
		j = n - 1; // porównywanie wzorca z tekstem zaczyna siê od koñca
		while ((j > -1) && (pattern[j] == text[i + j])) // dopóki znak wzorca pasuje do znaku okna wzorca w tekœcie
		{
			j--;
		}
		if (j == -1)  // ca³y wzorzec pasuje do okna
		{
			matches.push_back(i);
			i += bmnext[0]; // przesuniêcie okna na kolejn¹ mo¿liw¹ pozycjê
		}
		else
		{
			// poprawiona inicjalizacja badCharacter
			int badCharacter = last[text[i + j] - 'a'];
			if (badCharacter == -1)
			{
				badCharacter = j + 1; // jeœli znak nie wystêpuje w pattern, przesuwamy za ca³e okno
			}
			else
			{
				badCharacter = j - badCharacter; // obliczamy przesuniêcie na podstawie ostatniego wyst¹pienia znaku
			}
			// poprawione obliczanie goodSuffix
			int goodSuffix = bmnext[j + 1];
			i += std::max(badCharacter, goodSuffix); // przesuniêcie pozycji okna wzorca
		}
	}

	return matches;
}
