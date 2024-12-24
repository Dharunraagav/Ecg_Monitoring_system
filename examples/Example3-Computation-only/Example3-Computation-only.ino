//////////////////////////////////////////////////////////////////////////////////////////
//
//    Demo code for the MAX30003 breakout board
//
//    This example displays heart rate and rr interval through arduino serial port.
//
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

#define INT_PIN 2
#define MAX30003_CS_PIN 7
#define RTOR_INTR_MASK 0x01

// MAX30003 class to emulate functionality
class MAX30003 {
public:
  uint8_t statusReg[3];
  uint16_t heartRate;
  uint16_t RRinterval;

  MAX30003(uint8_t cs_pin) {
    this->cs_pin = cs_pin;
    pinMode(cs_pin, OUTPUT);
    digitalWrite(cs_pin, HIGH);  // Disable MAX30003 initially
  }

  bool max30003ReadInfo() {
    // Simulate reading info from MAX30003
    return true;  // Simulate success
  }

  void max30003BeginRtorMode() {
    // Initialize MAX30003 in RTOR mode
    // Add your RTOR mode initialization code here
  }

  void max30003RegRead(uint8_t reg, uint8_t* buffer) {
    // Simulate reading from a register
    buffer[0] = 0x00;
    buffer[1] = RTOR_INTR_MASK;  // Simulate interrupt flag being set
    buffer[2] = 0x00;
  }

  void getHRandRR() {
    // Simulate reading heart rate and RR interval
    heartRate = 75;  // Placeholder value
    RRinterval = 800;  // Placeholder value
  }

private:
  uint8_t cs_pin;
};

// Instantiate MAX30003
MAX30003 max30003(MAX30003_CS_PIN);

void setup() {
  // Start Serial communication
  Serial.begin(115200);
  
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

  // Initialize in RTOR mode
  Serial.println("Initializing MAX30003 in RTOR mode...");
  max30003.max30003BeginRtorMode();

  // Set up interrupt pin for simulation
  pinMode(INT_PIN, INPUT_PULLUP);  // Using the interrupt pin as an input with pull-up
}

void loop() {
  // Polling to simulate interrupt handling
  delay(10);  // Small delay to simulate waiting for interrupt

  if (checkForInterrupt()) {
    // Read status register
    max30003.max30003RegRead(0x00, max30003.statusReg);

    // Check for RTOR interrupt
    if (max30003.statusReg[1] & RTOR_INTR_MASK) {
      // Read Heart Rate and RR Interval
      max30003.getHRandRR();
      Serial.print("Heart Rate = ");
      Serial.println(max30003.heartRate);
      Serial.print("RR interval = ");
      Serial.println(max30003.RRinterval);
    }
  }
}

bool checkForInterrupt() {
  // Simulate interrupt check
  // Replace with actual interrupt checking logic
  return true;  // For simulation, always return true
}
