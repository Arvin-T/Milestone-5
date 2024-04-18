/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/

#include "IOAble.h"

using namespace std;
namespace seneca
{

    istream &operator>>(istream &is, IOAble &obj)
    {
        return obj.read(is);
    }
    ostream &operator<<(ostream &os, const IOAble &obj)
    {
        return obj.write(os);
    }
}