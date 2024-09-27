#ifndef RF
#define RF

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;


// Define a struct to hold Ethernet configuration parameters
 struct Config {
    static unsigned int LineRate;
    static double CaptureSizeMs;
    static unsigned int MinNumOfIFGsPerPacket;
    static uint64_t DestAddress;
    static uint64_t SourceAddress;
    static unsigned int MaxPacketSize;
    static unsigned int SCS;
    static unsigned int MaxNRB;
    static unsigned int NRBPerpacket;
    static string PayloadType;
    static string Payload;
}Configuration;

     unsigned int Config::LineRate;
     double Config::CaptureSizeMs;
     unsigned int Config::MinNumOfIFGsPerPacket;
     uint64_t Config::DestAddress;
     uint64_t Config::SourceAddress;
     unsigned int Config::MaxPacketSize;
     unsigned int Config::SCS;
     unsigned int Config::MaxNRB;
     unsigned int Config::NRBPerpacket;
     string Config::PayloadType;
     string Config::Payload;

    

// Function to read Ethernet configuration from a file
  bool readConfig(const std::string& filename, Config& Configuration) {
    std::ifstream inputFile(filename);
    std::string line;
    std::vector<std::string> myVector;
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << filename << std::endl;
        return false;
    }
    while (getline(inputFile, line)) {
        std::cout << line << std::endl;
        size_t pos = line.find('=');
        size_t second_space = line.find(pos + 2,' ');
        

            if (pos != std::string::npos) {
                std::string value = line.substr(pos + 2,second_space-(pos + 2));
                //std::cout <<"value"<< value << std::endl;
                myVector.push_back(value);
            }
            
    }

    Configuration.LineRate=stoi(myVector[0]);
    Configuration.CaptureSizeMs=stoi(myVector[1]);
    Configuration.MinNumOfIFGsPerPacket=stoi(myVector[2]);
    Configuration.DestAddress=stoull((myVector[3]).erase(0,2));
    Configuration.SourceAddress=stoull(myVector[4].erase(0,2));
    Configuration.MaxPacketSize=stoi(myVector[5]);
    Configuration.SCS=stoi(myVector[6]);
    Configuration.MaxNRB=stoi(myVector[7]);
    Configuration.NRBPerpacket=stoi(myVector[8]);
    Configuration.PayloadType=myVector[9];
    Configuration.Payload=myVector[10];


  

    // Close the file
    inputFile.close();
    return true;
}
#endif

/*int main() {
    
    Config Configuration;

    
    readConfig("second_milstone.txt", Configuration);
        
    




    return 0;
}*/

