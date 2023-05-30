#include "TeljesRendeles.h"
int TeljesRendeles::nextId = 0;

TeljesRendeles::TeljesRendeles(Time& leszallitasiDatum, std::vector<Rendeles>& reszRendelesek):ID(nextId++)
{
	this->leszallitasiDatum = leszallitasiDatum;
	this->reszRendelesek = reszRendelesek;
	const int reszRendelesSzama = reszRendelesek.size();
	for (int i = 0; i < reszRendelesSzama; i++)
		this->reszRendelesek[i].setLeszallitasiDatum(leszallitasiDatum);//a reszrendeleseket is legkesobb a teljes rendeles leszallitasi datumaig le kell szallitani
}

TeljesRendeles::TeljesRendeles():ID(nextId++), leszallitasiDatum(Time(0, 0, 0, 0))
{
}



TeljesRendeles::TeljesRendeles(const TeljesRendeles& right) :ID(nextId++), leszallitasiDatum(right.leszallitasiDatum), reszRendelesek(right.reszRendelesek)
{
}

Time TeljesRendeles::getLeszallitasiDatum()const 
{
	return leszallitasiDatum;
}

bool TeljesRendeles::setLeszallitasiDatum(const Time& leszallitasiDatum)
{
	if (leszallitasiDatum > Time())//nagyobb az aktualis datumnal
		this->leszallitasiDatum = leszallitasiDatum;
	else
		return false;
	for (int i = 0; i < reszRendelesek.size(); i++)//a reszrendelesek datumait is at kell allitani
		this->reszRendelesek[i].setLeszallitasiDatum(leszallitasiDatum);
	return true;
}

std::vector<Rendeles> TeljesRendeles::getReszRendelesek() const
{
	return reszRendelesek;
}

void TeljesRendeles::setReszRendelesek(const std::vector<Rendeles>& reszrendelesek)
{
	this->reszRendelesek = reszRendelesek;
}

int TeljesRendeles::getID() const
{
	return ID;
}

Time TeljesRendeles::teljesitesHossza() const
{
	Time ret(0,0,0,0);//ezzel kell visszaterni
	RudiMeret tmp = RudiGyar::getCurrentState();//kezdeti allapot elmentese
	for (unsigned i = 0; i < reszRendelesek.size(); i++) {
		switch (reszRendelesek[i].getRendeltRudi())
		{
		case(RudiMeret::kicsi):
			if (tmp != RudiMeret::kicsi) {//ha nem egyezik a jelenlegi allapot a legyartani kivant rudi meretevel allitani kell
				ret += RudiGyar::getAtallitasiIdo();//atalitasi idot hozzaadjuk a hosszt szamolo Time objektumhoz
				tmp= RudiMeret::kicsi;//atallitjuk a gyar jelenlegi allapotat
			}
			ret += unsigned(ceil(24* reszRendelesek[i].getMennyiseg() / RudiGyar::getKicsiKapacitas()));//ennyi idobe telik a resz rendelest legyartani, felfele kerekit
			break;

		case(RudiMeret::kozepes)://lasd elozo
			if (tmp != RudiMeret::kozepes) {
				ret += RudiGyar::getAtallitasiIdo();
				tmp= RudiMeret::kozepes;
			}
			ret += unsigned(ceil(24* reszRendelesek[i].getMennyiseg() / RudiGyar::getKozepesKapacitas()));
			break;
		case(RudiMeret::nagy)://last elozo elotti
			if (tmp != RudiMeret::nagy) {
				ret += RudiGyar::getAtallitasiIdo();
				tmp= RudiMeret::nagy;
			}
			ret += unsigned(ceil(24* reszRendelesek[i].getMennyiseg() / RudiGyar::getNagyKapacitas()));
			break;
		default:
			break;
		}

	}
	//a gyar valodi allapota nem valtozik, nincs tobb teendo
	return ret;
}

void TeljesRendeles::operator=(const TeljesRendeles& right)
{
	ID = nextId++;
	leszallitasiDatum = right.leszallitasiDatum;
	reszRendelesek = right.reszRendelesek;
}


std::ostream& operator<<(std::ostream& os,const TeljesRendeles& right)
{
	os << "ID: "<<right.getID() << "; Leszallitasi datum:  " << right.getLeszallitasiDatum() << std::endl << "rendelesek szama: "<< right.getReszRendelesek().size()<<std::endl<<"redelesek: "<<std::endl;
	const std::vector<Rendeles> rightReszRendelesei = right.getReszRendelesek();
	const int rightReszRendeleseinekSzama = right.getReszRendelesek().size();
	for (size_t i = 0; i < rightReszRendeleseinekSzama; i++)
		os <<"Resz rendeles "<<i+1<<":"<< std::endl<< rightReszRendelesei[i];
	return os;
}
