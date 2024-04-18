/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#include "PreTriage.h"

#include <fstream>
#include <iomanip>
#include <stdio.h>

#define MAX_PATIENT_NUM 100
namespace seneca
{
    PreTriage::PreTriage(const char *fileName)
    {
        waitTimeAvgTriage = 5;
        waitTimeAvgContaigen = 15;
        strcpy(dataFileName, fileName);
        load();
    }
    PreTriage::~PreTriage()
    {
        save();
        for (int i = 0; i < lineSize; i++)
        {
            delete m_lineup[i];
        }
    }
    int PreTriage::indexOfFirstInLine(char type) const
    {
        for (int i = 0; i < lineSize; i++)
        {
            if (m_lineup[i]->type() == type)
            {
                return i;
            }
        }
        return -1;
    }
    Time PreTriage::getWaitTime(const Patient &p) const
    {
        int priorityPatientCount = countPriorityPatients(p.type());

        Time waitTimeMultiplier = getWaitTimeMultiplier(p.type());
        Time estimatedWait = waitTimeMultiplier * priorityPatientCount;

        estimatedWait.m_minutes -= 35;

        return estimatedWait;
    }

    int PreTriage::countPriorityPatients(char priorityType) const
    {
        int count = 0;
        for (int i = 0; i < lineSize; i++)
        {
            if (m_lineup[i]->type() == priorityType)
            {
                count++;
            }
        }
        return count;
    }

    Time PreTriage::getWaitTimeMultiplier(char priorityType) const
    {
        return (priorityType == 'C') ? waitTimeAvgContaigen : waitTimeAvgTriage;
    }

    void PreTriage::setAverageWaitTime(Patient &patient)
    {
        Time currentTime = U.getTime();
        Time &avgWaitTime = (patient.type() == 'C') ? waitTimeAvgContaigen : waitTimeAvgTriage;

        Time waitDuration = currentTime - patient.time();
        avgWaitTime = (waitDuration + (avgWaitTime * (patient.number() - 1))) / patient.number();
    }

    void PreTriage::load()
    {
        ifstream file(dataFileName);
        if (!file.is_open())
        {
            cerr << "No data or bad data file!\n\n";
            return;
        }

        if (!readAveragesFromFile(file))
        {
            return;
        }

        if (!loadPatientsFromFile(file))
        {
            cout << "No data or bad data file!\n\n";
            return;
        }

        cout << lineSize << " Records imported..." << endl
             << endl;
    }

    bool PreTriage::readAveragesFromFile(ifstream &file)
    {
        if (!(file >> waitTimeAvgContaigen))
            return false;
        file.ignore();

        if (!(file >> waitTimeAvgTriage))
            return false;
        file.ignore();

        return true;
    }

    bool PreTriage::loadPatientsFromFile(ifstream &file)
    {
        char type;
        while (lineSize < MAX_PATIENT_NUM && file >> type)
        {
            file.ignore();

            Patient *patient = createPatientFromType(type);
            if (!patient)
            {
                cerr << "Invalid patient type encountered!\n";
                continue;
            }

            if (!patient->read(file))
            {
                delete patient;
                return false;
            }

            m_lineup[lineSize++] = patient;
        }

        if (lineSize == MAX_PATIENT_NUM && file.peek() != EOF)
        {
            cout << "Warning: number of records exceeded " << MAX_PATIENT_NUM << endl;
        }

        return lineSize > 0;
    }

    Patient *PreTriage::createPatientFromType(char type)
    {
        switch (type)
        {
        case 'C':
            return new TestPatient;
        case 'T':
            return new TriagePatient;
        default:
            return nullptr;
        }
    }

    void PreTriage::save() const
    {
        std::ofstream file(dataFileName);
        std::cout << "Saving lineup...\n";

        if (!file.is_open())
        {
            std::cerr << "Failed to open file for saving data!\n";
            return;
        }

        saveAverageWaitTimes(file);

        if (!file.good())
        {
            std::cerr << "Error saving average wait times!\n";
            return;
        }

        savePatients(file);

        std::cout << countPatientType('C') << " Contagion Tests and "
                  << countPatientType('T') << " Triage records were saved!\n";
    }
    void PreTriage::saveAverageWaitTimes(std::ofstream &file) const
    {
        file << waitTimeAvgContaigen << "," << waitTimeAvgTriage << std::endl;
    }

    void PreTriage::savePatients(std::ofstream &file) const
    {
        for (int i = 0; i < lineSize; ++i)
        {
            m_lineup[i]->write(file);
            file << '\n';
        }
    }

    int PreTriage::countPatientType(char type) const
    {
        int count = 0;
        for (int i = 0; i < lineSize; ++i)
        {
            if (m_lineup[i]->type() == type)
            {
                count++;
            }
        }
        return count;
    }

    void PreTriage::lineup()
    {
        Menu m("Select The Lineup:\n1- Contagion Test\n2- Triage", 1);
        int choice, counter = 1;
        m.display();
        cin >> choice;
        cout << "Row - Patient name                                          OHIP     Tk # Time\n";
        cout << "-------------------------------------------------------------------------------\n";

        auto printLineup = [&](char type)
        {
            for (int i = 0; i < lineSize; i++)
            {
                if (m_lineup[i]->type() == type)
                {
                    clog << left << setw(4) << setfill(' ') << counter++;
                    clog << "- ";
                    m_lineup[i]->write(clog);
                    cout << endl;
                }
            }
            if (lineSize == 0)
                clog << "Line up is empty!\n";
        };

        switch (choice)
        {
        case 0:
            break;
        case 1:
            printLineup('C');
            break;
        case 2:
            printLineup('T');
            break;
        }
        cout << "-------------------------------------------------------------------------------\n";
    }

    void PreTriage::registerPatient()
    {
        Menu m("Select Type of Registration:\n1- Contagion Test\n2- Triage", 1);
        int choice;
        if (lineSize < 100)
        {
            m.display();
            cin >> choice;
            cin.ignore(1000, '\n');

            auto registerPatientType = [&](char type)
            {
                if (type == 'C')
                {
                    m_lineup[lineSize] = static_cast<Patient *>(new TestPatient);
                }
                else if (type == 'T')
                {
                    m_lineup[lineSize] = static_cast<Patient *>(new TriagePatient);
                }
                cout << "Please enter patient information: " << endl;
                cin.clear();
                cin >> *m_lineup[lineSize];
                m_lineup[lineSize]->setArrivalTime();

                cout << "\n******************************************\n";
                cout << *m_lineup[lineSize];
                cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[lineSize]);
                cout << "\n******************************************\n\n";
                ++lineSize;
            };

            switch (choice)
            {
            case 0:
                break;
            case 1:
                registerPatientType('C');
                break;
            case 2:
                registerPatientType('T');
                break;
            }
        }
        else
        {
            cout << "Line up full!\n";
        }
    }

    void PreTriage::admit()
    {
        int choice, idx;
        Menu m("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 1);
        Time t = U.getTime();
        m.display();
        cin >> choice;
        cout << "\n******************************************\n";

        auto processAdmittance = [&](char type)
        {
            idx = indexOfFirstInLine(type);
            if (idx != -1)
            {
                cout << "Call time: [" << t << "]" << endl;
                cout << "Calling at for " << *m_lineup[idx];
                setAverageWaitTime(*m_lineup[idx]);
                removeDynamicElement(m_lineup, idx, lineSize);
            }
            else
            {
                cout << "Lineup is empty!\n";
            }
        };

        switch (choice)
        {
        case 0:
            break;
        case 1:
            processAdmittance('C');
            break;
        case 2:
            processAdmittance('T');
            break;
        }
        cout << "******************************************\n\n";
    }

    void PreTriage::run()
    {
        int choice;
        while (true)
        {
            Menu m("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup");
            m.display();
            cin >> choice;
            switch (choice)
            {
            case 0:
                return;
            case 1:
                registerPatient();
                break;
            case 2:
                admit();
                break;
            case 3:
                lineup();
                break;
            default:
                break;
            }
        }
    }

}
