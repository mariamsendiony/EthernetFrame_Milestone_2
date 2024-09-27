#include"ORAN.h"
/*
A single section is used per one Ethernet packet with IQ samples startPrbu is equal to 0 and numPrbu is equal to the number of RBs used:

rb field is not used (value 0).

symInc is not used (value 0)
*/
    uint8_t ORAN::frameId=0;
    uint8_t ORAN::subframeId=0;
    uint8_t ORAN::slotId=0;
    uint8_t ORAN::symbolId=0;
    int ORAN::index_within_iq=0;
    int ORAN::count=0;

ORAN::ORAN()
{
  
    first_byte=0;
    numPrbu = Config::NRBPerpacket==273? 0: Config::NRBPerpacket;
    StartPrbu=0;
    sectionId=0;
    RB=0;
    SymInc=0;
   

}

void ORAN::setFirstByte(uint8_t value)
{
    first_byte=value;
}

void ORAN::setFrameId(uint8_t value)
{
    frameId=value;
}

void ORAN::setSubframeId(uint8_t value)
{
    subframeId=value;
}

void ORAN::setSlotId(uint8_t value)
{
    slotId=value;
}

void ORAN::setSymbolId(uint8_t value)
{
    symbolId=value;
}

void ORAN::setSectionId(uint16_t value)
{
    sectionId=value;
}

void ORAN::setRB(uint8_t value)
{
    RB=value;
}

void ORAN::setSymInc(uint8_t value)
{
    SymInc=value;
}

void ORAN::setStartPrbu(uint16_t value)
{
    StartPrbu=value;
}

void ORAN::setNumPrbu(uint8_t value)
{
    numPrbu=value;
}

void ORAN::setPayload(const std::vector<IQsamples> &value)
{
    payload=value;
}

void ORAN::setCount(int value)
{
    count=value;
}

void ORAN::setIndexWithinIq(int value)
{
    index_within_iq=value;
}

uint8_t ORAN::getFirstByte() const
{
    return first_byte;
}

uint8_t ORAN::getFrameId()
{
    return frameId;
}

uint8_t ORAN::getSubframeId()
{
    return subframeId;
}

uint8_t ORAN::getSlotId()
{
    return slotId;
}

uint8_t ORAN::getSymbolId()
{
    return symbolId;
}

uint16_t ORAN::getSectionId() const
{
    return sectionId;
}

uint8_t ORAN::getRB() const
{
    return RB;
}

uint8_t ORAN::getSymInc() const
{
    return SymInc;
}

uint16_t ORAN::getStartPrbu() const
{
    return StartPrbu;
}

uint8_t ORAN::getNumPrbu() const
{
    return numPrbu;
}

int ORAN::getIndexWithinIq()
{
    return index_within_iq;
}

// vector<int> ORAN::calculate()
// {
//     vector<int> parameters;
//     //Slot calculations
//     int number_slots=Config::SCS/15;
//     double slotduration_ms=1/(double(number_slots));
//     //cout<<slotduration_ms<<'\n';
//     //Each slot contains 14 symbols and each symbol has a specific NRB
//     int Number_packets_per_symbol=ceil((float)Config::MaxNRB/(float) Config::NRBPerpacket);
//     //cout<<Number_packets_per_symbol<<'\n';
//     int Number_packets_per_slot=Number_packets_per_symbol*14;
//     //cout<<Number_packets_per_slot<<'\n';
//     int Number_packets_per_frame=Number_packets_per_slot*10*number_slots;
//     //cout<<Number_packets_per_frame<<'\n';
//     int Number_packets_per_second=Number_packets_per_frame*((float)pow(10,3)*(Config::CaptureSizeMs/10));
//     //cout<<Number_packets_per_second<<'\n';
//     //rate=size/time
//     //Total number of packets during the transmission duration
//     int totalPackets=Number_packets_per_second *(Config::CaptureSizeMs/1000);
//     //cout<<"total"<<totalPackets<<'\n';
//     int total_bytes_duration=Config::LineRate*pow(10,6)*Config::CaptureSizeMs;
//     //cout<<total_bytes_duration<<'\n';
//     int number_bytes_per_packet_per_ORAN_per_second_payload=Number_packets_per_second*Config::NRBPerpacket*2*12;
//     //cout<<number_bytes_per_packet_per_ORAN_per_second_payload<<'\n';
//     //Using the units bytes/s *s/packet=bytes/packet when calculated,720,divide by 12,60,divide by 30 equals 24 divide by 12 which equals 2.
//     int number_bytes_per_packet=number_bytes_per_packet_per_ORAN_per_second_payload/Number_packets_per_second;
//     //cout<<number_bytes_per_packet<<'\n';
//     int total_time_seconds=Config::CaptureSizeMs*pow(10,3);
//     //cout<<total_time_seconds;

// }

string ORAN::int2Hex(uint32_t value)
{
    ostringstream ss;
    ss << std::hex << value;
    return ss.str();
    
}
string ORAN::intToHex(int value)
{
    
    ostringstream oss;
    // Convert to hexadecimal
    oss << std::hex << value; 
    return oss.str();

}
uint16_t ORAN::convertStrHexa(string hexaStr)
{
    std::istringstream iss(hexaStr);
    unsigned int hexNumber;

    // Read the hexadecimal string into an unsigned integer
    iss >> std::hex >> hexNumber;
    return hexNumber;
  
}


void ORAN::generate_ORAN_packet(vector<uint16_t>& ORANPacket)
{   
    IQsamples iqq;
    vector<IQsamples> iqvalues = readiq("iq_file.txt",iqq);
    

    if(symbolId==14){
        symbolId=0;
        slotId++;
        if(slotId==(Config::SCS/15)){
        slotId=0;
        subframeId++;
                if(subframeId==10){
                subframeId=0;
                frameId++;
            }
        }
    }
    ORANPacket.push_back(first_byte);
    ORANPacket.push_back(frameId);
    ORANPacket.push_back(subframeId);
    ORANPacket.push_back(slotId);
    ORANPacket.push_back(symbolId);
    ORANPacket.push_back(sectionId);
    ORANPacket.push_back(RB);
    ORANPacket.push_back(SymInc);
    ORANPacket.push_back(StartPrbu);
    ORANPacket.push_back(numPrbu);
    
    int limit=index_within_iq+Config::NRBPerpacket*12;

    for(int i=index_within_iq;i<(limit);i++){
        string hex_i = intToHex(iqvalues[i].i);
        string hex_q = intToHex(iqvalues[i].q);
        
        ORANPacket.push_back(stoul(hex_i, nullptr, 16));
        ORANPacket.push_back(stoul(hex_q, nullptr, 16));
        
        // Incase the data from the input file ends, loop back to the start of the file
        if(i == iqvalues.size() - 1){
            int diff=(Config::NRBPerpacket*12)-(i-index_within_iq+1);
            index_within_iq=0;
            limit=diff;
        }
    }

    index_within_iq=index_within_iq+Config::NRBPerpacket*12;
    
    symbolId++;



}

int ORAN::generate_ORAN_packet_fragmentation(vector<uint16_t> &ORANPacket)
{
    IQsamples iqq;
    vector<IQsamples> iqvalues = readiq("iq_file.txt",iqq);
    //headers+minimumIFG
    int limit;
    int headersandminimumIFG=42+Config::MinNumOfIFGsPerPacket;
    int IFG=Config::MinNumOfIFGsPerPacket;
    //MAX packet size is assumed to always be divisible by 4
    int payload_ORAN_per_packet=(Config::MaxPacketSize)-headersandminimumIFG;
    while(payload_ORAN_per_packet%(Config::NRBPerpacket*12)!=0){
        payload_ORAN_per_packet=payload_ORAN_per_packet--;
        IFG++;
    }
    int Number_required_payload_bytes=Config::NRBPerpacket*12*2*2;
    int Number_packets_torepresent_required=ceil((float)Number_required_payload_bytes/(float)payload_ORAN_per_packet);
    if(count==Number_packets_torepresent_required)
    {
        return IFG;
    }
    else{
                if(count==0||count!=(Number_packets_torepresent_required-1)){
                    limit=index_within_iq+payload_ORAN_per_packet/4;
                    count++;
                }
        
                    
                else{
                    int diff=Number_required_payload_bytes-(count*payload_ORAN_per_packet);
                    limit=index_within_iq+diff/4;
                    count++;
                    while(headersandminimumIFG+diff%4!=0){
                        IFG++;
                    }
                 }
        
    }
    for(int i=index_within_iq;i<(limit);i++){
        string hex_i = intToHex(iqvalues[i].i);
        string hex_q = intToHex(iqvalues[i].q);
        
        ORANPacket.push_back(stoul(hex_i, nullptr, 16));
        ORANPacket.push_back(stoul(hex_q, nullptr, 16));
        
        // Incase the data from the input file ends, loop back to the start of the file
        if  (i == iqvalues.size() - 1){
            int diff=(Config::NRBPerpacket*12)-(i-index_within_iq+1);
            index_within_iq=0;
            limit=diff;
        }
    }

    

}

// int main()
// {
    
//     Config Configuration;    
//     readConfig("second_milstone.txt", Configuration);
//     ORAN ora;
//     //ora.calculate();
//     vector< uint16_t> packet,packet2;
//     ora.generate_ORAN_packet(packet);
    
//     // for (int i=0;i<packet.size();i++) {
//     //    cout <<std::hex<< packet[i] << " ";
//     // }
//     // ora.generate_ORAN_packet(packet2);

//     // for (int i=0;i<packet2.size();i++) {
//     //    cout <<std::hex<< packet2[i] << " ";
//     // }
// }
