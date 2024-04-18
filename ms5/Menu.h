/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <stdio.h>
#include <iostream>

using namespace std;
namespace seneca
{
    class Menu
    {
        const char *m_text;
        int m_numOptions;
        int m_numTabs;

    public:
        Menu(const char *menuContent, int numberOfTabs = 0);
        ~Menu();

        int &operator>>(int &Selection);
        void display() const;
        Menu(const Menu &) = delete;
        Menu &operator=(const Menu &) = delete;
    };
}
#endif
