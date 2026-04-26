/**
 * @file core_logic.cpp
 * @author Kiril Zolotarov (kz000012@red.ujaen.es)
 * @author Roberto Menegassi (ramf0001@red.ujaen.es)
 * @brief Implements the main wizarding school simulation logic and menu-driven
 * user interaction.
 * @version 0.1
 * @date 2026-03-09
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "core_logic.h"
#include "Spell.h"
#include "WizardStudent.h"
#include "Professor.h"
#include <iostream>
#include <memory>

// This function attempts to read a value from standard input.
template <typename T>
bool safe_read(T &value)
{
    if (std::cin >> value)
        return true; // Successfully reading

    // Check if EOF was reached
    if (std::cin.eof())
        return false; // EOF reached, we can exit the program

    // If we get here, it means input error (e.g., non-numeric input)
    std::cin.clear();             // Clear the error state
    std::cin.ignore(10000, '\n'); // Ignore the rest to prevent infinite loop

    return true; // Return true to continue the program
}

void displayMenu()
{
    std::cout << "\n=== Wizarding School Menu ===\n";
    std::cout << "1. Create new student\n";
    std::cout << "2. Teach new spell\n";
    std::cout << "3. Practice spells\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void handleCreateStudent(
    Professor &professor,
    std::vector<std::shared_ptr<WizardStudent>> &allStudents)
{
    std::string name;
    std::string house;

    std::cout << "Enter student name: ";
    if (!safe_read(name))
        return;

    std::cout << "Enter house name: ";
    if (!safe_read(house))
        return;

    auto student = std::make_shared<WizardStudent>(name, house, 1);
    allStudents.push_back(student);
    professor.addStudent(student);
}

void handleTeachSpell(
    Professor &professor,
    const std::vector<std::shared_ptr<WizardStudent>> &allStudents)
{
    if (allStudents.empty())
    {
        std::cout << "No students to teach!\n";
        return;
    }

    Spell spell("Wingardium Leviosa", "Levitation", 1);
    professor.teachSpell(spell);
}

void handlePracticeSpells(
    Professor &professor,
    const std::vector<std::shared_ptr<WizardStudent>> &allStudents)
{
    if (allStudents.empty())
    {
        std::cout << "No students to practice!\n";
        return;
    }

    for (auto &student : allStudents)
        student->practiceSpells();

    professor.evaluateStudents();
}

bool handleMenuChoice(
    int choice,
    Professor &professor,
    std::vector<std::shared_ptr<WizardStudent>> &allStudents)
{
    switch (choice)
    {
    case 1:
        handleCreateStudent(professor, allStudents);
        return true;
    case 2:
        handleTeachSpell(professor, allStudents);
        return true;
    case 3:
        handlePracticeSpells(professor, allStudents);
        return true;
    case 4:
        return false;
    default:
        std::cout << "Invalid option!\n";
        return true;
    }
}

void run_simulation()
{
    Professor mcgonagall("McGonagall", "Transfiguration");
    std::vector<std::shared_ptr<WizardStudent>> allStudents;

    int choice;
    while (true)
    {
        displayMenu();
        if (!safe_read(choice))
            break;
        if (!handleMenuChoice(choice, mcgonagall, allStudents))
            break;
    }
}