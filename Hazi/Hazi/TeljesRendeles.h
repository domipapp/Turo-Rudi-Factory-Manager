#pragma once
#include "Rendeles.h"
#include "Time.h"
#include "RudiGyar.h"
#include <iostream>
#include <cmath>
#include <vector>
class Rendeles;
class TeljesRendeles
{
	static int nextId;//teljes rendeles kovetkezo id-ja
	int ID;//teljes rendeles id-ja
	std::vector<Rendeles> reszRendelesek;//rendeles objektumokat tartalmazo vektor
	Time leszallitasiDatum;//meddig kell leszallitani a teljes rendelest

public:
	TeljesRendeles(Time& leszallitasiDatum, std::vector<Rendeles>& reszRendelesek);//standard parameteres konstruktor
	TeljesRendeles();//default konstruktor, a leszallitasi datum (0,0,0,0)
	TeljesRendeles(const TeljesRendeles& right);//standard copy konstruktor
	Time getLeszallitasiDatum()const;//visszaadja hogy meddig kell leszallitani a teljes rendelest
	bool setLeszallitasiDatum(const Time& leszallitasiDatum);//beallitja hogy meddig kell leszallitani a teljes rendelest
	std::vector<Rendeles> getReszRendelesek()const;//visszaadja a teljes rendeles reszrendeleseinek a vektorat(tombjet)
	void setReszRendelesek(const std::vector<Rendeles>& reszrendelesek);//beallitja/modositja a teljes rendeles reszrendeleseinek a vektorat(tombjet)
	int getID()const;//visszaadja a teljes rendeles id-jat
	Time teljesitesHossza()const;//visszaadja hogy mennyi ido teljesiteni/legyartani az egesz teljes rendelest
	void operator=(const TeljesRendeles& right);//standard egyenlo operator
};
std::ostream& operator<<(std::ostream& os,const TeljesRendeles& right);//kiirato/diagnosztikai fuggveny


