/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H
#include <iostream>

using namespace std;
namespace seneca
{
    class IOAble
    {
    public:
        friend ostream &operator<<(ostream &, const IOAble &);
        friend istream &operator>>(istream &, IOAble &);
        virtual ~IOAble(){};
        virtual ostream &write(ostream &) const = 0;
        virtual istream &read(istream &) = 0;
    };

}
#endif
