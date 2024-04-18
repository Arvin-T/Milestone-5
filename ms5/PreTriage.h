
/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#ifndef PreTriage_h
#define PreTriage_h

#include <iostream>

#include "Patient.h"
#include "TriagePatient.h"
#include "TestPatient.h"
#include "Menu.h"
#include "Utils.h"
#include "IOAble.h"
#include "Ticket.h"

#define maxNum 100
namespace seneca
{
    class PreTriage
    {
        // Attributes
        Time waitTimeAvgContaigen;
        Time waitTimeAvgTriage;
        Patient *m_lineup[maxNum];
        char dataFileName[200];
        int lineSize = 0;

        // Methods
        int indexOfFirstInLine(char type) const;
        void load();
        void save() const;
        void setAverageWaitTime(Patient &p);
        Time getWaitTime(const Patient &p) const;
        void registerPatient();
        void admit();
        void lineup();

    public:
        PreTriage(const char *dataFilename);
        ~PreTriage();
        void run();
        int countPriorityPatients(char priorityType) const;
        Time getWaitTimeMultiplier(char priorityType) const;
        bool readAveragesFromFile(ifstream &file);
        bool loadPatientsFromFile(ifstream &file);
        Patient *createPatientFromType(char type);
        void saveAverageWaitTimes(std::ofstream &file) const;
        void savePatients(std::ofstream &file) const;
        int countPatientType(char type) const;
    };
}

#endif /* PreTriage_h */