#include "ConvexHull.h"
#include <algorithm>
#include <cmath>
#include <iostream>


std::vector<Vertex> ConvexHull::calculateConvexHull(std::vector<Vertex> v)
{
	int n = v.size();
	if (n < 3) return std::vector<Vertex>(); //bo otoczka potrzebuje conajmniej 3 punktow, nwm czy to potrzebne, bo na poziomie genracji grafu juz odrzuca ta mozliwosc ig  


	int minYid = 0; // zmienna do szukania punktu z najmniejszym Y (jezeli jest kilka punktów o najmniejszym Y to wybiera ten najbardziej na lewo)
	for (int i = 1; i < n; i++)
	{
		if (v[i].gety() < v[minYid].gety() || (v[i].gety() == v[minYid].gety() && v[i].getx() < v[minYid].getx()))
		{
			minYid = i;
		}
	}

	int q, p = minYid; // id punktow ktorymi bede szukac otoczki
	std::vector<Vertex> convexHull; //wektor, w ktorym beda punkty nalezace do otoczki
	std::vector<bool> used(n, false);
	for (int i = 0; i < n; i++)
	{
		q = (p + 1) % n; // po prostu nastêpny punkt, ale daje modulo ilosc punktow, zeby ciagle iterowac po punktach
		for (int j = 0; j < n; j++) //petla do szukania kiedy wzystkie 3 punkty uloza sie przeciwnie do wskazowek zegara
		{
			if (crossProduct(v[p], v[q], v[j]) == 2 || (crossProduct(v[p], v[q], v[j]) == 0 && !used[j] && distance(v[p], v[j]) > distance(v[p], v[q])))
			{
				q = j;
			}
		}
		p = q;
		convexHull.push_back(v[p]);
		used[p] = true;

		if (p == minYid)
		{
			break; // jak powroce do punktu z ktorego zaczelam to wychodze z petli
		}
	}

	return convexHull;
}

float ConvexHull::crossProduct(Vertex p, Vertex q, Vertex r)
{
	float n = (q.getx() - p.getx()) * (r.gety() - q.gety()) - (q.gety() - p.gety()) * (r.getx() - q.getx()); // iloczyn wektorowy
	if (n == 0) return 0; // kolinearne
	if (n > 0) return 1; // zgodnie z ruchem wskazowek zegara
	else return 2; // przeciwnie z ruchem wskazowek zegara
}

float ConvexHull::distance(Vertex p, Vertex q)
{
	return sqrt(pow(q.getx() - p.getx(), 2) + pow(q.gety() - p.gety(), 2));
}

float ConvexHull::perimeter(std::vector<Vertex>& v)
{
	float calculatePerimeter = 0;

	for (int i = 1; i < v.size(); i++)
	{
		calculatePerimeter += sqrt(pow(v[i].getx() - v[i - 1].getx(), 2) + pow(v[i].gety() - v[i - 1].gety(), 2));
	}
	// obliczanie dlugosci ostatniego odcinka - z punktu ostatniego w wektorze do punktu pierwszego w wektorze
	calculatePerimeter += sqrt(pow(v[v.size() - 1].getx() - v[0].getx(), 2) + pow(v[v.size() - 1].gety() - v[0].gety(), 2));
	return calculatePerimeter;

}
