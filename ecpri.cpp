#include "ecpri.h"

uint16_t ecpri::SeqId=0;
ecpri::ecpri()
{
    ORANPacket=new ORAN;
    first_byte=0x00;
    ecpri_message=0x00;
    PC_RTC=0x00;
}
void ecpri::generate_ecpri(vector<uint16_t> &ecpriPacket,vector<IQsamples>& iqvalues)
{
    
    vector<uint16_t> ORAN_packet;
    ORANPacket->generate_ORAN_packet(ORAN_packet,iqvalues);
    ecpriPacket.push_back(first_byte);
    ecpriPacket.push_back(ecpri_message);
    ecpriPacket.insert(ecpriPacket.end(),ORAN_packet.begin(),ORAN_packet.end());
    ecpriPacket.push_back(PC_RTC);
    ecpriPacket.push_back(SeqId);
    SeqId++;
    if(SeqId==256)
    {
        SeqId=0;
    }
    
}

void ecpri::setFirstByte(uint8_t value)
{
    first_byte=value;
}

void ecpri::setEcpriMessage(uint8_t value)
{
    ecpri_message=value;
}

void ecpri::setORANPacket(ORAN *value)
{
    ORANPacket=value;
}

void ecpri::setPayload(const std::vector<uint16_t> &value)
{
    payload=value;
}

void ecpri::setPC_RTC(uint16_t value)
{
    PC_RTC=value;
}

void ecpri::setSeqId(uint16_t value)
{
    SeqId=value;
}

uint8_t ecpri::getFirstByte() const
{
    return first_byte;
}

uint8_t ecpri::getEcpriMessage() const
{
    return ecpri_message;
}

ORAN *ecpri::getORANPacket() const
{
    return ORANPacket;
}

uint16_t ecpri::getPC_RTC() const
{
    return PC_RTC;
}

uint16_t ecpri::getSeqId()
{
    return SeqId;
}

/*int main()
{
    Config Configuration;    
    readConfig("second_milstone.txt", Configuration);
    ecpri* ecpriobject=new ecpri;
    vector<uint16_t> ecpriPacket;
    ecpriobject->generate_ecpri(ecpriPacket);
    for(int i=0;i<ecpriPacket.size();i++)
    {
        cout<<std::hex<<ecpriPacket[i]<<" ";
    }
    return 0;
}*/