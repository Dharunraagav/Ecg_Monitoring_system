# Ecg_Monitoring_System

## Overview

The **Ecg_Monitoring_System** is a project that utilizes the **ProtoCentral MAX30003 ECG AFE Sensor** to monitor and record Electrocardiogram (ECG) signals. This system is designed for real-time ECG data acquisition, heart rate (HR) measurement, and R-R interval detection, making it suitable for health monitoring applications.

The project uses the MAX30003 chip, a single-lead ECG analog front-end that also includes heartbeat detection for real-time monitoring. The system is capable of collecting and transmitting ECG data via serial communication (UART) to be visualized and analyzed on a computer or other devices.

### Features
- Real-time ECG monitoring
- Heart rate measurement
- R-R interval detection (for heartbeat analysis)
- Easy integration with Arduino and other platforms
- Data visualization via serial communication

## Requirements

To use the **Ecg_Monitoring_System**, you will need the following components:

- **ProtoCentral MAX30003 ECG AFE Sensor** (Breakout Board)
- An Arduino (or compatible) board
- Jumper wires for connections
- A PC or device to receive the data (via serial communication)

### Software Requirements
- Arduino IDE (to upload the code to the Arduino)
- **ProtoCentral MAX30003 ECG AFE Sensor Library** v1.0.2
- Serial terminal software (e.g., PuTTY, Arduino Serial Monitor, etc.)

## Hardware Connections

### Arduino to MAX30003 Breakout Board

| MAX30003 Pin Label | Pin Function         | Arduino Pin Connection |
|--------------------|----------------------|------------------------|
| MISO               | Slave Out            | D12                    |
| MOSI               | Slave In             | D11                    |
| SCLK               | Serial Clock         | D13                    |
| CS                 | Chip Select          | D7                     |
| VCC                | Digital VDD          | +5V                    |
| GND                | Digital Gnd          | GND                    |
| FCLK               | 32K Clock            | -                      |
| INT1               | Interrupt 1          | D2                     |
| INT2               | Interrupt 2          | -                      |

## Code Description

### 1. **MAX30003 Sensor Initialization**
The MAX30003 sensor is initialized through the SPI interface. The program continuously reads ECG data and sends it to a serial port for visualization.

### 2. **ECG Data Processing**
The code reads ECG samples from the MAX30003 chip and calculates the heart rate (HR) and R-R intervals. The data is packaged and sent via UART to a connected computer or display system.

### 3. **Real-Time Heart Rate and R-R Interval Monitoring**
Whenever an interrupt is triggered, the system fetches the heart rate and RR intervals and prints them to the serial monitor for real-time feedback.

### 4. **Serial Communication**
The collected data (ECG samples, heart rate, and RR intervals) is transmitted via the serial interface for visualization and further processing.

## Getting Started

### 1. Install the MAX30003 Arduino Library

To make the system work, you'll need the **ProtoCentral MAX30003 ECG AFE Sensor Library**.

1. Open the Arduino IDE.
2. Go to **Sketch** > **Include Library** > **Manage Libraries**.
3. Search for **ProtoCentral MAX30003**.
4. Install the library.

### 2. Upload the Code

1. Download or clone this repository.
2. Open the Arduino IDE and load the code (`.ino` file) provided in this repository.
3. Select the correct Arduino board and port.
4. Click on **Upload** to upload the code to your Arduino.

### 3. Monitor the Data

1. Once the code is uploaded, open the Serial Monitor in the Arduino IDE (set the baud rate to **57600**).
2. You should start seeing the ECG data, heart rate, and RR intervals printed on the Serial Monitor.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- **ProtoCentral Electronics** for providing the **MAX30003 ECG AFE Sensor** and the associated library.
- **Maxim Integrated** for creating the MAX30003 chip.

For further details and information, visit the [ProtoCentral GitHub Repository](https://github.com/Protocentral/protocentral_max30003).

## Troubleshooting

- If the sensor is not providing data, ensure that the wiring is correct and the sensor is powered properly.
- If you encounter issues with the serial communication, verify that the baud rate is set correctly and the right serial port is selected.
- For additional help, refer to the official [MAX30003 documentation](https://www.maximintegrated.com/en/products/analog/biometric-sensing/MAX30003.html).
