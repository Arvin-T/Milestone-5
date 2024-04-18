/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#include "TestPatient.h"

namespace seneca
{

    int TestPatient::nextTestTicket = 1;

    TestPatient::TestPatient() : Patient(nextTestTicket++)
    {
    }

    char TestPatient::type() const
    {
        return 'C';
    }

    std::ostream &TestPatient::write(std::ostream &os) const
    {
        if (&os == &std::cout)
        {
            os << "Contagion TEST\n";
        }
        return Patient::write(os); // Call base class implementation
    }

    std::istream &TestPatient::read(std::istream &is)
    {
        Patient::read(is);
        if (&is != &std::cin)
        {
            nextTestTicket = number() + 1; // Update for file reads
        }
        return is;
    }

} // namespace seneca
