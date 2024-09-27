#ifndef iq
#define iq
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

struct IQsamples{
    signed int i;
    signed int q;
}iqs;


std::vector<IQsamples> readiq(const std::string& filename, IQsamples& iqs) {
    std::ifstream inputFile(filename);
    std::string line;
    std::vector<IQsamples> myVector;
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return myVector;
        
    }
    while (getline(inputFile, line)) {
        IQsamples structing;
        size_t pos = line.find(' ');
        size_t endline=line.find('\n');
        std::string value_i= line.substr(0,pos);
        std::string value_q=line.substr(pos+1,endline-(pos+1));
        structing.i=stoi(value_i);
        structing.q=stoi(value_q);
        myVector.push_back(structing);



    }
    inputFile.close();
    return myVector;
}

/*int main(){
    IQsamples iqq;
    readiq("iq_file.txt",iqq);
}*/
#endif