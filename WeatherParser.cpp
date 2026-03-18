#include <iostream>  // For standard input/output operations
#include <string>    // For std::string class
#include <map>       // For std::map (key-value pairs)
#include <vector>    // For std::vector (dynamic arrays)
#include <algorithm> // For algorithm utilities

// Class that monitors and processes weather alert signals
class WeatherSentinel {
private:
    // Replace "022105" with your actual Parish FIPS code (e.g., 022105 is Tangipahoa)
    std::string homeFipsCode = "022105"; 

    // Map of weather event codes to their alert level descriptions
    std::map<std::string, std::string> alertLevels = {
        {"TOR", "TORNADO WARNING - RED ALERT"},           // Tornado warning code and message
        {"SVR", "SEVERE THUNDERSTORM - YELLOW ALERT"},    // Severe storm code and message
        {"FFW", "FLASH FLOOD - YELLOW ALERT"}             // Flash flood code and message
    };

public:
    // Method to process an incoming weather alert signal
    void processSignal(std::string rawSignal) {
        // SAME Format: [Preamble]-[Originator]-[Event]-[Location]-[Duration]-[Time]-[ID]
        // Example: ZCZC-WXR-TOR-022105+0015...
        
        // Extract the 3-character event code starting at position 9
        std::string eventCode = rawSignal.substr(9, 3);
        // Extract the 6-character FIPS location code starting at position 13
        std::string signalFips = rawSignal.substr(13, 6);

        // Display which location the incoming alert is for
        std::cout << "Incoming Signal for Location: " << signalFips << std::endl;

        // 1. Check if the alert is for OUR location
        // 000000 means the alert applies to all areas
        if (signalFips == homeFipsCode || signalFips == "000000") { 
            
            // 2. Check if it's an event we care about (exists in alertLevels map)
            if (alertLevels.count(eventCode)) {
                // If the event code matches, print the alert message
                std::cout << "!!! ALERT FOR YOUR AREA: " << alertLevels[eventCode] << " !!!" << std::endl;
            } else {
                // Event detected locally but not in our priority list
                std::cout << "Local event detected (" << eventCode << "), but not in priority list." << std::endl;
            }

        } else {
            // Alert is for a different parish, so ignore it
            std::cout << "Alert ignored. Not for home Parish (" << homeFipsCode << ")." << std::endl;
        }
    }
};

// Main program entry point
int main() {
    // Create an instance of the WeatherSentinel system
    WeatherSentinel sentinel;

    // Display system status message
    std::cout << "--- Sentinel System Active (Louisiana Parish Filter On) ---" << std::endl;

    // Test 1: An alert for a DIFFERENT parish (should be ignored)
    std::string otherParish = "ZCZC-WXR-TOR-022017"; 
    sentinel.processSignal(otherParish);

    // Test 2: An alert for YOUR parish (should trigger alert message)
    std::string homeParish = "ZCZC-WXR-TOR-022105"; 
    sentinel.processSignal(homeParish);

    // Exit the program successfully
    return 0;
}