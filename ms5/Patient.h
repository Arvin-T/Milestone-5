#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H
/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"

namespace seneca
{

    class Patient : public IOAble
    {
    protected:
        char *m_patientName;
        int m_numOHIP;
        Ticket m_ticket;

    public:
        // Constructors
        Patient(Ticket ticket);
        Patient(const Patient &other); // Copy Constructor

        Patient &operator=(const Patient &other);

        ~Patient();

        // Pure virtual function for polymorphism
        virtual char type() const = 0;

        // Equality comparisons
        bool operator==(char rightOperand) const;
        bool operator==(const Patient &patient) const;

        void setArrivalTime();
        Time time() const;
        int number() const;

        operator bool() const;
        operator char *() const;

        void setName(const char *newName);
        void setOHIP(int OHIP);

        virtual std::ostream &write(std::ostream &ostr) const;
        virtual std::istream &read(std::istream &istr);

        friend std::ostream &operator<<(std::ostream &ostr, const Patient &p);
        friend std::istream &operator>>(std::istream &istr, Patient &p);
    };

} // namespace seneca

#endif // SENECA_PATIENT_H
