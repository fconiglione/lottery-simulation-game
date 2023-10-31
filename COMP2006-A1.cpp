#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>


using namespace std;

const int NUM_OF_DRAW = 6;
const int MAX_NUMBER = 45;


bool promptUser(const string& promptString) {
    char userInput;

    do {
        cout << promptString << endl;
        cin >> userInput;
        userInput = tolower(userInput);

        if (userInput == 'y' || userInput == 'n') {
            return userInput == 'y';
        }
        cout << "Invalid input. Please type either 'y' for yes or 'n' for no." << endl;
    } while (true);
}
// this is a helper function that checks if the number does not already exist in an input vecotr
bool numberExists(const vector<int>& numbers, int num) {
    for (int existingNum : numbers) {
        if (existingNum == num) {
            return true;
        }
    }
    return false;
}
// this function continues to generate random numbers until the random number is unique, i.e not in the existing numbers
int generateUniqueRandomNumber(const vector<int>& existingNumbers) {
    int randomNumber;
    do {
        randomNumber = rand() % MAX_NUMBER + 1;
    } while (numberExists(existingNumbers, randomNumber));

    return randomNumber;
}
// this function uses the two helper functions above to generate unique num of draw numbers
vector<int> generateNumbers() {
    vector<int> numbers;
    for (int i = 0; i < NUM_OF_DRAW; i++) {
        numbers.push_back(generateUniqueRandomNumber(numbers));
    }
    return numbers;
}

// this function uses the numberExists helper function to check for unique numbers and checks for range
vector<int> getPlayerNumbers() {
    vector<int> numbers;

    for (int i = 0; i < NUM_OF_DRAW; ++i) {
        int num;
        do {
            cout << "Enter unique number " << i + 1 << " (between 1 and " << MAX_NUMBER << "): " << endl;

            if (!(cin >> num)) {  // If the input is not an integer
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the rest of the input
                cout << "Invalid input. Please enter a number." << endl;
                continue;  // Go to the next iteration of the loop without further checks
            }

            if (num >= 1 && num <= MAX_NUMBER && !numberExists(numbers, num)) {
                numbers.push_back(num);
                break; // Exit the loop as the number is valid
            }

            if (num < 1 || num > MAX_NUMBER) {
                cout << "Number out of range. ";
            }
            else {
                cout << "Number already entered. ";
            }

        } while (true);
    }

    return numbers;
}


// this function takes two integer vectors and compare them to see how many of those integers are matching

int countMatches(const vector<int>& a, const vector<int>& b) {
    int count = 0;
    for (int num : a) {
        if (numberExists(b, num)) {
            count++;
        }
    }
    return count;
}

void outputVectorNumbers(const vector<int>& a) {
    for (int num : a) {
        cout << num << " ";
    }
}


int main() {
    while (true) {
        // Initialize random number generator
        srand(time(0));

        // Variables
        vector<int> playerNumbers;
        vector<int> bonusNumbers;
        vector<int> winningNumbers;
        vector<int> computerNumbers;
        int randomNumber;
        int draw = 1;
        int winnings = 0;
        int numOfGames;
        int totalCost = 0;
        int totalWinnings = 0;
        const int ticketCost = 5;
        char response;

        // Display the program introduction and instructions
        cout << "Lottery Simulation - Lottario" << endl;
        cout << "Francesco Coniglione (1206780), Jaskarn Dhillon (1200409), Miran (1197590), Kalem Sdao (1185287)" << endl;
        bool understandRules = promptUser("Do you understand the rules & regulations (Y/N)? ");


        if (!understandRules) {
            cout << "Lottario Lottery Simulation: Rules & Regulations" << endl;
            cout << "-------------------------------------------------" << endl;

            cout << "1. Eligibility:" << endl;
            cout << "   - Players must be of legal age to participate." << endl << endl;

            cout << "2. Picking Numbers:" << endl;
            cout << "   - Each player must pick six (6) unique numbers from a set of 1 to 45. And they also get a set of 6 numbers (bonous numbers)" << endl;
            cout << "   - Players can choose to have the computer generate random numbers on their behalf." << endl << endl;

            cout << "3. Draw and Winning:" << endl;
            cout << "   - For each game, six (6) unique winning numbers  are drawn at random." << endl;
            cout << "   - Players win by matching their selected numbers or bonous numbers to the drawn numbers." << endl;
            cout << "   - Matching all six numbers results in a jackpot win." << endl << endl;

            cout << "4. Costs and Payments:" << endl;
            cout << "   - Each game costs 5 CAD to play." << endl;
            cout << "   - All winnings are virtual and for simulation purposes only. No real money or prizes are awarded." << endl << endl;

            cout << "5. Game Continuation:" << endl;
            cout << "   - After each game, players can choose to play again or exit the simulation." << endl << endl;


            cout << "Please ensure you understand the rules and regulations before participating in the Lottario Lottery Simulation." << endl;

            cout << "Please review the Official Lottario Lottery Rules and Regulations by visiting:" << endl;
            cout << "https://www.olg.ca/content/dam/olg/web/product/resources/documents/lottery-rules/olg-lottario-game-conditions-en.pdf" << endl;
        }


        bool wantToPlay = promptUser("Would you like to play? (y/n)");

        if (wantToPlay) {

            cout << "How many games would you like to play? ";

            cin >> numOfGames;

            totalCost = numOfGames * ticketCost;

            cout << "You are paying " << totalCost << " CAD to play " << numOfGames << " draws." << endl;
            cout << "Do you want me (the computer) to generate the random numbers, or would you like to pick them yourself? " << endl;
            cout << "(Enter 'Y' for generating the numbers or any other key to continue): " << endl;
            cin >> response;
            cout << endl;
            for (int i = 0; i < numOfGames; i++) {
                if (response == 'Y' || response == 'y') {
                    cout << "Draw: " << draw << endl;
                    // Generate random computer numbers
                    computerNumbers = generateNumbers();
                    cout << "The computer generated numbers are: ";
                    outputVectorNumbers(computerNumbers);
                }
                else {
                    cout << "Draw: " << draw << endl;
                    // Input player numbers
                    playerNumbers = getPlayerNumbers();
                    // Display player and bonus numbers
                    cout << "You have picked: ";
                    outputVectorNumbers(playerNumbers);
                }

                // Generate random bonus numbers
                bonusNumbers.clear(); // Clear the previous bonus numbers
                bonusNumbers = generateNumbers();

                // Generate random winning numbers
                winningNumbers.clear();
                winningNumbers = generateNumbers();
                cout << endl;

                cout << "Here are your bonus numbers: ";
                outputVectorNumbers(bonusNumbers);
                cout << endl;

                // Display winning numbers
                cout << "The winning numbers are: ";
                outputVectorNumbers(winningNumbers);
                cout << endl << endl;

                // Compare numbers
                int matchedNumbers = countMatches(playerNumbers, winningNumbers);
                int matchedBonusNumbers = countMatches(bonusNumbers, winningNumbers);


                // Calculate winnings
                if (matchedNumbers == 6 || matchedBonusNumbers == 6) {
                    winnings += 10; // Replace with the actual prize amount
                }

                computerNumbers.clear();
                winningNumbers.clear();
                draw++;

                if (matchedNumbers < 6 || matchedBonusNumbers < 6) {
                    if (matchedBonusNumbers > matchedNumbers) {
                        cout << "You matched: " << matchedBonusNumbers << " number(s) and you lost." << endl;
                    }
                    else {
                        cout << "You matched: " << matchedNumbers << " number(s) and you lost." << endl;
                    }
                }
                else {
                    cout << "You matched: " << 6 << " number(s) and, you won." << endl;
                }
                cout << endl;
            }

            totalWinnings = winnings - totalCost;

            if (totalWinnings < 0) {
                cout << "You spent $" << totalCost << " CAD and You Lost $" << abs(totalWinnings) << " CAD." << endl << endl;
            }
            else {
                cout << "You spent $" << totalCost << " CAD and You Won $" << abs(totalWinnings) << " CAD." << endl << endl;
            }
            cout << "Do you want to play again (Y/N)? ";

            cin >> response;

            if (response == 'N' || response == 'n') {

                cout << "Sorry to hear you wouldn't like to play, hope to see you again soon." << endl;
                break;

            }
        }

        else {
            cout << "Sorry to hear you wouldn't like to play, hope to see you again soon." << endl;
            break;
        }
    }

    return 0;
}