/**
 * \file message-passer.cpp
 * \author Fill me in!
 *
 *
 * \remarks
 *
 */

#include <iostream>
#include <fstream>
#include <random>
#include "chunkystring.hpp"
#include "noisy-transmission.hpp"

using namespace std;




/**
 * \brief Option Processing
 * \details
 *   Sets various configuration variables by modifying variables passed
 *   by reference.
 *
 *   Will return with an exit error of 2 if receives a usage problem.
 *
 * \param options       Input of options from command line.
 * \param seed          Optional seed value for random number generator
 * \param filename      Name of file to read original message from
 * \param noiseLevel    Likelihood of a character being modified
 */
void processOptions(std::list<std::string> options,
		    string& filename,
                    float& noiseLevel)
{

    // Loop through the options. If they start with a dash
    // try to interpret them as a flag; if not, assume it's
    // the number of insertions.
    string flag;
    string value;

    while (!options.empty()) {
        
        // Store the flag and remove it from the options list
        flag = options.front();
        options.pop_front();

        // If there is no argument following the option throw
        // an error
        if (options.empty()) {
            std::cerr << "Empty argument" << std::endl;
            exit(2);
        };

        // Store the flag and remove it from the options list
	    value = options.front();
	    options.pop_front();

        
	    if (flag == "-n" || flag == "--noise") {
            // If the flag is for noise asign the 
            // noise level to the argument passed to the flag
	        noiseLevel = stod(value);
        } else if (flag == "-f" || flag == "--filename") {  
            // make the name of file that we read the message from
            // be the argument passed to the -f option
            filename = value;
        } else {
            // Otherwise we were passed (an) invalid flag(s)
            // so throw an error
            cerr << "Unrecognized option: " << flag << std::endl;
            cerr << "Usage: ./messagePasser -n noise -f filename" << endl;
            exit(2);
        }
    }

    return;
}



int main(int argc, const char* argv[])
{
    float noiseLevel = 0;
    string fileName;

    // Read in the options from the command line 
    std::list<std::string> options(argv + 1, argv + argc);
    processOptions(options, fileName, noiseLevel);

    // Set up a in-filestream object to read from the filename
    // passed to the command line
    ifstream fileReader( fileName );

    if ( !fileReader.is_open() ) {
        // The file could not be opened
        cerr << "Unable to read from file" << fileName << endl;
        exit(-1);
    }
    else {
        // Safely use the file stream
        string messageLine; 
        ChunkyString::ChunkyString message;

	// Read in each line from the file into messageLine
    // convert messageLine into a string and add that line 
    // to the whole message
    while (getline(fileReader, messageLine)) {
        string messagePlusNewL = messageLine +"\n";
        ChunkyString::ChunkyString messageLineChunky{messagePlusNewL};
  	    message += messageLineChunky;
	}

    // Create the noisy message and print it
	NoisyTransmission::NoisyTransmission transmissionLine{noiseLevel};
	transmissionLine.transmit(message);

        cout << message << endl;
        return 0;
    }


}
