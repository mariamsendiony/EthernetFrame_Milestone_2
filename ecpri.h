#include "ORAN.cpp"
class ecpri{
  uint8_t  first_byte;
  uint8_t  ecpri_message;
  ORAN* ORANPacket;
  vector<uint16_t> payload;
  uint16_t PC_RTC;
  static uint16_t SeqId;
  public:
  ecpri();
  void generate_ecpri(vector<uint16_t>& ecpriPacket);
  void setFirstByte(uint8_t value);
  void setEcpriMessage(uint8_t value);
  void setORANPacket(ORAN* value);
  void setPayload(const std::vector<uint16_t>& value);
  void setPC_RTC(uint16_t value);
  static void setSeqId(uint16_t value);

    // Getters
  uint8_t getFirstByte() const;
  uint8_t getEcpriMessage() const;
  ORAN* getORANPacket() const;
  const vector<uint16_t>& getPayload() const;
  uint16_t getPC_RTC() const ;
  static uint16_t getSeqId();
};