#pragma once
#include "Time.h"
#include "RudiGyar.h"
#include<iostream>
#include <string>
enum class RudiMeret { kicsi, kozepes, nagy };
std::ostream& operator<<(std::ostream& os, const RudiMeret& right);//rudi meret kiirato fuggveny
	class Rendeles
	{
		Time leszallitasiDatum;//meddig kell leszallitani a rendelest
		RudiMeret rendeltRudi;//a rendelt rudi merete
		unsigned mennyiseg;//a rendelt rudi mennyisege
		std::string ID;//a rendeles id-ja/neve
	public:
		//standard konstruktor, az aktualis datum az alapmeretezett leszallitasi ido
		Rendeles(RudiMeret rendeltRudi = RudiMeret::kicsi, unsigned db = 0, std::string ID = "Reszrendeles", Time leszallitasiDatum = Time());
		Rendeles(const Rendeles& right);//standard copy konstruktor
		RudiMeret getRendeltRudi()const;//visszaadja a rendelt rudi meretet
		void setRendeltRudi(const RudiMeret& rendeltRudi);//beallitja a rendelt rudi meretet
		int getMennyiseg()const;//visszaadja a rendelt rudi mennyiseget
		void setMennyiseg(const unsigned mennyiseg);//beallitja a rendelt rudi mennyiseget
		Time getLeszallitasiDatum()const;//visszaadja hogy meddig kell leszallitani a rendelest
		bool setLeszallitasiDatum(const Time& leszallitasiDatum);//beallitja hogy meddig kell leszallitani a rendelest
		std::string getID()const;//visszaadja a rendeles id-jat/nevet
		void setID(const std::string& ID);//beallitja a rendeles id-jat/nevet
		Time teljesitesHossza()const;//visszaadja a rendeles teljesitesehez szukseges idot atallitassal
		bool operator<(const Rendeles& right)const;//leszallitasi ido szerinti osszehasonlito fuggveny
		bool operator>(const Rendeles& right)const;//leszallitasi ido szerinti osszehasonlito fuggveny
	};
	std::ostream& operator<<(std::ostream&os, const Rendeles& right);//rendeles kiirato diagnosztikai fuggveny


