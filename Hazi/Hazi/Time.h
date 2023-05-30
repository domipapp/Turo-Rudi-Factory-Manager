#pragma once
#include <iostream>
//jelenlegi datum
const int currentYear = 2021;
const int currentMonth = 4;
const int currentDay = 1;
const int currentHour = 0;
class Time
{
	//datum: ev honap nap ora
	unsigned year= currentYear;
	unsigned month = currentMonth;
	unsigned day= currentDay;
	unsigned hour= currentHour;
	
public:
	Time(unsigned year = currentYear, unsigned month = currentMonth, unsigned day = currentDay, unsigned hour = currentHour);//alapmeretezetten a jelenlegi datum
	bool setYear(unsigned set);//beallitja az evet
	bool setMonth(unsigned set);//beallitja a honapot
	bool setDay(unsigned set);//beallitja a napot
	bool setHour(unsigned set);//beallitja az orat
	unsigned getYear()const;//visszaadja az evet
	unsigned getMonth()const;//visszaadja a honapot
	unsigned getDay()const;//visszaadja a napot
	unsigned getHour()const;//visszaadja az orat
	unsigned getInHours()const;//visszaadja az idot oraban
	bool operator<(const Time& right)const;//osszehasonlito fuggveny
	bool operator>(const Time& right)const;//osszehasonlito fuggveny
	Time operator+=(const unsigned hour);//oraval valo osszeado fuggveny
	Time operator+=(const Time& right);//datumot datummal osszeado fuggveny
};
std::ostream& operator<<(std::ostream& os, const Time& right);//kiirato/diagynosztikai fuggveny

