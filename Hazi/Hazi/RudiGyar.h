#pragma once
#include "Rendeles.h"
#include "TeljesRendeles.h"
#include <iostream>
#include <vector>
#include <algorithm>
class TeljesRendeles;
class Rendeles;
enum class RudiMeret;
class RudiGyar
{
	//a gyar db/napi gyartasi kapacitasai
	static const unsigned kicsiKapacitas;
	static const unsigned kozepesKapacitas;
	static const unsigned nagyKapacitas;
	static const unsigned atallitasiIdo;//ennyi ora atallitani a gepeket
	static RudiMeret currentState;//a gepek jellenleg ennek a rudinak a gyartasara vannak beallitva
	Time utolsoGyartasVege;//eddigre lesz legyartva minden rendeles
	std::vector<Rendeles> rendelesek;//ezeket a rendeleseket kell teljesiteni, nem teljes rendeleseket hanem sima rendeleseket tarol
	bool autoOptimalize;//insertTeljesRendeles optimalizaljone, alapmeretezetten false
public:
	RudiGyar(Time utolsoGyartasVege = Time(), bool autoOptimalize = false);//deafualt es parameteres konstruktor
	RudiGyar(const RudiGyar& theOther);//copy konstruktor
	void insertTeljesRendeles(const TeljesRendeles& teljesRendeles);//akkor szurja be ha le tudja szallitani
	void optimalize();//optimalizalja a gyartasi folyamator, a legrovidebb idore torekszik
	std::vector<Rendeles> makeRendelesArray(const Rendeles& r1, const  Rendeles& r2, const  Rendeles& r3)const;//3 elemu rendeles vektort csinal
	std::vector<Rendeles> makeRendelesArray(const Rendeles& r1, const  Rendeles& r2)const;//2 elemu rendeles vektort csinal
	std::vector<Rendeles> makeRendelesArray(const Rendeles& r1)const;//1 elemu rendeles vektort csinal
	static unsigned getKicsiKapacitas();//visszaadja a gyar kicsi rudit gyarto kapacitasat
	static unsigned getKozepesKapacitas();//visszaadja a gyar kozepes rudit gyarto kapacitasat
	static unsigned getNagyKapacitas();//visszaadja a gyar nagy rudit gyarto kapacitasat
	static unsigned getAtallitasiIdo();//visszaadja az atallitasi idot oraban
	static RudiMeret getCurrentState();//visszaadja a gepek jelenlegi allapotat
	Time getUtolsoGyartasVege()const;//visszaadja hogy mikorra lesz legyartva minden rendeles
	std::vector<Rendeles> getRendelesek()const;//visszaadja a rendelesek vektorat
	unsigned getRendelesekSzama()const;//visszaadja hogy hany darab rendelest kell legyartani
	bool getAutoOptimalize()const;//visszaadja hogy beszuraskor automatikusan optimalizal-e 
	void setAutoOptimalize(bool autoOptimalize);//beallitja hogy optimalizaljon-e automatikusan
	void setCurrentState(const RudiMeret& currentState);//beallitja a gyar gepeit egy bizonos meret gyartasara 
	std::vector<Rendeles> selectKicsi(const std::vector<Rendeles>& rendelesek)const;//rendelesekbol kivalasztja azokat amelyek kicsi rudit akarnak gyartani
	std::vector<Rendeles> selectKozepes(const std::vector<Rendeles>& rendelesek)const;//rendelesekbol kivalasztja azokat amelyek kozepes rudit akarnak gyartani
	std::vector<Rendeles> selectNagy(const std::vector<Rendeles>& rendelesek)const;//rendelesekbol kivalasztja azokat amelyek nagy rudit akarnak gyartani
	//3 vectort egybe olvaszt balrol jobbra sorrendben
	std::vector<Rendeles> merge(const std::vector<Rendeles>& bal, const std::vector<Rendeles>& kozep, const std::vector<Rendeles>& jobb)const;

};
std::ostream& operator<<(std::ostream& os, const RudiGyar& right);//kiirato/diagnosztikai fuggveny
