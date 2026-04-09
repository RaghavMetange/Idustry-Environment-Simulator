Industrial Hub: Integrated Automation System - 
A comprehensive ESP32-based controller designed to simulate and manage five critical industrial sub-systems within a single hub. This project demonstrates automation logic, electrical isolation using relays, and sensor-driven workflows.
🚀 Project Overview - 
The Industrial Hub is a multi-functional automation project that consolidates several industrial operations into one microcontroller. Because industrial sensors are often unavailable in simulation environments, this project uses creative hardware substitutions to maintain authentic logic flow.
Core Sub-Systems - 
1. Assembly Line Counter: Monitors production flow using binary state detection.
2. Smart Door Security: A secure entry system utilizing a Relay to control high-power solenoid locks.
3. Vending Machine: Manages dispensing logic triggered by user interaction.
4. Forklift Safety System: A proximity-based warning system to prevent workplace collisions.
5. Parking Occupancy Monitor: Tracks logistics slots and outputs data for real-time monitoring.
🛠 Hardware Substitutions - 
To ensure the project remains functional within simulation environments, several industrial-grade sensors were replaced with standard components. These substitutions maintain the original logic while using parts available in software like Wokwi or Tinkercad:
1. Inductive Proximity Sensor - Slide Switch: Used in the Assembly Line Counter. The switch mimics the binary "High/Low" signal an inductive sensor sends when detecting metal parts on a conveyor belt.
2. IR Proximity Sensor - Pushbutton: Used for the Smart Door Security. Pressing the button simulates a person standing in front of the door, triggering the IR sensor's detection logic.
3. Capacitive Proximity Sensor - Touch Pins: Used in the Vending Machine interface. This leverages the ESP32’s built-in touch-sensing capabilities to simulate industrial touch-sensitive buttons for item selection.
4. Bluetooth Module (HC-05) - Serial Monitor: Used for the Parking Occupancy Monitor. Instead of transmitting data wirelessly, all occupancy logs and telemetry are printed directly to the Serial Monitor for debugging and verification.These mappings ensure that the core C++ logic remains "Hardware Ready." You can transition to physical industrial sensors by simply updating the pin definitions without rewriting the underlying automation code.
⚡ Relay Logic & Safety
A key feature of this system is the integration of Relay Modules.
Galvanic Isolation: The relay physically separates the 3.3V ESP32 logic from high-voltage components (12V-230V).
High-Load Switching: Allows the hub to control industrial actuators like solenoid locks, motors, and sirens that the ESP32 cannot power directly.
Setup & Installation
Hardware: Connect your ESP32 to the relay modules and input components (Buttons/Switches) as per the /diagrams.
Software: * Open the project in the Arduino IDE or VS Code (PlatformIO).
Ensure the ESP32 board library is installed.
Upload the code to your board.
Simulation: For digital testing, import the code into Wokwi or Tinkercad.
🔮 Future Scope
IoT Integration: Adding MQTT support to monitor the hub via a mobile dashboard.
OLED Feedback: Adding a local display for real-time status updates of all 5 systems.
Physical Sensors: Swapping switches for industrial NPN/PNP proximity sensors.
