/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <typeinfo>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>

#include "Patient.h"
using namespace std;
namespace seneca
{
    Patient::Patient(Ticket ticket) : m_patientName(nullptr), m_numOHIP(0), m_ticket(ticket)
    {
    }
    Patient::Patient(const Patient &patient) : m_ticket(patient.m_ticket)
    {
        if (patient.m_patientName)
        {
            m_patientName = new char[strlen(patient.m_patientName) + 1];
            strcpy(m_patientName, patient.m_patientName);
        }
        else
        {
            m_patientName = nullptr;
        }
        m_numOHIP = patient.m_numOHIP;
    }
    Patient &Patient::operator=(const Patient &other)
    {
        if (this != &other)
        {
            delete[] m_patientName;

            m_patientName = nullptr;
            if (other.m_patientName)
            { // Check for valid name
                m_patientName = new char[std::strlen(other.m_patientName) + 1];
                std::strcpy(m_patientName, other.m_patientName);
            }

            m_numOHIP = other.m_numOHIP;
            m_ticket = other.m_ticket;
        }
        return *this;
    }
    Patient::~Patient()
    {
        delete[] m_patientName;
    }
    bool Patient::operator==(char rightOperand) const
    {
        return type() == rightOperand;
    }
    bool Patient::operator==(const Patient &patient) const
    {
        if (typeid(*this).name() != typeid(patient).name())
        {
            return false;
        }

        return true;
    }

    int Patient::number() const
    {
        return m_ticket.number();
    }
    void Patient::setArrivalTime()
    {
        m_ticket.resetTime();
    }
    Time Patient::time() const
    {
        return m_ticket.time();
    }
    Patient::operator bool() const
    {
        return (m_numOHIP >= 100000000 && m_numOHIP <= 999999999) && m_patientName != nullptr;
    }
    Patient::operator char *() const
    {
        return m_patientName;
    }
    void Patient::setName(const char *newName)
    {
        delete[] m_patientName;
        m_patientName = nullptr;

        if (newName)
        {
            m_patientName = new char[std::strlen(newName) + 1];
            std::strcpy(m_patientName, newName);
        }
    }

    void Patient::setOHIP(int OHIP)
    {
        m_numOHIP = (OHIP >= 100000000 && OHIP <= 999999999) ? OHIP : m_numOHIP;
    }
    std::ostream &Patient::write(std::ostream &ostr) const
    {
        if (&ostr == &std::cout)
        {
            if (*this)
            { // Valid patient record
                ostr << m_ticket << std::endl
                     << m_patientName << ", OHIP: " << m_numOHIP << std::endl;
            }
            else
            {
                ostr << "Invalid Patient Record" << std::endl;
            }
        }
        else if (&ostr == &std::clog)
        {
            ostr << std::left << std::setw(53) << std::setfill('.') << (m_patientName ? m_patientName : "Invalid Patient Record") << std::setfill(' ') << m_numOHIP << std::right << std::setw(5) << m_ticket.number() << ' ' << m_ticket.time();
        }
        else
        { // CSV
            if (*this)
            {
                ostr << type() << ',' << m_patientName << ',' << m_numOHIP << ',';
                m_ticket.write(ostr);
            }
            else
            {
                ostr << "Invalid Patient Record";
            }
        }
        return ostr;
    }

    istream &Patient::read(istream &istr)
    {
        char tempName[51] = {};
        int tempOHIP = 0;

        if (&istr == &std::cin)
        {
            std::cout << "Name: ";
            istr.get(tempName, 51);
            setName(tempName);
            istr.ignore(1000, '\n');

            std::cout << "OHIP: ";
            while (true)
            {
                if (!(istr >> tempOHIP))
                { // Check for extraction failure
                    std::cout << "Bad integer value, try again: ";
                    istr.clear();
                    istr.ignore(1000, '\n');
                }
                else if (tempOHIP < 100000000 || tempOHIP > 999999999)
                {
                    std::cout << "Invalid value entered, retry [100000000 <= value <= 999999999]: ";
                }
                else
                {
                    break;
                }
            }
            setOHIP(tempOHIP);
            istr.ignore(1000, '\n');
        }
        else
        {
            istr.get(tempName, 51, ',');
            setName(tempName);
            istr.ignore(1000, ',');

            istr >> tempOHIP;
            setOHIP(tempOHIP);
            istr.ignore(1000, ',');

            m_ticket.read(istr);
        }
        return istr;
    }

    std::ostream &operator<<(ostream &ostr, const Patient &p)
    {
        return p.write(ostr);
    }

    std::istream &operator>>(istream &istr, Patient &p)
    {
        return p.read(istr);
    }

};
