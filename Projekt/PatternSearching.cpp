#include "PatternSearching.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void PatternSearching::fillLast()
{
	int n = pattern.size();
	last.resize(26, -1);  // utworzenie wektora last wype�nionego -1; 26, bo jest 26 ma�ych liter alfabetu angielskiego
	for (int i = 0; i < n; i++)
	{
		last[pattern[i] - 'a'] = i;  // ustawia ostatnie po�o�enie ka�dego znaku
	}
}

void PatternSearching::fillBMNext()
{
	int n = pattern.size();
	bmnext.resize(n + 1, n);  // utworzenie wektora bmnext
	std::vector<int> Pi(n + 1, 0); // wektor pomocniczy do bmnext
	Pi[n] = n + 1;  // wstawia ostatni� warto�� na o 1 wieksza niz d�ugosc wzorca

	int i = n, j = n + 1;
	while (i > 0)
	{
		while ((j <= n) && (pattern[i - 1] != pattern[j - 1])) // gdy bie��cy prefikso-sufiks istnieje i nie daje si� rozszerzy� w lewo
		{
			if (bmnext[j] == n)
			{
				bmnext[j] = j - i; // przesuniecie dla niepasuj�cego sufiksu
			}
			j = Pi[j]; // w j umieszczone jest po�o�enie prefikso-sufiksu wewn�trznego
		}
		j--; // prefikso-sufiks rozszerzany albo nie istnieje
		i--; // przesuniecie sie na kolejna pozycje w lewo
		Pi[i] = j; // zapisanie po�o�enia prefikso-sufiksu w wektorze
	}

	j = Pi[0]; // najdluzszy prefikso-sufiks
	for (i = 0; i <= n; i++)
	{
		if (bmnext[i] == n)
		{
			bmnext[i] = j; // w wolnych miejscach umieszczenie po�o�enia prefikso-sufiksu
		}
		if (i == j)
		{
			j = Pi[j]; // jak sufiks go nie mie�ci, to brany jest kolejny prefikso-sufiks
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
	std::vector<int> matches; // wektor przechowuj�cy wyst�pienia wzorca w tek�cie
	int m = text.size();
	int n = pattern.size();
	int i = 0, j;

	while (i <= m - n) // inaczej: dop�ki okno wzorca mie�ci si� wewn�trz tekstu
	{
		j = n - 1; // por�wnywanie wzorca z tekstem zaczyna si� od ko�ca
		while ((j > -1) && (pattern[j] == text[i + j])) // dop�ki znak wzorca pasuje do znaku okna wzorca w tek�cie
		{
			j--;
		}
		if (j == -1)  // ca�y wzorzec pasuje do okna
		{
			matches.push_back(i);
			i += bmnext[0]; // przesuni�cie okna na kolejn� mo�liw� pozycj�
		}
		else
		{
			// poprawiona inicjalizacja badCharacter
			int badCharacter = last[text[i + j] - 'a'];
			if (badCharacter == -1)
			{
				badCharacter = j + 1; // je�li znak nie wyst�puje w pattern, przesuwamy za ca�e okno
			}
			else
			{
				badCharacter = j - badCharacter; // obliczamy przesuni�cie na podstawie ostatniego wyst�pienia znaku
			}
			// poprawione obliczanie goodSuffix
			int goodSuffix = bmnext[j + 1];
			i += std::max(badCharacter, goodSuffix); // przesuni�cie pozycji okna wzorca
		}
	}

	return matches;
}
