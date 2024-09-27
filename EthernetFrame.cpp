#include "EthernetFrame.h"

uint32_t EthernetFrame::crc32()
{
   
    
    std::vector<uint64_t> data ={preamble, Config::DestAddress,Config::SourceAddress,etherType};
    data.insert(data.end(),payload.begin(),payload.end());

    uint32_t crc = 0xFFFFFFFF; // Initial value
    for (auto byte : data) {
        crc ^= byte;
        for (int i = 0; i < 8; ++i) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320; // Polynomial
            } else {
                crc >>= 1;
            }
        }
    }
    return ~crc; // Final XOR value
}

EthernetFrame::EthernetFrame()
{   
    vector<uint16_t> payload;
    ecpri* ecpripacket=new ecpri;
    destinationMac= Config::DestAddress;
    sourceMac=Config::SourceAddress;
    preamble=0xFB555555555555D5;
    etherType=0xAEFE;
    
}

void EthernetFrame::setpreamble(uint64_t &preamble)
{

    this->preamble=preamble;
}

void EthernetFrame::setpayload(vector<uint16_t> &payload)
{
    this->payload=payload;
}


void EthernetFrame::setType(uint16_t &etherType)
{
    this->etherType=etherType;
   
}

void EthernetFrame::setSourceAddr(uint64_t &SourceAddress)
{

   sourceMac=SourceAddress;
}

void EthernetFrame::setDestAddr(uint64_t &DestinationAddress)
{
    destinationMac=DestinationAddress;
}

void EthernetFrame::setIFG(uint64_t &IFG)
{
   this->IFG=IFG;
}

uint64_t EthernetFrame::getPreamble()
{
    return preamble;
}

vector<uint16_t> EthernetFrame::getpayload()
{
    return payload;
}

uint64_t EthernetFrame::getType()
{
    return etherType;
}

uint64_t EthernetFrame::getSourceAddr()
{
    return sourceMac;
}

uint64_t EthernetFrame::getDestAddr()
{
    return destinationMac;
}

vector< unsigned int > EthernetFrame::GeneratePacket_Parameters()
{   vector <unsigned int> parameters;
    unsigned int ORAN_Payload=Config::NRBPerpacket*12*2*2;
    unsigned int ORAN_Header=8;
    unsigned int Ecpri_Header=8;
    unsigned int ORAN_Size=ORAN_Payload+ORAN_Header;
    //WithoutIFG
    unsigned int Ethernet_Header=26;
    unsigned int Frame_size_without_IFG=ORAN_Size+Ecpri_Header+Ethernet_Header;
    unsigned int IFG=Config::MinNumOfIFGsPerPacket;

    //cout<<"Frame_size_without_IFG"<<Frame_size_without_IFG<<'\n';
  
    //Check 4 bytes alignment
    while((Frame_size_without_IFG+IFG)%4!=0)
    {
        IFG +=1;

    }
    unsigned int Frame_size_bytes=Frame_size_without_IFG+IFG;
    //checking fragmentation
      if(Frame_size_bytes>Config::MaxPacketSize)
    {
        cout<<"Frame size exceeds maximum packet size\n";
        return parameters;
    }
    //cout<<"Frame_size_bytes"<<Frame_size_bytes<<'\n';

    //Want to calculate number of ethernet frames to send withing the time interval
    unsigned int number_slots=Config::SCS/15;
    unsigned int Number_packets_per_symbol=ceil((float)Config::MaxNRB/(float) Config::NRBPerpacket);
    //cout<<Number_packets_per_symbol<<'\n';
    unsigned int Number_packets_per_slot=Number_packets_per_symbol*14;
    //cout<<Number_packets_per_slot<<'\n';
    unsigned int Number_packets_per_frame=Number_packets_per_slot*10*number_slots;
    //cout<<Number_packets_per_frame<<'\n';
    unsigned int Number_packets_per_second=Number_packets_per_frame*((float)pow(10,3)*(Config::CaptureSizeMs/10));
    //cout<<Number_packets_per_second<<'\n';
    unsigned int total_bytes_duration=Config::LineRate*pow(10,6)*Config::CaptureSizeMs;
    //cout<<total_bytes_duration<<'\n';
    unsigned int total_time_seconds=Config::CaptureSizeMs*pow(10,3);
    //cout<<total_time_seconds<<'\n';
    unsigned int totalPackets=Number_packets_per_second *(Config::CaptureSizeMs/1000);
    //cout<<"total"<<totalPackets<<'\n';
    float ethernet_time_seconds=(float)Frame_size_bytes*8/((float)Config::LineRate*pow(10,9));
    //cout<<ethernet_time_seconds<<'\n';
    //Calculate number of IFG at the end
    unsigned IFG_at_end_bytes=(total_time_seconds-(ethernet_time_seconds*totalPackets))*Config::LineRate/8;
    //cout<<IFG_at_end_bytes<<'\n';



    
    parameters={IFG,IFG_at_end_bytes,totalPackets};
   
    return parameters;
  

}
long long convertStrHexa(string hexaStr){
    const int hexaStrLength = hexaStr.length();
    // const short diffLowerCaseToDigits, diffUpperCaseDigits;
    long long res = 0;
    short int hexaCharToDigit;
    if (hexaStrLength <= 2 || ! (hexaStr[0] && (hexaStr[1] == 'x' || hexaStr[1] == 'X')))
        return -1;
    
    for (int i = 2; i < hexaStrLength; i++){ // start from the third element after 0x
        // if (hexaStr[i] == 'x' || hexaStr[i] == 'X')
        //     break; // reached the hexadecimal annotator
        
        if (hexaStr[i] >= 48 && hexaStr[i] <= 57) // that means that the number in the range of [0-9]
        {
            hexaCharToDigit = hexaStr[i] - 48;
        }
        else if (hexaStr[i] >= 97 && hexaStr[i] <= 102) // means in range [a-f]
        {
            hexaCharToDigit = hexaStr[i] - 97 + 10; // 10 is the offset where a starts from 10
        }
        else if (hexaStr[i] >= 65 && hexaStr[i] <= 70)
        {
            hexaCharToDigit = hexaStr[i] - 65 + 10;
        }
        else
        {
            cout << "Incorrect format" << endl;
            return -1;
        }
        res = res << 4;  // 4 shifts equivalent to multiply by 16
        res += hexaCharToDigit;
    }
    return res;
}

string EthernetFrame::intToHex(uint64_t value)
{
    std::ostringstream ss;
    ss << std::hex << value;
    return ss.str();
   
}

string EthernetFrame::intvector2string(vector<uint16_t> &value)
{
    string result="";
    
    for (int i = 0; i < value.size(); ++i) {
        if(i<7 || i==8|| i==9||i==11){
            result=result+putIdIntoStringOneByte(value[i]);
        }
        else{
             result=result+putIdIntoStringTwoByte(value[i]);
        }
    }
    return result;
}

string EthernetFrame::generate_packet(int IFG_per_packet)
{
    
    
    string IFG_byte="07";
    uint32_t crc=crc32();
    //cout<<(crc);
    string payloadStr;
    ecpri* ecpripacket=new ecpri;
    ecpripacket->generate_ecpri(payload);
    payloadStr=intvector2string(payload);

    string Frame=intToHex(preamble)+to_string(destinationMac)+to_string(sourceMac)+intToHex(etherType)+payloadStr+putIdIntoStringFourByte(crc)+repeatString(IFG_byte,IFG_per_packet);
    //cout<<Frame<<'\n';
    return Frame ;
}

string EthernetFrame::repeatString(const std::string &str, int times)
{
    
    string result;
    while (times > 0) {
        result += str;
        times--;
    }
    return result;
}
string EthernetFrame::putIdIntoStringTwoByte(uint16_t id)
{
        if (id < 0 || id > 65535)
    {
        throw std::out_of_range("Number must be between 0 and 65535");
    }
    std::stringstream stream;
    stream << std::setw(4) << std::setfill('0') << std::hex << std::uppercase << id;
    return stream.str();
}
string EthernetFrame::putIdIntoStringFourByte(uint32_t id)
{   //cout<<id<<'\n';
        if (id < 0 || id > 4294967295)
    {
        throw std::out_of_range("Number must be between 0 and 4,294,967,295");
    }
    std::stringstream stream;
    stream << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << id;
    return stream.str();
}
string EthernetFrame::putIdIntoStringOneByte(uint16_t id)
{
        if (id < 0 || id > 255)
    {
        throw std::out_of_range("Number must be between 0 and 255");
    }
    std::stringstream stream;
    stream << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << id;
    return stream.str();
}
/*
int main(){
    Config Configuration;
    readConfig("second_milstone.txt", Configuration);
    EthernetFrame* ef;
    vector<unsigned int> parameters=ef->GeneratePacket_Parameters();

    for(int i=0;i<15;i++){
        ef=new EthernetFrame;
        string packet=ef->generate_packet(parameters[0]);
        cout<<packet<<'\n';
        cout<<"------------------------------------"<<'\n';
    }

}
*/
