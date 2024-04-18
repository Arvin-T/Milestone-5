/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#ifndef TEST_PATIENT_H
#define TEST_PATIENT_H

#include "Patient.h"

namespace seneca
{

    class TestPatient : public Patient
    {
    private:
        static int nextTestTicket;

    public:
        TestPatient();
        char type() const override;
        std::ostream &write(std::ostream &os) const override;
        std::istream &read(std::istream &is) override;

        // No explicit destructor needed for now
    };

} // namespace seneca

#endif // TEST_PATIENT_H
