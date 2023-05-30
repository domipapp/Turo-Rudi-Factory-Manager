#include "Rendeles.h"

Rendeles::Rendeles(RudiMeret rendeltRudi, unsigned db, std::string ID, Time leszallitasiDatum) : rendeltRudi(rendeltRudi), mennyiseg(db), leszallitasiDatum(leszallitasiDatum), ID(ID)
{
}

Rendeles::Rendeles(const Rendeles& right)
{ 
	rendeltRudi = right.rendeltRudi;
	mennyiseg = right.mennyiseg;
	leszallitasiDatum = right.leszallitasiDatum;
	ID = right.ID;
}

RudiMeret Rendeles::getRendeltRudi()const
{
	return rendeltRudi;
}

void Rendeles::setRendeltRudi(const RudiMeret& rendeltRudi)
{
	this->rendeltRudi = rendeltRudi;
}

int Rendeles::getMennyiseg()const
{
	return mennyiseg;
}

void Rendeles::setMennyiseg(const unsigned mennyiseg)
{
	this->mennyiseg = mennyiseg;
}

Time Rendeles::getLeszallitasiDatum() const
{
	return leszallitasiDatum;
}

bool Rendeles::setLeszallitasiDatum(const Time& leszallitasiDatum)
{
	if (leszallitasiDatum > Time()) {//nagyobb az aktualis datumnal
		this->leszallitasiDatum = leszallitasiDatum;
		return true;
	}
	return false;
}

std::string Rendeles::getID() const
{
	return ID;
}

void Rendeles::setID(const std::string& ID)
{
	this->ID = ID;
}

Time Rendeles::teljesitesHossza() const
{
	Time ret(0, 0, 0, 0);//ezzel kell visszaterni
switch (rendeltRudi)
		{
		case(RudiMeret::kicsi):
			if (RudiGyar::getCurrentState() != RudiMeret::kicsi) //ha nem egyezik a jelenlegi allapot a legyartani kivant rudi meretevel allitani kell
				ret += RudiGyar::getAtallitasiIdo();//atalitasi idot hozzaadjuk a hosszt szamolo Time objektumhoz
			ret += unsigned(ceil(24 * mennyiseg / RudiGyar::getKicsiKapacitas()));//ennyi idobe telik a rendelest legyartani, felfele kerekit
			break;

		case(RudiMeret::kozepes)://lasd elozo
			if (RudiGyar::getCurrentState() != RudiMeret::kozepes)
				ret += RudiGyar::getAtallitasiIdo();
			ret += unsigned(ceil(24 * mennyiseg / RudiGyar::getKozepesKapacitas()));
			break;
		case(RudiMeret::nagy)://last elozo elotti
			if (RudiGyar::getCurrentState() != RudiMeret::nagy)
				ret += RudiGyar::getAtallitasiIdo();
			ret += unsigned(ceil(24 * mennyiseg / RudiGyar::getNagyKapacitas()));
			break;
		default:
			break;
		}

	//a gyar valodi allapota nem valtozik, nincs tobb teendo
	return ret;
}

bool Rendeles::operator<(const Rendeles& right) const
{
	return (this->getLeszallitasiDatum()<right.getLeszallitasiDatum());
}

bool Rendeles::operator>(const Rendeles& right) const
{
	return (this->getLeszallitasiDatum() > right.getLeszallitasiDatum());
}

std::ostream& operator<<(std::ostream& os, const RudiMeret& right)
{
	switch (right)
	{
	case(RudiMeret::kicsi):
		os << "kicsi";
		break;

	case(RudiMeret::kozepes):
		os << "kozepes";
		break;
	case(RudiMeret::nagy):
		os << "nagy";
		break;
	default:
		break;
	}
	return os;
}


std::ostream& operator<<(std::ostream& os, const Rendeles& right)
{
	os << "ID: " << right.getID()<< std::endl;
	if (right.getRendeltRudi()== RudiMeret::kicsi)
		os << "Kicsi rudibol ";
	if (right.getRendeltRudi() == RudiMeret::kozepes)
		os << "Kozepes rudibol ";
	if (right.getRendeltRudi() == RudiMeret::nagy)
		os << "Nagy rudibol ";
	os << right.getMennyiseg()<< " darab" << std::endl;
	os << "Leszallitasi datum: " << right.getLeszallitasiDatum()<<std::endl;
	return os;
}
