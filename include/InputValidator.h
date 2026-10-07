#ifndef INPUT_VALIDATOR_H
#define INPUT_VALIDATOR_H

#include <string>
#include <vector>

class InputValidator {
public:
    // Read non-empty or validated string
    static std::string getString(const std::string& prompt, bool allowEmpty = false);
    
    // Read multi-line content terminated by a sentinel (e.g., "END")
    static std::string getMultilineContent(const std::string& prompt);

    // Read integer within [minVal, maxVal]
    static int getInt(const std::string& prompt, int minVal, int maxVal);

    // Read valid positive ID
    static int getId(const std::string& prompt);

    // Read Yes/No confirmation
    static bool getConfirmation(const std::string& prompt);

    // Category selection from available list or new custom category
    static std::string selectCategory(const std::vector<std::string>& existingCategories);

    // Visual feedback helpers
    static void printError(const std::string& message);
    static void printSuccess(const std::string& message);
    static void printInfo(const std::string& message);
    static void printWarning(const std::string& message);
};

#endif // INPUT_VALIDATOR_H
