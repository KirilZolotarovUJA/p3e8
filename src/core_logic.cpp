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

/**
 * @brief Safely reads a value from standard input, handling errors and EOF.
 *
 * @tparam T The type of the value to read.
 * @param value Reference to the variable where the read value will be stored.
 * @return true  If the read succeeded or if a recoverable input error occurred.
 * @return false If EOF was reached, indicating the program should terminate.
 */
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

/**
 * @brief Prompts the user for student details and enrolls a new student.
 *
 * @param professor   The professor who will supervise the new student.
 * @param allStudents The shared list to which the new student is appended.
 */
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

/**
 * @brief Instructs the professor to teach a predefined spell to their students.
 *
 * @param professor   The professor who will teach the spell.
 * @param allStudents Read-only list used to verify that students exist before
 *                    attempting to teach.
 */
void handleTeachSpell(
    const Professor &professor,
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

/**
 * @brief Makes every enrolled student practice their spells and triggers
 *        professor evaluation.
 *
 * @param professor   The professor who evaluates the students after practice.
 * @param allStudents Read-only list of students who will practice their spells.
 */
void handlePracticeSpells(
    const Professor &professor,
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

/**
 * @brief Dispatches a menu choice to the corresponding handler function.
 *
 * @param choice      The menu option entered by the user.
 * @param professor   The professor passed through to the relevant handler.
 * @param allStudents The student list passed through to the relevant handler.
 * @return true  If the simulation loop should continue (choices 1–3 and any
 *               invalid input).
 * @return false If the user chose to exit (choice 4).
 */
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
        if (!safe_read(choice) || !handleMenuChoice(choice, mcgonagall, allStudents))
            break;
    }
}