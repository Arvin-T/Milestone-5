/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#ifndef SENECA_TIME_H
#define SENECA_TIME_H
using namespace std;
namespace seneca
{
    class Time
    {

    public:
        int m_minutes;
        operator unsigned int() const;
        Time &operator*=(int val);
        Time &operator-=(const Time &D);
        Time operator-(const Time &T) const;
        Time &reset();
        Time(unsigned int min = 0u);
        ostream &write(ostream &ostr = cout) const;
        istream &read(istream &istr = cin);
        friend ostream &operator<<(ostream &ostr, const Time &T);
        friend istream &operator>>(istream &istr, Time &T);
    };

}
#endif
