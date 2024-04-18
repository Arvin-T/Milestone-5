/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/

#include <iostream>
#include <iomanip>
#include <stdio.h>

#include "Time.h"
#include "Utils.h"

using namespace std;

namespace seneca
{

    istream &Time::read(istream &istr)
    {
        int hours;
        int mins;
        char colon = '\0';
        istr >> hours;
        istr >> colon;
        if (colon != ':')
        {
            istr.setstate(ios::failbit);
            return istr;
        }
        else
        {
            istr >> mins;
            this->m_minutes = hours * 60 + mins;
        }
        return istr;
    }
    istream &operator>>(istream &istr, Time &T)
    {
        return T.read(istr);
    }
    Time &Time::reset()
    {
        this->m_minutes = U.getTime();
        return *this;
    }

    Time::Time(unsigned int min)
    {
        this->m_minutes = min;
    }

    ostream &Time::write(ostream &ostr) const
    {
        int mins = this->m_minutes % 60;
        int hours = this->m_minutes / 60;

        ostr << setfill('0') << setw(2) << hours << ':' << setw(2) << mins;
        return ostr;
    }
    ostream &operator<<(ostream &ostr, const Time &T)
    {
        return T.write(ostr);
    }
    Time::operator unsigned int() const
    {
        return this->m_minutes;
    }

    Time &Time::operator*=(int val)
    {
        this->m_minutes *= val;
        return *this;
    }
    Time &Time::operator-=(const Time &D)
    {
        this->m_minutes -= D.m_minutes;
        if (this->m_minutes < 0)
        {
            this->m_minutes += 1440;
        }
        return *this;
    }

    Time Time::operator-(const Time &T) const
    {
        Time newObj(*this);
        newObj -= T;
        return newObj;
    }

}
