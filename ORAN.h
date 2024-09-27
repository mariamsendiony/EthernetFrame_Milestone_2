
#include "Read_file_Milestone_2.h"
#include "Readiq.h"
#include <sstream>
#include <ostream>
#include <string>
#include <iostream>
#include <iomanip>

class ORAN
{   //Total bytes=32 8(header)+12(2) I-Q 
    
    uint8_t first_byte;
    static uint8_t frameId;
    static uint8_t subframeId;
    static uint8_t slotId;
    static uint8_t symbolId;
    uint16_t sectionId;
    uint8_t RB;
    uint8_t SymInc;
    uint16_t StartPrbu;
    uint8_t numPrbu;
    vector<IQsamples> payload;
    static int count;
    static int index_within_iq;
    public:
    ORAN();
    //vector<int> calculate();
    // Setters
    void setFirstByte(uint8_t value);
    static void setFrameId(uint8_t value);
    static void setSubframeId(uint8_t value);
    static void setSlotId(uint8_t value);
    static void setSymbolId(uint8_t value);
    void setSectionId(uint16_t value);
    void setRB(uint8_t value);
    void setSymInc(uint8_t value);
    void setStartPrbu(uint16_t value);
    void setNumPrbu(uint8_t value);
    void setPayload(const std::vector<IQsamples>& value);
    static void setCount(int value);
    static void setIndexWithinIq(int value);

    // Getters
    uint8_t getFirstByte() const;
    static uint8_t getFrameId();
    static uint8_t getSubframeId();
    static uint8_t getSlotId();
    static uint8_t getSymbolId();
    uint16_t getSectionId() const;
    uint8_t getRB() const;
    uint8_t getSymInc() const;
    uint16_t getStartPrbu() const;
    uint8_t getNumPrbu() const;
    const std::vector<IQsamples>& getPayload() const;
    static int getCount() { return count; }
    static int getIndexWithinIq();
    ///
    string int2Hex(uint32_t value);
    void generate_ORAN_packet(vector<uint16_t>& ORANPacket);
    int generate_ORAN_packet_fragmentation(vector<uint16_t>& ORANPacket);
    string intToHex( int value);
    uint16_t convertStrHexa(string hexaStr);

};



