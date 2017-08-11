/**
 * \file noisytransmit.cpp
 * \author Fill me in!
 *
 * \brief Defines the noisyTransmit() function for stepping through a 
 * chunkystring and randomly doubling, erasing, or leaving each character
 * unchanged.
 *
 * \details
 *
 * \remarks
 *
 */

#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "chunkystring.hpp"
#include "noisy-transmission.hpp"


NoisyTransmission::NoisyTransmission(float errorRate) : errorRate_(errorRate), 
  dis_(0,1) {
    seed();
}

void NoisyTransmission::seed() {
    std::random_device rd;
    gen_.seed(rd());
}

float NoisyTransmission::getRandomFloat() {
    return dis_(gen_);
}


void NoisyTransmission::transmit(ChunkyString::ChunkyString& message) {
    if (errorRate_ > 0.5) {
        std::cerr << "The error rate must be >= to 0.5" << std::endl;
        exit(2);
    } else {
        std::cout << message <<std::endl;

        // Loop through all characters in the message
        for(auto iter = message.begin(); iter != message.end();) {
            
            float randFloat = getRandomFloat();
            
            // errorRate_ % of the time a character should be duplicated
            if (0.0 < randFloat && randFloat <= errorRate_) {
                char toDuplicate = *iter;
                iter = message.insert(iter, toDuplicate);
                advance(iter, 2);
            } else if (errorRate_ < randFloat && randFloat < (2 * errorRate_)) {
                // errorRate_ % of the time a character should be removed
                iter = message.erase(iter);

            } else {
                // Every other time we do nothing
                ++iter;
            }
            
        }
    }

}
