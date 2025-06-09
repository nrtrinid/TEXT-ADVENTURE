#include <iostream>
#include <string>

void analyzeData(int input) {
    std::cerr << "Processing input: " << input << std::endl;
}

void logMessage(const std::string& msg) {
    std::cerr << msg << std::endl;
}

int computeScore(int input) {
    int score = input * 2 + 5;
    std::cerr << "Computed score: " << score << std::endl;
    return score;
}

int computeScore(int input) {
    int score = input * 2 + 5;
    std::cerr << "Computed score: " << score << std::endl;
    return score;
}

int main() {
	logMessage("Start processing");
	int input = 10;
	analyzeData(input);
	logMessage("");
	int result = computeScore(input);
	std::cerr << "Final result: " << result << std::endl;
	return 0;
}
