//////////////////////////////////////////////////////////////////////////////////////////
//
//    Demo code for the MAX30003 breakout board
//
//    This example plots the ECG through Arduino Plotter.
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

// Initialize MAX30003 class to simulate functionality
class MAX30003 {
public:
  uint32_t ecgdata;

  MAX30003(uint8_t cs_pin) {
    this->cs_pin = cs_pin;
    pinMode(cs_pin, OUTPUT);
    digitalWrite(cs_pin, HIGH);  // Disable the MAX30003 initially
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

void loop() {
  // Read ECG sample
  max30003.getEcgSamples();

  // Print ECG data to Serial monitor
  Serial.println(max30003.ecgdata);

  // Send ECG data over UART
  Serial.write(String(max30003.ecgdata).c_str());
  Serial.write('\n');  // Add a newline character for readability

  // Delay for 8ms (similar to the time.sleep(0.008) in Python)
  delay(8);
}
