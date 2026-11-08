# 🔐 Automatic Door Lock System Using PIC16F877A

A password-based automatic door lock system developed as part of the Embedded Systems Laboratory at the Institute of Space Technology (IST), Islamabad.

The project implements an electronic access-control mechanism using a PIC16F877A microcontroller, a 4×3 matrix keypad, and a 16×2 LCD. Users enter a predefined five-digit password through the keypad. Upon successful authentication, the LCD displays an access-granted message, and an L293D motor driver activates a DC motor to operate the door-lock mechanism.

The system also incorporates a three-attempt security mechanism. After three consecutive incorrect password entries, the LCD displays an intruder detection message and activates a buzzer alarm.

The project involved embedded C programming using MPLAB, circuit design and simulation in Proteus, and physical hardware implementation on a breadboard.

## 📌 Project Overview

The Automatic Door Lock System demonstrates the practical application of microcontroller-based embedded systems in electronic access control and security.

The PIC16F877A serves as the central controller, processing password inputs received through the matrix keypad and controlling the LCD, motor-driver circuit, and buzzer.

The system implements two primary operating conditions:

- **Successful Authentication:** When the correct five-digit password is entered, the LCD displays an access-granted message, and the DC motor is activated through the L293D motor driver to operate the door-lock mechanism.
- **Failed Authentication:** Incorrect password entries are detected and counted. After three consecutive unsuccessful attempts, the system displays an intruder detection message and activates the buzzer alarm while keeping the door locked.

## ✨ Key Features

### 1. Five-Digit Password Authentication
- Accepts numerical password input through a 4×3 matrix keypad.
- Processes user input using the PIC16F877A microcontroller.
- Validates the entered five-digit password before granting access.

### 2. LCD-Based User Interface
- Uses a 16×2 character LCD (LM016L).
- Displays password-related messages and authentication results.
- Provides feedback for successful and unsuccessful authentication.

### 3. Automatic Door Operation
- Uses an L293D dual H-bridge motor driver.
- Controls a DC motor following successful password verification.
- Implements motor-driven door-lock operation.

### 4. Three-Attempt Security Mechanism
- Tracks consecutive incorrect password attempts.
- Allows up to three password attempts.
- Displays an intruder detection message after the third unsuccessful attempt.
- Prevents unauthorized door operation.

### 5. Buzzer-Based Intruder Alert
- Activates a buzzer following three consecutive incorrect password entries.
- Provides an audible security alert.
- Keeps the door locked during the security alert condition.

## 🛠️ Hardware Components

| Component | Function |
|---|---|
| PIC16F877A | Main microcontroller for processing inputs and controlling system operations |
| 4×3 Matrix Keypad | Accepts five-digit password input |
| 16×2 LCD (LM016L) | Displays authentication messages and system status |
| L293D Motor Driver | Controls the DC motor using microcontroller signals |
| DC Motor | Operates the door-lock mechanism |
| Buzzer | Generates an audible alert following three incorrect password attempts |
| Crystal Oscillator | Provides the microcontroller clock signal |
| 22 pF Capacitors | Used in the oscillator circuit |
| 10 kΩ Resistor | Used in the microcontroller reset circuitry |
| 1 kΩ Potentiometer | Adjusts LCD contrast |
| Breadboard | Used for physical circuit assembly and prototyping |
| Connecting Wires | Establish electrical connections between components |

## ⚙️ Software and Development Tools

| Tool | Application |
|---|---|
| MPLAB IDE | Embedded C firmware development |
| Proteus 8 Professional | Circuit schematic design and simulation |
| PIC16F877A | Embedded system controller |
| Embedded C | Firmware development and peripheral control |

## 🧠 System Architecture

The system consists of five primary functional sections:

**1. Input Section — Matrix Keypad**

The 4×3 matrix keypad serves as the user input interface. It allows users to enter a five-digit access password, which is received and processed by the PIC16F877A.

**2. Processing Section — PIC16F877A**

The PIC16F877A processes keypad inputs, performs password verification, and maintains the incorrect-attempt counter. Based on the authentication result, it generates the appropriate control signals for the LCD, motor driver, and buzzer.

**3. Display Section — 16×2 LCD**

The LCD provides visual feedback by displaying password-entry prompts, authentication results, and security-related messages.

**4. Actuation Section — L293D and DC Motor**

The L293D motor driver interfaces the microcontroller with the DC motor. Following successful authentication, the driver controls the motor to operate the door-lock mechanism.

**5. Security Section — Buzzer**

The buzzer provides an audible alert when three consecutive incorrect password attempts are detected.

## 🔄 System Operation

The general operating sequence is as follows:

1. The PIC16F877A initializes the keypad, LCD, and associated peripherals.
2. The LCD displays the initial system prompt.
3. The user enters a five-digit password through the matrix keypad.
4. The microcontroller receives and processes the entered password.
5. The entered password is compared with the predefined password.

**If the password is correct:**
- The LCD displays an access-granted message.
- The PIC16F877A sends control signals to the L293D motor driver.
- The motor driver activates the DC motor.
- The motor operates the door-lock mechanism.

**If the password is incorrect:**
- The LCD displays an incorrect password message.
- The incorrect-attempt counter is incremented.
- The door remains locked.

**After three consecutive incorrect attempts:**
- The LCD displays an intruder detection message.
- The buzzer is activated to generate an audible alarm.
- The system prevents unauthorized door operation.

## 🔬 Circuit Design and Simulation

The circuit was designed using Proteus 8 Professional. The surviving original Proteus schematic illustrates the PIC16F877A interfacing with the 4×3 matrix keypad and 16×2 LCD, along with the associated oscillator and reset circuitry.

The microcontroller firmware was developed in embedded C using MPLAB X IDE. The source code was compiled using the MPLAB XC8 compiler to generate a HEX (`.hex`) file containing the compiled firmware.

For simulation in Proteus, the generated HEX file was assigned to the **Program File** property of the PIC16F877A microcontroller component. The oscillator frequency was configured to match the circuit's crystal frequency, and the simulation was executed to test the system's operation.

The surviving original Proteus schematic does not include the motor-driver and buzzer connections. A separate reconstructed circuit schematic illustrating the complete system, including the L293D motor driver, DC motor, and buzzer, will be provided. This illustration will be clearly identified as a reconstruction rather than the original Proteus schematic.

## 🔧 Physical Hardware Implementation

The project was physically assembled on a breadboard, integrating the microcontroller, keypad, LCD, motor-driver circuit, DC motor, and buzzer.

The hardware implementation provided practical experience in:

- PIC microcontroller interfacing.
- Matrix keypad input handling.
- LCD communication and display control.
- DC motor control using an H-bridge motor driver.
- Buzzer interfacing and alarm generation.
- Embedded hardware integration and prototyping.

Original hardware photographs, firmware source files, and the complete original circuit documentation are currently unavailable. The embedded C firmware and complete circuit documentation are being reconstructed for this repository.

## 🎯 Project Objectives

- Understand practical applications of microcontroller-based embedded systems.
- Develop a password-controlled electronic access-control system.
- Interface a matrix keypad with a PIC microcontroller.
- Implement LCD-based user interaction.
- Develop embedded C firmware using MPLAB.
- Implement password validation and attempt-counting logic.
- Integrate a DC motor through an L293D motor driver.
- Implement buzzer-based security alerts.
- Design and simulate electronic circuits using Proteus.
- Gain practical experience in breadboard-based hardware prototyping.

## 📂 Repository Structure

```text
PIC16F877A-Automatic-Door-Lock-System/
│
├── README.md
│
├── src/
│   └── main.c
│
├── images/
│   ├── original-proteus-schematic.png
│   └── reconstructed-circuit-schematic.png
│
└── LICENSE
```

**Note:** The `src/main.c` file has the reconstructed embedded C code that was originally written in MPLAB. The `images/` directory contain the original schematic without the motor driver and the separately labelled reconstructed circuit illustration has all parts. Complete Proteus project files are unavailable.

## 🚀 Possible Future Improvements

- Multiple password support.
- Password modification functionality.
- RFID-based authentication.
- Improved access-control mechanisms.
- Integration of door-position feedback.
- Additional security features and monitoring capabilities.

## 📚 Academic Information

| Detail | Information |
|---|---|
| Project Title | Automatic Door Lock System Using PIC16F877A |
| Institution | Institute of Space Technology (IST), Islamabad |
| Department | Electrical Engineering |
| Course | Embedded Systems Laboratory |
| Microcontroller | PIC16F877A |
| Motor Driver | L293D |
| Programming Language | Embedded C |
| Programming Environment | MPLAB |
| Circuit Design and Simulation | Proteus 8 Professional |
| Hardware Implementation | Breadboard Prototype |
| Project Category | Embedded Systems and Microcontroller Applications |

---

**Technical Areas:** Embedded Systems · PIC Microcontrollers · Embedded C · MPLAB · Proteus · Keypad Interfacing · LCD Interfacing · DC Motor Control · Security Systems · Hardware Prototyping
