/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#ifndef SENECA_TICKET_H_
#define SENECA_TICKET_H_
#include <iostream>

#include "Time.h"
#include "IOAble.h"
namespace seneca
{
    class Ticket : public IOAble
    {
        Time m_time;
        int m_number;

    public:
        Ticket(int);
        Time time() const;
        int number() const;
        void resetTime();
        std::ostream &write(std::ostream &) const;
        std::istream &read(std::istream &);
    };
}
#endif
