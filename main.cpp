#include <iostream>
#include <string>
#include <vector>
#include <random>

std::string playerName;

struct traveler {
    std::string name;
};

struct travelparty {
    std::vector<traveler> members; // Vector to store party members
    // integers for Party resources
    int health = 100;
    int food = 100;
    int happiness = 100;
    int ammunition = 100;
    int oxen = 3;
};

class oregontrail {
private:
    
    std::random_device rd; // Random device for seeding
    std::mt19937 gen; // Mersenne Twister random number generator

public:
travelparty party;
    oregontrail() : gen(rd()) {} // Initialize random number generator with seed from random device


    void startGame() {
        std::cout << "Hello! Welcome to The Oregon Trail!\n";
        std::cout << "What is your name?\n";
        std::cin >> playerName;
        std::cout << "Hi " << playerName << "! Thanks for playing!\n";
      std::cout << "Your fellow travelers are named John, Lilian, Marie, and Jack.\n";
      std::cout << "You have a set amount of food, health, ammunition, oxen, and morale. You will have to make decisions for your travel party to survive the Oregon Trail, and each decision comes with different consequences for your resources. \n" << "Good Luck " << playerName << "!\n";
        // Add the player to the party
        traveler player;
        player.name = playerName;
        party.members.push_back(player);

        // Add other party members
        addMember("Jack");
        addMember("Marie");
        addMember("Lilian");
        addMember("John");
    }

    void addMember(const std::string& name) {
        traveler newMember;
        newMember.name = name;
        party.members.push_back(newMember);
    }

    void travel() {
        // Simulate traveling along the trail
        std::cout << "Traveling along the trail...\n";

        // Deduct resources for traveling
        std::uniform_int_distribution<int> foodDist(3, 7); // Random distribution for food deduction
        party.food -= foodDist(gen); // Deduct random units of food

        // Check if the party has enough resources to continue traveling
        if (party.food <= 0 || party.oxen <= 0) {
            std::cout << "Your party doesn't have enough resources to continue traveling.\n";
        }

        
        party.happiness += 5; // Increment happiness
        party.health -= 5; // Decrement health due to exhaustion

        // Display feedback to the player
        std::cout << "Happiness increased because of progress on the path.\n";
        std::cout << "Health decreased due to exhaustion.\n";
    }

    void addTravelerToParty(const traveler& newTraveler) {
        party.members.push_back(newTraveler);
    }
};

void event(oregontrail& game) {
    // Choose a random number to decide the event
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> eventDist(1, 6); // Random distribution for event selection
    int eventNumber = eventDist(gen); // Generate random event number

    // Perform the selected event
    switch (eventNumber) {
        case 1:
            // Event 1: River crossing
            std::cout << "You come across a river. Do you ford it or try to build a bridge?\n";
            int riverChoice;
            std::cout << "1. Ford the river\n";
            std::cout << "2. Try to build a bridge\n";
            std::cin >> riverChoice;
            if (riverChoice == 1) {
                // Ford the river (option 1)
                std::cout << "You decide to ford the river.\n" << "One of your party members gets hypothermia.\n";
               game.party.health -= 10;
              
            } else if (riverChoice == 2) {
                // Try to build a bridge (option 2)
                std::cout << "You decide to try to build a bridge.\n" << "This has worked, but spending the time there has cost your party some food.\n";
                game.party.food -= 10;
              
            } else {
                std::cout << "Invalid choice.\n";
            }
            break;
        case 2:
            // Event 2: Wolf attack
            std::cout << "The party is attacked by wolves. Do you fight them off or try to escape?\n";
            int wolfChoice;
            std::cout << "1. Fight off the wolves\n";
            std::cout << "2. Try to escape\n";
            std::cin >> wolfChoice;
            if (wolfChoice == 1) {
                // Fight off the wolves (option 1)
                std::cout << "You decide to fight off the wolves.\n" << "Your party was successful in fighting the wolves, but you lost some ammunition.\n";
              game.party.ammunition -= 20;
                
            } else if (wolfChoice == 2) {
                // Try to escape (option 2)
                std::cout << "You decide to try to escape.\n" << "Your party manages to escape, but the wolves killed one of your oxen.\n";
              game.party.oxen -= 1;  
            } else {
                std::cout << "Invalid choice.\n";
            }
            break;
        case 3:
            // Event 3: Infected leg
            std::cout << "A member of your travel party gets an infected leg. Do you saw it off or ration more food for them to fight the infection?\n";
            int legChoice;
            std::cout << "1. Saw off the leg\n";
            std::cout << "2. Ration more food\n";
            std::cin >> legChoice;
            if (legChoice == 1) {
                // Saw off the leg (option 1)
                std::cout << "You decide to saw off the leg.\n" << "Your party's morale is greatly decreased.\n";
              game.party.happiness -= 30;
                
            } else if (legChoice == 2) {
                // Ration more food (option 2)
                std::cout << "You decide to ration more food.\n" << "Your party member successfully fights the infection, but you lost some food.\n";
              game.party.food -=10;
                
            } else {
                std::cout << "Invalid choice.\n";
            }
            break;
        case 4:
            // Event 4: Trading post
            std::cout << "You come across a trading post. Do you buy a guitar or a fishing rod?\n";
            int tradingChoice;
            std::cout << "1. Buy a guitar\n";
            std::cout << "2. Buy a fishing rod\n";
            std::cin >> tradingChoice;
            if (tradingChoice == 1) {
                // Buy a guitar (option 1)
                std::cout << "You decide to buy a guitar.\n" << "Your party's morale has increased!\n";
              game.party.happiness += 10;
                
            } else if (tradingChoice == 2) {
                // Buy a fishing rod (option 2)
                std::cout << "You decide to buy a fishing rod.\n" << "Your party's food has increased!\n";
               game.party.food += 10;
            } else {
                std::cout << "Invalid choice.\n";
            }
            break;
        case 5:
            // Event 5: Dirty water
            std::cout << "One member of your travel party tries some stagnant water.\n";
            // One member dies (no decision)
            if (!game.party.members.empty()) {
                // Randomly select a member to die
                std::uniform_int_distribution<int> memberDist(0, game.party.members.size() - 1);
                int randomIndex = memberDist(gen);
                std::cout << game.party.members[randomIndex].name << " has died from drinking dirty water.\n";
                // Remove the deceased member from the party
                game.party.members.erase(game.party.members.begin() + randomIndex);
                // Decrement health
                game.party.health -= 15;
            }
            break;
        case 6:
            // Event 6: Finding gold
            std::cout << "The members of your party find gold.\n";
            // Improve morale greatly(no desicion)
            game.party.happiness += 15;
            break;
        default:
            // default case (shouldn't be chosen)
            std::cout << "Unexpected event occurred.\n";
            break;
    }
}

int main() {
    oregontrail game;
    game.startGame();
//game logic for tracking progress
    int eventsCount = 0; // number of events
    const int maxEvents = 10; // Maximum number of events before winning the game

    while (eventsCount < maxEvents) {
        game.travel(); // Perform travel
        event(game);
        // Increment the events counter
        eventsCount++;

        // Check if the party has run out of critical resources
        if (game.party.health <= 0 || game.party.food <= 0 || game.party.ammunition <= 0 || game.party.happiness <= 0 || game.party.oxen <= 0) {
            std::cout << "Your party has run out of critical resources and died.\n";
            return 0; // Exit the program
        }
        // Check win condition
        if (eventsCount >= maxEvents) {
            std::cout << "Congratulations " << playerName << "! Your party successfully travelled the Oregon Trail!\n";
            break; // Exit loop
        }
    }
    return 0; // Exit the program
}

