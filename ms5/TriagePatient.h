/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#ifndef TRIAGE_PATIENT_H
#define TRIAGE_PATIENT_H

#include <cstring>
#include "Patient.h"

namespace seneca
{

    class TriagePatient : public Patient
    {
    private:
        static int nextTriageTicket;
        char *m_symptoms;

    public:
        TriagePatient();
        ~TriagePatient();
        char type() const override;

        std::ostream &write(std::ostream &os) const override;
        std::istream &read(std::istream &is) override;

        // Rule of Three (for memory management)
        TriagePatient(const TriagePatient &other);            // Copy constructor
        TriagePatient &operator=(const TriagePatient &other); // Assignment Operator
    };

} // namespace seneca

#endif // TRIAGE_PATIENT_H
