#include "RudiGyar.h"
const unsigned RudiGyar::kicsiKapacitas = 301000;// db/nap
const unsigned RudiGyar::kozepesKapacitas = 234000;
const unsigned RudiGyar::nagyKapacitas = 177000;
const unsigned RudiGyar::atallitasiIdo = 12;//ora
RudiMeret RudiGyar::currentState = RudiMeret::kicsi;

RudiGyar::RudiGyar(Time utolsoGyartasVege, bool autoOptimalize) :utolsoGyartasVege(utolsoGyartasVege), autoOptimalize(autoOptimalize)
{
}

RudiGyar::RudiGyar(const RudiGyar& theOther)
{
    rendelesek = theOther.rendelesek;
    utolsoGyartasVege = theOther.utolsoGyartasVege;
    autoOptimalize = theOther.autoOptimalize;
}

void RudiGyar::insertTeljesRendeles(const TeljesRendeles& teljesRendeles)
{
    Time tmpT = utolsoGyartasVege;//ha nem tudnank leszallitani nem akarjuk modositani az idot
    if ((tmpT += teljesRendeles.teljesitesHossza()) > teljesRendeles.getLeszallitasiDatum()) {//megnezi le tudja-e leszallitani a kivant idoig
        std::cout << "A teljes redeles nem leszallithato a megadott idon belul" << std::endl;
        return;
    }
    const std::vector<Rendeles> teljesRendelesReszrendelesei = teljesRendeles.getReszRendelesek();
    const int teljesRendelesRendelesSzama = teljesRendelesReszrendelesei.size();
    for (int i = 0; i < teljesRendelesRendelesSzama; i++)//le tudja szallitani, felveszi a rendelesek koze
        rendelesek.push_back(teljesRendelesReszrendelesei[i]);
    utolsoGyartasVege += teljesRendeles.teljesitesHossza();//hozzaadta a rendelesekhez igy kesobbre lesz kesz az osszes rendeles
    RudiGyar::setCurrentState(rendelesek[rendelesek.size() - 1].getRendeltRudi()); //az utolso rendeles rendelesenek a rudimeretere allitja a gyarat
    try {
        if (autoOptimalize)
            RudiGyar::optimalize();
    }
    catch (std::bad_alloc()) {
        std::cout << "Az optimalizalas memoriafoglalasi hibakba utkozott" << std::endl;
    }
    return;
}

void RudiGyar::optimalize()
{
    currentState = RudiMeret::kicsi;// a gyar inditasakor minden gep kicsi gyartasara van allitva
    //rendelesek szetvalogatasa meret szerint
    std::vector<Rendeles> kicsi = RudiGyar::selectKicsi(rendelesek);
    std::vector<Rendeles> kozepes = RudiGyar::selectKozepes(rendelesek);
    std::vector<Rendeles> nagy = RudiGyar::selectNagy(rendelesek);
    //szetvalogatott rendelesek rendezese ugy hogy elol legyen az amit a leghamarabb le kell gyartani
    std::sort(kicsi.begin(), kicsi.end());
    std::sort(kozepes.begin(), kozepes.end());
    std::sort(nagy.begin(), nagy.end());
    rendelesek = merge(kicsi, kozepes, nagy);//osszeolvasztaskor a kicsi elvez elsobbseget mert igy nem kell az elsonel atallitani
    bool teszt = true;//ha igaz akkor optimalizalva van
    Time tmp = utolsoGyartasVege = Time();//alaphelyzetbe allitjuk a gyarat
    do {
        tmp = Time();//minden ciklus elejen alaphelyzet mert sikertelen volt az optimalizalas
        teszt = true;//ha teszt nem valtozik sikeres az optimalizalas
        for (int i = 0; i < rendelesek.size(); i++) {
            tmp += rendelesek[i].teljesitesHossza();
            RudiGyar::setCurrentState(rendelesek[i].getRendeltRudi());
            if (tmp > rendelesek[i].getLeszallitasiDatum()) {//nem lehet megoldani a gyartast
                teszt = false;
                Rendeles tmpR = rendelesek[i];//rendelesek[i] hamarabb kellene legyartani
                rendelesek[i] = rendelesek[i - 1];
                rendelesek[i - 1] = tmpR;
            }
            if (!teszt)
                break;//nem lehet igy megoldani a gyartast ujra kell probalkozni
        }

    } while (!teszt);
    utolsoGyartasVege = tmp;//sikerult az optimalizalas, tmp tarolja a teljesites hosszat
}


std::vector<Rendeles> RudiGyar::makeRendelesArray(const Rendeles& r1, const  Rendeles& r2, const  Rendeles& r3)const
{
    std::vector<Rendeles> tmp;
    tmp.push_back(r1);
    tmp.push_back(r2);
    tmp.push_back(r3);
    return tmp;
}

std::vector<Rendeles> RudiGyar::makeRendelesArray(const Rendeles& r1, const Rendeles& r2)const
{
    std::vector<Rendeles> tmp;
    tmp.push_back(r1);
    tmp.push_back(r2);
    return tmp;
}

std::vector<Rendeles> RudiGyar::makeRendelesArray(const Rendeles& r1)const
{
    std::vector<Rendeles> tmp;
    tmp.push_back(r1);
    return tmp;
}

unsigned RudiGyar::getKicsiKapacitas()
{
    return kicsiKapacitas;
}

unsigned RudiGyar::getKozepesKapacitas()
{
    return kozepesKapacitas;
}

unsigned RudiGyar::getNagyKapacitas()
{
    return nagyKapacitas;
}

unsigned RudiGyar::getAtallitasiIdo()
{
    return atallitasiIdo;
}

RudiMeret RudiGyar::getCurrentState()
{
    return currentState;
}

Time RudiGyar::getUtolsoGyartasVege()const
{
    return utolsoGyartasVege;
}


std::vector<Rendeles> RudiGyar::getRendelesek()const
{
    return rendelesek;
}

unsigned RudiGyar::getRendelesekSzama()const
{
    return (unsigned)rendelesek.size();
}

bool RudiGyar::getAutoOptimalize()const
{
    return autoOptimalize;
}

void RudiGyar::setAutoOptimalize(bool autoOptimalize)
{
    this->autoOptimalize = autoOptimalize;
}

void RudiGyar::setCurrentState(const RudiMeret& currentState)
{
    this->currentState = currentState;
}

std::vector<Rendeles> RudiGyar::selectKicsi(const std::vector<Rendeles>& rendelesek)const
{
    std::vector<Rendeles> kicsi;
    for (int i = 0; i < rendelesek.size(); i++)
        if ((int)rendelesek[i].getRendeltRudi() == (int)RudiMeret::kicsi)//kicsiket valogatja
            kicsi.push_back(rendelesek[i]);
    return kicsi;
}

std::vector<Rendeles> RudiGyar::selectKozepes(const std::vector<Rendeles>& rendelesek)const
{
    std::vector<Rendeles> kozepes;
    for (int i = 0; i < rendelesek.size(); i++)
        if ((int)rendelesek[i].getRendeltRudi() == (int)RudiMeret::kozepes)//kozepeseket valogatja
            kozepes.push_back(rendelesek[i]);
    return kozepes;
}

std::vector<Rendeles> RudiGyar::selectNagy(const std::vector<Rendeles>& rendelesek)const
{
    std::vector<Rendeles> nagy;
    for (int i = 0; i < rendelesek.size(); i++)
        if ((int)rendelesek[i].getRendeltRudi() == (int)RudiMeret::nagy)//nagyokat valogatja
            nagy.push_back(rendelesek[i]);
    return nagy;
}

std::vector<Rendeles> RudiGyar::merge(const std::vector<Rendeles>& bal, const std::vector<Rendeles>& kozep, const std::vector<Rendeles>& jobb)const
{
    std::vector<Rendeles> ret = bal;//bekerul a baloldali
    for (int i = 0; i < kozep.size(); i++)//bekerul a kozepso
        ret.push_back(kozep[i]);
    for (int i = 0; i < jobb.size(); i++)//bekerul a jobboldali
        ret.push_back(jobb[i]);
    return ret;
}


std::ostream& operator<<(std::ostream& os, const RudiGyar& right)
{
    os << "Kicsi rudi kapacitas: " << right.getKicsiKapacitas() << "db/ nap;\nKozepes rudi kapacitas: " << right.getKozepesKapacitas() <<
        "db/ nap;\nNagy rudi kapacitas: " << right.getNagyKapacitas() << "db/ nap;\nAtallasi ido: " << right.getAtallitasiIdo() << "ora" << std::endl;
    switch (right.getCurrentState()) {
    case(RudiMeret::kicsi):
        os << "Gepek ennek a gyartasara beallitva: kicsi" << std::endl;
        break;
    case(RudiMeret::kozepes):
        os << "Gepek ennek a gyartasara beallitva: kozepes" << std::endl;
        break;
    case(RudiMeret::nagy):
        os << "Gepek ennek a gyartasara beallitva: nagy" << std::endl;
        break;
    default:
        break;
    }
    os << "Rendelesek szama: " << right.getRendelesekSzama() << std::endl;
    const std::vector<Rendeles> rightRendelesei = right.getRendelesek();
    for (unsigned i = 0; i < right.getRendelesekSzama(); i++)
        os << rightRendelesei[i] << std::endl;
    os << "Utolso gyartas vege: " << right.getUtolsoGyartasVege() << std::endl;
    return os;
}
