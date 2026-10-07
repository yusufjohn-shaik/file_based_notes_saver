#include "InputValidator.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <cstdlib>

std::string InputValidator::getString(const std::string& prompt, bool allowEmpty) {
    std::string input;
    while (true) {
        if (!prompt.empty()) {
            std::cout << prompt;
        }
        if (!std::getline(std::cin, input)) {
            if (std::cin.eof()) {
                std::cout << "\nExiting application.\n";
                std::exit(0);
            }
            std::cin.clear();
            return "";
        }
        std::string trimmed = Utils::trim(input);
        if (allowEmpty || !trimmed.empty()) {
            return trimmed;
        }
        printError("Input cannot be empty. Please enter a valid value.");
    }
}

std::string InputValidator::getMultilineContent(const std::string& prompt) {
    if (!prompt.empty()) {
        std::cout << prompt << "\n";
    }
    std::cout << Utils::Colors::DIM << "(Tip: Type your text. Enter 'END' on a single line when finished)" 
              << Utils::Colors::RESET << "\n";

    std::string result;
    std::string line;
    bool first = true;

    while (std::getline(std::cin, line)) {
        if (Utils::toLower(Utils::trim(line)) == "end") {
            break;
        }
        if (!first) {
            result += "\n";
        }
        result += line;
        first = false;
    }

    if (std::cin.eof() && result.empty()) {
        std::cout << "\nExiting application.\n";
        std::exit(0);
    }

    if (Utils::trim(result).empty()) {
        printWarning("Note content was left empty.");
    }
    return result;
}

int InputValidator::getInt(const std::string& prompt, int minVal, int maxVal) {
    std::string input;
    while (true) {
        if (!prompt.empty()) {
            std::cout << prompt;
        }
        if (!std::getline(std::cin, input)) {
            if (std::cin.eof()) {
                std::cout << "\nExiting application.\n";
                std::exit(0);
            }
            std::cin.clear();
            return minVal;
        }

        std::string trimmed = Utils::trim(input);
        if (trimmed.empty()) {
            printError("Input cannot be empty. Please enter a number.");
            continue;
        }

        try {
            size_t idx = 0;
            int value = std::stoi(trimmed, &idx);
            if (idx == trimmed.length()) {
                if (value >= minVal && value <= maxVal) {
                    return value;
                } else {
                    printError("Invalid choice! Please enter a number between " +
                               std::to_string(minVal) + " and " + std::to_string(maxVal) + ".");
                    continue;
                }
            } else {
                printError("Invalid input! Please enter an integer number.");
            }
        } catch (...) {
            printError("Invalid input! Please enter a valid numeric value.");
        }
    }
}

int InputValidator::getId(const std::string& prompt) {
    return getInt(prompt, 1, 2000000000);
}

bool InputValidator::getConfirmation(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        if (!std::getline(std::cin, input)) {
            if (std::cin.eof()) {
                std::cout << "\nExiting application.\n";
                std::exit(0);
            }
            std::cin.clear();
            return false;
        }
        std::string lower = Utils::toLower(Utils::trim(input));
        if (lower == "y" || lower == "yes") {
            return true;
        }
        if (lower == "n" || lower == "no") {
            return false;
        }
        printError("Invalid confirmation input! Please enter [Y/N].");
    }
}

std::string InputValidator::selectCategory(const std::vector<std::string>& existingCategories) {
    std::cout << "\n" << Utils::Colors::BOLD << "Categories:" << Utils::Colors::RESET << "\n";
    int index = 1;
    for (const auto& cat : existingCategories) {
        std::cout << "  " << index++ << ". " << cat << "\n";
    }
    std::cout << "  " << index << ". [Enter Custom Category]\n";

    int choice = getInt("\nSelect Category (1-" + std::to_string(index) + "): ", 1, index);
    if (choice >= 1 && choice < index) {
        return existingCategories[choice - 1];
    } else {
        return getString("Enter New Category Name: ");
    }
}

void InputValidator::printError(const std::string& message) {
    std::cout << Utils::Colors::BOLD << Utils::Colors::RED << "Error: " 
              << Utils::Colors::RESET << Utils::Colors::RED << message 
              << Utils::Colors::RESET << "\n";
}

void InputValidator::printSuccess(const std::string& message) {
    std::cout << Utils::Colors::BOLD << Utils::Colors::GREEN << "Success: " 
              << Utils::Colors::RESET << Utils::Colors::GREEN << message 
              << Utils::Colors::RESET << "\n";
}

void InputValidator::printInfo(const std::string& message) {
    std::cout << Utils::Colors::BOLD << Utils::Colors::CYAN << "Info: " 
              << Utils::Colors::RESET << Utils::Colors::CYAN << message 
              << Utils::Colors::RESET << "\n";
}

void InputValidator::printWarning(const std::string& message) {
    std::cout << Utils::Colors::BOLD << Utils::Colors::YELLOW << "Warning: " 
              << Utils::Colors::RESET << Utils::Colors::YELLOW << message 
              << Utils::Colors::RESET << "\n";
}
