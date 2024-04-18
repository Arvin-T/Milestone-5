/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#include "TriagePatient.h"
#include <iostream>

namespace seneca
{

    int TriagePatient::nextTriageTicket = 1;

    TriagePatient::TriagePatient() : Patient(nextTriageTicket++), m_symptoms(nullptr)
    {
    }

    TriagePatient::~TriagePatient()
    {
        delete[] m_symptoms;
        m_symptoms = nullptr;
    }

    char TriagePatient::type() const
    {
        return 'T';
    }

    std::ostream &TriagePatient::write(std::ostream &os) const
    {
        if (&os == &std::cout)
        {
            os << "TRIAGE\n";
        }
        Patient::write(os);

        if (&os == &std::cout && m_symptoms)
        {
            os << "Symptoms: " << m_symptoms << std::endl;
        }
        else if (&os != &std::clog && m_symptoms)
        {
            os << "," << m_symptoms;
        }
        return os;
    }

    std::istream &TriagePatient::read(std::istream &is)
    {
        delete[] m_symptoms;
        m_symptoms = nullptr;

        Patient::read(is);
        if (&is != &std::cin)
        {
            is.ignore(); // Ignore comma
        }
        else
        {
            std::cout << "Symptoms: ";
        }

        char tempSymptoms[512];
        is.getline(tempSymptoms, 512, '\n');

        if (is)
        { // If read was successful...
            m_symptoms = new char[std::strlen(tempSymptoms) + 1];
            std::strcpy(m_symptoms, tempSymptoms);

            if (&is != &std::cin)
            {
                nextTriageTicket = number() + 1;
            }
        }
        else
        { // Reading failed, reset
            delete[] m_symptoms;
            m_symptoms = nullptr;
        }

        return is;
    }

} // namespace seneca
