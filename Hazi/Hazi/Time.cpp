#include "Time.h"


Time::Time(unsigned year, unsigned month, unsigned day, unsigned hour)
{

	this->year = year;
	this->month= month;
	this->day = day;
	this->hour = hour;

}

bool Time::setYear(unsigned set)
{
	if (set >= currentYear) {//csak jelenlegi vagy jovobeli evre allithato
		year = set;
		return true;
	}
	return false;
}

bool Time::setMonth(unsigned set)
{
	if (set >= 1 && set <= 12) {//a honapokat 1-12 ig ertelmezzuk
		month = set;
		return true;
	}
	return false;
}

bool Time::setDay(unsigned set)
{
	if (set >= 1 && set <= 30) {//minden honapot 30 naposnak ertelmezunk
		day = set;
		return true;
	}
	return false;
}

bool Time::setHour(unsigned set)
{
	if (set >= 0 && set <= 23) {//az orakat 0-23 kozott ertelmezzuk, a 24 ora az 0 ora
		hour = set;
		return true;
	}
	return false;
}

unsigned Time::getYear() const
{
	return year;
}

unsigned Time::getMonth() const
{
	return month;
}

unsigned Time::getDay() const
{
	return day;
}

unsigned Time::getHour() const
{
	return hour;
}

unsigned Time::getInHours() const
{
	return (year * 365 * 30 * 24 + month * 30 * 24 + day * 24 + hour);
}

bool Time::operator<(const Time& right) const
{
	if (this->getInHours() < right.getInHours())//kisebb ha 0,0,0,0 ota eltelt ido kisebb
		return true;
	return false;
}

bool Time::operator>(const Time& right) const
{
	if (this->getInHours() > right.getInHours())//kisebb ha 0, 0, 0, 0 ota eltelt ido kisebb
		return true;
	return false;
}

Time Time::operator+=(const unsigned hour)
{
	this->hour += hour;//minden orat elobb az orahoz hozza adjuk
	do {
		if (this->hour >= 24) {//ha valtani kell napot 24 orat levonunk es noveljuk a napot eggyel
			this->hour -= 24;
			day++;
		}
		if (day > 30) {//ha valtani kell honapot a honapot noveljuk eggyel
			day = 0;
			month++;
		}
		if (month > 12) {//ha valtani kell evet noveljuk az evet eggyel
			month = 0;
			year++;
		}
	} 	while (this->hour >= 24);//addig csinaljuk amig az ora ertelmezheto tartomanyba nem esik
	return *this;
}

Time Time::operator+=(const Time& right)
{
	*this += right.getInHours();//oraban adjuk hozza 
	return *this;
}


std::ostream& operator<<(std::ostream& os, const Time& right)
{
	os << right.getYear() << "." << right.getMonth() << "." << right.getDay() << "  " << right.getHour() << "H";
	return os;
}
