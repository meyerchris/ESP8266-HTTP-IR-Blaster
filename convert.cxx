#include <iostream>

// Found raw at: http://www.avsforum.com/forum/166-lcd-flat-panel-displays/1936145-samsung-un24h4500afxza-toggle-discrete-power-off-switching-inputs.html
// Converted using: http://irdb.tk/decode/

// Reverse the order of bits in a byte
// Example: 01000000 -> 00000010
unsigned char ReverseByte(unsigned char b)
{
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return(b);
}

// Calculate 32 bit NECx code
unsigned long GenNECXCode(unsigned char p_Device, unsigned char p_SubDevice, unsigned char p_Function)
{
  unsigned long ReverseDevice = (unsigned long)ReverseByte(p_Device);
  unsigned long ReverseSubDevice = (unsigned long)ReverseByte(p_SubDevice);
  unsigned long ReverseFunction = (unsigned long)ReverseByte(p_Function);
  return((ReverseDevice << 24) | (ReverseSubDevice << 16) | (ReverseFunction << 8) | ((~ReverseFunction) & 0xFF));
}

int main(int argc, char *argv[])
{
  int SAMSUNG_BITS = 32;
  unsigned long SAMSUNG_POWER_ON = GenNECXCode(7,7,153); // Discrete ON
  unsigned long SAMSUNG_POWER_OFF = GenNECXCode(7,7,152); // Discrete OFF
  unsigned long SAMSUNG_SRC_HDMI1 = GenNECXCode(7,7,233); // HDMI 1
  unsigned long SAMSUNG_SRC_HDMI2 = GenNECXCode(7,7,190); // HDMI 2
  unsigned long SAMSUNG_SRC_HDMI3 = GenNECXCode(7,7,194); // HDMI 2

  std::cout << "on --> SAMSUNG:" << std::hex << SAMSUNG_POWER_ON << ":" << std::dec << SAMSUNG_BITS << std::endl;
  std::cout << "off --> SAMSUNG:" << std::hex << SAMSUNG_POWER_OFF << ":" << std::dec << SAMSUNG_BITS << std::endl;
  std::cout << "hdmi1 --> SAMSUNG:" << std::hex << SAMSUNG_SRC_HDMI1 << ":" << std::dec << SAMSUNG_BITS << std::endl;
  std::cout << "hdmi2 --> SAMSUNG:" << std::hex << SAMSUNG_SRC_HDMI2 << ":" << std::dec << SAMSUNG_BITS << std::endl;
  std::cout << "hdmi3 --> SAMSUNG:" << std::hex << SAMSUNG_SRC_HDMI3 << ":" << std::dec << SAMSUNG_BITS << std::endl;

  // irsend.sendSAMSUNG(SAMSUNG_POWER_ON, SAMSUNG_BITS);
}
