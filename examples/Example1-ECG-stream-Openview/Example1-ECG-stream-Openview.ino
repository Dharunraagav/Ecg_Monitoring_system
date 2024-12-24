//////////////////////////////////////////////////////////////////////////////////////////
//
//    Demo code for the MAX30003 breakout board
//
//    This example plots the ECG through serial UART on openview processing GUI.
//    GUI URL: https://github.com/Protocentral/protocentral_openview.git
//
//    Arduino connections:
//
//  |MAX30003 pin label| Pin Function         |Arduino Connection|
//  |----------------- |:--------------------:|-----------------:|
//  | MISO             | Slave Out            |  D12             |
//  | MOSI             | Slave In             |  D11             |
//  | SCLK             | Serial Clock         |  D13             |
//  | CS               | Chip Select          |  D7              |
//  | VCC              | Digital VDD          |  +5V             |
//  | GND              | Digital Gnd          |  Gnd             |
//  | FCLK             | 32K CLOCK            |  -               |
//  | INT1             | Interrupt1           |  02              |
//  | INT2             | Interrupt2           |  -               |
//
//    This software is licensed under the MIT License(http://opensource.org/licenses/MIT).
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//   NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//   For information on how to use, visit https://github.com/Protocentral/protocentral_max30003
//
/////////////////////////////////////////////////////////////////////////////////////////

#include <SPI.h>

// Constants
#define MAX30003_CS_PIN 7
#define INT_PIN 2

#define CES_CMDIF_PKT_START_1 0x0A
#define CES_CMDIF_PKT_START_2 0xFA
#define CES_CMDIF_TYPE_DATA 0x02
#define CES_CMDIF_PKT_STOP 0x0B

#define DATA_LEN 12
#define ZERO 0

// Data packet arrays
byte DataPacket[DATA_LEN];
const byte DataPacketFooter[2] = {ZERO, CES_CMDIF_PKT_STOP};
const byte DataPacketHeader[5] = {CES_CMDIF_PKT_START_1, CES_CMDIF_PKT_START_2, DATA_LEN, ZERO, CES_CMDIF_TYPE_DATA};

// Define MAX30003 class to simulate functionality
class MAX30003 {
public:
  uint32_t ecgdata;
  uint16_t RRinterval;
  uint8_t heartRate;

  MAX30003(uint8_t cs_pin) {
    this->cs_pin = cs_pin;
    pinMode(cs_pin, OUTPUT);
    digitalWrite(cs_pin, HIGH);  // disable the MAX30003 initially
  }

  bool max30003ReadInfo() {
    // Simulate successful read from MAX30003
    return true;  // Replace with actual implementation if available
  }

  void max30003Begin() {
    // Initialize the MAX30003
  }

  uint32_t getEcgSamples() {
    // Simulate getting ECG samples
    ecgdata = 123456;  // Placeholder value
    return ecgdata;
  }

  void getHRandRR() {
    // Simulate getting heart rate and RR interval
    heartRate = 75;  // Placeholder value
    RRinterval = 800;  // Placeholder value
  }

private:
  uint8_t cs_pin;
};

// Initialize MAX30003 instance
MAX30003 max30003(MAX30003_CS_PIN);

void setup() {
  // Start Serial communication
  Serial.begin(57600);

  // Initialize SPI
  SPI.begin();
  pinMode(MAX30003_CS_PIN, OUTPUT);
  digitalWrite(MAX30003_CS_PIN, HIGH);  // Disable device initially

  // Initialize MAX30003
  bool ret = max30003.max30003ReadInfo();
  if (ret) {
    Serial.println("MAX30003 read ID Success");
  } else {
    while (!ret) {
      Serial.println("Failed to read ID, please make sure all the pins are connected.");
      delay(5000);  // Wait 5 seconds and try again
      ret = max30003.max30003ReadInfo();
    }
  }

  Serial.println("Initializing MAX30003...");
  max30003.max30003Begin();
}

void sendDataThroughUART() {
  // Populate DataPacket with ECG data, RR interval, and heart rate
  DataPacket[0] = max30003.ecgdata & 0xFF;
  DataPacket[1] = (max30003.ecgdata >> 8) & 0xFF;
  DataPacket[2] = (max30003.ecgdata >> 16) & 0xFF;
  DataPacket[3] = (max30003.ecgdata >> 24) & 0xFF;

  DataPacket[4] = max30003.RRinterval & 0xFF;
  DataPacket[5] = (max30003.RRinterval >> 8) & 0xFF;
  DataPacket[6] = 0x00;
  DataPacket[7] = 0x00;

  DataPacket[8] = max30003.heartRate & 0xFF;
  DataPacket[9] = (max30003.heartRate >> 8) & 0xFF;
  DataPacket[10] = 0x00;
  DataPacket[11] = 0x00;

  // Send packet header
  for (int i = 0; i < 5; i++) {
    Serial.write(DataPacketHeader[i]);
  }

  // Send MAX30003 data
  for (int i = 0; i < DATA_LEN; i++) {
    Serial.write(DataPacket[i]);
  }

  // Send packet footer
  for (int i = 0; i < 2; i++) {
    Serial.write(DataPacketFooter[i]);
  }
}

void loop() {
  // Get ECG sample and heart rate/RR interval
  max30003.getEcgSamples();
  max30003.getHRandRR();

  // Send the data through UART
  sendDataThroughUART();

  // Delay for 8ms
  delay(8);
}
