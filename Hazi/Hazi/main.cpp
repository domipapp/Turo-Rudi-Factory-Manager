#define  _CRTDBG_MAP_ALLOC
#include "Time.h"
#include "RudiGyar.h"
#include "TeljesRendeles.h"
#include "Rendeles.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	cout << fixed << setprecision(0);
	cout << "--------------------------------------\n";
	{
		RudiGyar rudiGyar;
		Rendeles rendeles1(RudiMeret::kicsi, 1500000, "rendeles1");
		Rendeles rendeles2(RudiMeret::kozepes, 2500000, "rendeles2");
		Rendeles rendeles3(RudiMeret::nagy, 3500000, "rendeles3");
		cout << rendeles1 << endl << rendeles2 << endl << rendeles3 << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*id, jelenlegi datum, leszallitasi datum es a beallitott rendelesek
		ID: rendeles1
		Kicsi rudibol 1500000 darab
		Leszallitasi datum: 2021.4.1  0H
		ID: rendeles2
		Kozepes rudibol 2500000 darab
		Leszallitasi datum: 2021.4.1  0H
		ID: rendeles3
		Nagy rudibol 3500000 darab
		Leszallitasi datum: 2021.4.1  0H
		*/
		rendeles1.setRendeltRudi(RudiMeret::kozepes);
		rendeles2.setMennyiseg(4500000);
		cout << rendeles1 << endl << rendeles2 << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*modosult rendles1 es rendeles2
		ID: rendeles1
		Kozepes rudibol 1500000 darab
		Leszallitasi datum: 2021.4.1  0H
		ID: rendeles2
		Kozepes rudibol 4500000 darab
		Leszallitasi datum: 2021.4.1  0H
		*/
		vector<Rendeles> rendelesTomb = rudiGyar.makeRendelesArray(rendeles1, rendeles2);
		cout << rendelesTomb[0] << endl << rendelesTomb[1] << endl;
		rendeles1.setMennyiseg(1000000);
		cout << rendelesTomb[0] << endl << rendeles1 << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*makeRendelesArray mukodik, ha valtoztatom az eredetit a tombben levo nem valtozik.
		ID: rendeles1
		Kozepes rudibol 1500000 darab
		Leszallitasi datum: 2021.4.1  0H
		ID: rendeles2
		Kozepes rudibol 4500000 darab
		Leszallitasi datum: 2021.4.1  0H
		ID: rendeles1
		Kozepes rudibol 1500000 darab
		Leszallitasi datum: 2021.4.1  0H
		ID: rendeles1
		Kozepes rudibol 1000000 darab
		Leszallitasi datum: 2021.4.1  0H
		*/
		Time ido1(2021, 4, 16, 19);
		TeljesRendeles teljesRendeles1(ido1, rendelesTomb);
		rendelesTomb[0].setMennyiseg(0);
		cout << rendelesTomb[0] << endl;
		cout << teljesRendeles1 << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*	rendelesTomb[0].setMennyiseg(0); nem valtozat a TeljesRendelesen
		ID: rendeles1
		Kozepes rudibol 0 darab
		Leszallitasi datum: 2021.4.1  0H

		ID: 0; Leszallitasi datum:  2021.4.16  19H
		rendelesek szama: 2
		redelesek:
		Resz rendeles 1:
		ID: rendeles1
		Kozepes rudibol 1500000 darab
		Leszallitasi datum: 2021.4.16  19H
		Resz rendeles 2:
		ID: rendeles2
		Kozepes rudibol 4500000 darab
		Leszallitasi datum: 2021.4.16  19H
		*/
		Time teszt(2022, 12, 30, 23);
		cout << (teszt += 1) << endl;
		cout << (teszt += Time(0, 0, 0, 1)) << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*mindket operator+= mukodik
		2023.0.0  0H
		2023.0.0  1H
		*/
		Rendeles rendeles4 = Rendeles(RudiMeret::kicsi, RudiGyar::getKicsiKapacitas(), "rendeles4");
		Rendeles rendeles5 = Rendeles(RudiMeret::kozepes, RudiGyar::getKozepesKapacitas(), "rendeles5");
		Rendeles rendeles6 = Rendeles(RudiMeret::nagy, RudiGyar::getNagyKapacitas(), "rendeles6");
		vector<Rendeles> rendelesTomb2 = rudiGyar.makeRendelesArray(rendeles4, rendeles5, rendeles6);
		TeljesRendeles teljesRendeles2(ido1, rendelesTomb2);
		cout << teljesRendeles2.teljesitesHossza() << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*24+12+24+12+24 ora = 4 nap
		0.0.4  0H
		*/
		cout << RudiGyar::getCurrentState() << endl << teljesRendeles1 << endl;
		cout << teljesRendeles1.teljesitesHossza() << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/* 2-> currentState= kicsi(ez az alapmeretezett),1500000+4500000 = 6000000db kozepes rudi. kozepesKapacitas: 234000;
		*6000000/234000=25,64nap= 615,38ora=616ora; +12ora(atallitani kicsirol kozepesre)=628ora= 26 nap 4 ora
		kicsi
		ID: 0; Leszallitasi datum:  2021.4.16  19H
		rendelesek szama: 2
		redelesek:
		Resz rendeles 1:
		ID: rendeles1
		Kozepes rudibol 1500000 darab
		Leszallitasi datum: 2021.4.16  19H
		Resz rendeles 2:
		ID: rendeles2
		Kozepes rudibol 4500000 darab
		Leszallitasi datum: 2021.4.16  19H

		0.0.26  2H
		*/
		cout << "teszt:" << teszt << endl;
		cout << "ido1:" << ido1 << endl;
		if (teszt > ido1)
			cout << "teszt > ido1" << endl;
		if (ido1 < teszt)
			cout << "ido < teszt" << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*teszt mindig nagyobb mint ido1, osszehasonlitas mukodik
		teszt:2023.0.0  1H
		ido1:2021.4.16  19H
		teszt > ido1
		ido < teszt
		*/
		Time ido2 = Time(2022, 0, 0, 0);
		cout << rudiGyar;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*default ido; 0 gyartani valo; alapmeretezett meret beallitas: kicsi
		Kicsi rudi kapacitas: 301000db/ nap;
		Kozepes rudi kapacitas: 234000db/ nap;
		Nagy rudi kapacitas: 177000db/ nap;
		Atallasi ido: 12ora
		Gepek ennek a gyartasara beallitva: kicsi
		Teljes rendelesek szama: 0
		Utolso gyartas vege: 2021.4.1  0H
		*/
		rudiGyar.insertTeljesRendeles(teljesRendeles1);
		cout << "--------------------------------------\n";
		//vart kimenet
		/*teljesites1 nem kerul gyartasra mert nem tudja leszallitani a gyar a kert idoig
		A teljes redeles nem leszallithato a megadott idon belul
		*/
		teljesRendeles2.setLeszallitasiDatum(ido2);
		rudiGyar.insertTeljesRendeles(teljesRendeles2);
		cout << rudiGyar << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*teljesrendeles2 teljesitesi ideje 4 nap; utolso rendeles rudimerete: nagy; a gyar le tudja szallitani 2022.0.0.0-ig
		Kicsi rudi kapacitas: 301000db/ nap;
		Kozepes rudi kapacitas: 234000db/ nap;
		Nagy rudi kapacitas: 177000db/ nap;
		Atallasi ido: 12ora
		Gepek ennek a gyartasara beallitva: nagy
		Rendelesek szama: 3
		ID: rendeles4
		Kicsi rudibol 301000 darab
		Leszallitasi datum: 2022.0.0  0H

		ID: rendeles5
		Kozepes rudibol 234000 darab
		Leszallitasi datum: 2022.0.0  0H

		ID: rendeles6
		Nagy rudibol 177000 darab
		Leszallitasi datum: 2022.0.0  0H

		Utolso gyartas vege: 2021.4.5  0H
		*/
		teljesRendeles1.setLeszallitasiDatum(Time(2021, 5, 5, 0));
		rudiGyar.insertTeljesRendeles(teljesRendeles1);
		cout << rudiGyar << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*teljesrendeles1 a lista vegere kerul
		Kicsi rudi kapacitas: 301000db/ nap;
		Kozepes rudi kapacitas: 234000db/ nap;
		Nagy rudi kapacitas: 177000db/ nap;
		Atallasi ido: 12ora
		Gepek ennek a gyartasara beallitva: kozepes
		Rendelesek szama: 5
		ID: rendeles4
		Kicsi rudibol 301000 darab
		Leszallitasi datum: 2022.0.0  0H

		ID: rendeles5
		Kozepes rudibol 234000 darab
		Leszallitasi datum: 2022.0.0  0H

		ID: rendeles6
		Nagy rudibol 177000 darab
		Leszallitasi datum: 2022.0.0  0H

		ID: rendeles1
		Kozepes rudibol 1500000 darab
		Leszallitasi datum: 2021.5.5  0H

		ID: rendeles2
		Kozepes rudibol 4500000 darab
		Leszallitasi datum: 2021.5.5  0H

		Utolso gyartas vege: 2021.5.0  2H
		*/
		rudiGyar.optimalize();
		cout << rudiGyar << endl;
		cout << "--------------------------------------\n";
		//vart kimenet
		/*optimalizalt, rendezettebb gyartasi folyamat
		Kicsi rudi kapacitas: 301000db/ nap;
		Kozepes rudi kapacitas: 234000db/ nap;
		Nagy rudi kapacitas: 177000db/ nap;
		Atallasi ido: 12ora
		Gepek ennek a gyartasara beallitva: nagy
		Rendelesek szama: 5
		ID: rendeles4
		Kicsi rudibol 301000 darab
		Leszallitasi datum: 2022.0.0  0H

		ID: rendeles1
		Kozepes rudibol 1500000 darab
		Leszallitasi datum: 2021.5.5  0H

		ID: rendeles2
		Kozepes rudibol 4500000 darab
		Leszallitasi datum: 2021.5.5  0H

		ID: rendeles5
		Kozepes rudibol 234000 darab
		Leszallitasi datum: 2022.0.0  0H

		ID: rendeles6
		Nagy rudibol 177000 darab
		Leszallitasi datum: 2022.0.0  0H

		Utolso gyartas vege: 2021.4.30  14H
		*/
	}
	_CrtDumpMemoryLeaks();
}