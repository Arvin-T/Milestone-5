#define _CRT_SECURE_NO_WARNINGS
/***********************************************************************
Milestone 5
Name:         Seyedarvin Tabatabaei Ferezghi
Seneca email: stabatabaei-ferezghi@myseneca.ca
Student ID:   122267230
Date:         APL 17 2024
***********************************************************************/
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstring>
#include <string>

#include "Time.h"
#include "Utils.h"
#include "Menu.h"

using namespace std;

namespace seneca
{

  void Menu::display() const
  {
    const char *temp_var = m_text;
    for (int tab_index = 0; tab_index < m_numTabs; tab_index++)
    {
      cout << "   ";
    }
    while (*temp_var != '\0')
    {
      while (*temp_var != '\n' && *temp_var != '\0')
      {
        cout << *temp_var;
        temp_var++;
      }
      if (*temp_var == '\n')
      {
        cout << endl;
        for (int tab_index = 0; tab_index < m_numTabs; tab_index++)
        {
          cout << "   ";
        }
        temp_var++;
      }
    }
    cout << '\n';
    for (int tab_index = 0; tab_index < m_numTabs; tab_index++)
    {
      cout << "   ";
    }
    cout << "0- Exit" << '\n';
    for (int tab_index = 0; tab_index < m_numTabs; tab_index++)
    {
      cout << "   ";
    }
    cout << "> ";
  }

  int &Menu::operator>>(int &Selection)
  {
    string input_size;
    int user_input;
    int flag_var = 0;
    display();
    do
    {
      getline(cin, input_size, '\n');
      cin.sync();

      if (!isdigit(input_size[0]) && !isdigit(input_size[1]))
      {
        cin.sync();
        cout << "Bad integer value, try again: ";
      }
      else if (input_size[1] == ' ')
      {
        cout << "Only enter an integer, try again: ";
      }
      else
      {
        user_input = stoi(input_size);
        if (user_input < 0 || user_input > m_numOptions)
        {
          cout << "Invalid value entered, retry[0 <= value <= " << m_numOptions << "]: ";
        }
        else
        {
          flag_var = 1;
          Selection = user_input;
        }
      }

    } while (flag_var == 0);
    return Selection;
  }

  Menu::Menu(const char *menu_content, int num_tabs)
  {
    m_numTabs = num_tabs;
    m_text = new char[strlen(menu_content) + 1];
    strcpy(const_cast<char *>(m_text), menu_content);
    m_numOptions = 0;
    for (size_t i = 0; i < strlen(m_text) && m_text[i] != '\0'; i++)
    {
      if (m_text[i] == '\n')
      {
        m_numOptions++;
      }
    }
  }

  Menu::~Menu()
  {
    delete[] m_text;
    m_text = nullptr;
  }

}
