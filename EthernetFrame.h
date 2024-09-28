#ifndef EF
#define EF
#include "ecpri.cpp"
#include "Read_file_Milestone_2.h"
#include <algorithm>
#include <cctype>

class EthernetFrame{
    private:
    // Member variables (frame components)
    uint64_t preamble;
    uint64_t destinationMac;
    uint64_t sourceMac;
    uint16_t etherType;
    vector<uint16_t> payload; 
    uint32_t crc;
    uint64_t IFG;
    ecpri* ecpripacket;
    public:
    EthernetFrame();
    uint32_t crc32();
    void setpreamble(uint64_t &preamble);
    void setpayload(vector<uint16_t> &payload);
    void setType(uint16_t &etherType);
    void setSourceAddr(uint64_t &SourceAddress);
    void setDestAddr(uint64_t &DestinationAddress);
    void setIFG(uint64_t &IFG);
    uint64_t getPreamble();
    vector<uint16_t> getpayload();
    uint64_t getType();
    uint64_t getSourceAddr();
    uint64_t getDestAddr();
    vector<unsigned int> GeneratePacket_Parameters();
    long long convertStrHexa(string hexaStr);
    string intToHex(uint64_t value);
    string intvector2string(vector<uint16_t> &value);
    string generate_packet(int IFG_per_packet,vector<IQsamples>& iqvalues);
    string repeatString(const std::string& str, int times);
    string putIdIntoStringTwoByte(uint16_t id);
    string putIdIntoStringFourByte(uint32_t id);
    string putIdIntoStringOneByte(uint16_t id);
};
#endif