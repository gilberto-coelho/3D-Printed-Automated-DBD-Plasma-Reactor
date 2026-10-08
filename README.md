# 3D-Printed Automated DBD Plasma Reactor

A custom **3D-printed automation system** developed for a laboratory-built **Dielectric Barrier Discharge (DBD) plasma reactor**, used in plasma-mediated vapor generation (PMVG) coupled to atomic absorption spectrometry (AAS).

The system integrates a **servo-actuated sample sealing mechanism**, **contactless infrared temperature monitoring**, and **Arduino-based control** to automate plasma operation, minimize mercury vapor losses, and improve analytical workflow.

The complete system, including **3D mechanical design, fabrication, electronics integration, Arduino programming, and automation**, was developed and implemented by me.

**Development:** 2024  
**Microcontroller:** Arduino Uno (ATmega328P)  
**Mechanical design:** Custom 3D-printed assembly  
**Programming:** Arduino C/C++  
**Application:** Automated PMVG-AAS instrumentation

**Complete automated DBD reactor:**

<img width="1330" height="1481" alt="Automated DBD plasma reactor" src="https://github.com/user-attachments/assets/5cc49c08-a85c-4b6b-951c-77c2ff6d2448" />

<br>

## Overview

The project was developed to address two main challenges in DBD operation:

1. **Sample sealing:** liquid samples were manually introduced through a small opening in the quartz reactor, which needed to be sealed immediately to prevent analyte vapor losses during argon flow.
2. **Temperature monitoring:** conventional metallic temperature probes could cause unwanted electrical discharges near the high-voltage electrodes.

A compact 3D-printed assembly was designed to integrate the quartz reactor, MG90S servo motor, MLX90614 infrared thermometer, Arduino Uno, LCD, and electronic controls.

The resulting system provides:

- Automated sample inlet sealing using a servo motor and polyimide tape
- Contactless temperature measurement through an infrared sensor
- Automatic high-voltage power supply switching
- Optoelectronic isolation between the Arduino and power supply
- Real-time temperature and elapsed-time display on a 16×2 LCD
- Audible notifications for measurement completion and reactor cooling
- Servo calibration with EEPROM storage
- Push-button control and serial data output

<br>

## System Architecture

The **Arduino Uno** coordinates the mechanical movement, sensor acquisition, plasma switching, and user notifications.

```text
                     ┌──────────────────────┐
                     │      Arduino Uno     │
                     │       ATmega328P     │
                     └──────────┬───────────┘
                                │
         ┌──────────────────────┼──────────────────────┬───────────────────────┐
         │                      │                      │                       |
         ▼                      ▼                      ▼                       ▼
 ┌────────────────┐    ┌────────────────┐    ┌────────────────┐    ┌───────────────────────┐
 │   MG90S Servo  │    │    MLX90614    │    │    16×2 LCD    │    │ LED / Phototransistor │
 │                │    │    IR Sensor   │    │   I2C Display  │    │  Switching Interface  │
 │  Sealing Arm   │    │                │    │                │    └───────────────────────┘ 
 └────────────────┘    │  Temperature   │    │   Monitoring   │                │
                       └────────────────┘    └────────────────┘                ▼
                                                                   ┌──────────────────────┐
                                                                   │  High-Voltage Power  │
                                                                   │        Supply        │
                                                                   └──────────┬───────────┘
                                                                              │
                                                                              ▼
                                                                   ┌──────────────────────┐
                                                                   │      DBD Plasma      │
                                                                   └──────────────────────┘                     
```

<br>

## 3D Mechanical Design

A custom **3D-printed holder** was designed around the quartz reactor geometry to integrate the mechanical and electronic components into a compact assembly.

The structure accommodates the tubular quartz reactor, MG90S servo motor, movable sealing arm, polyimide tape, MLX90614 infrared sensor, Arduino Uno, 16×2 LCD, push-button, and buzzer.

Particular attention was given to **alignment of the sealing arm with the sample introduction opening** and positioning of the infrared sensor beneath the reactor.

### 3D CAD Model

**Complete CAD assembly:**

<img width="3744" height="1943" alt="Complete CAD assembly" src="https://github.com/user-attachments/assets/41563477-563b-4f85-8885-6edb4974fdb9" />

<br>
<br>

**3D-printed components:**

<table>
  <tr>
    <td width="50%">
      <img width="100%" alt="3D-printed components" src="https://github.com/user-attachments/assets/55488927-55ad-4e46-bccd-0445445c8c46" />
    </td>
    <td width="50%">
      <img width="100%" alt="Assembled 3D-printed components" src="https://github.com/user-attachments/assets/522bac59-c219-4acf-96d7-758c3bc05bd3" />
    </td>
  </tr>
</table>

<br>
<br>

## Servo-Actuated Sample Sealing Mechanism

A **MG90S servo motor** controls a movable arm that automatically seals the **2 mm sample introduction opening** in the quartz reactor.

- **Open position:** allows manual sample introduction using a micropipette.
- **Closed position:** presses the sealing surface against the reactor opening, minimizing argon leakage and mercury vapor losses.

The arm remains closed during plasma operation and subsequent cooling.

### Polyimide Tape Selection

**Polyimide tape** was wrapped around the sealing arm to provide a flexible contact surface compatible with the elevated temperatures and electrical environment of the DBD reactor.

The tape enables repeated opening and closing while maintaining the gas flow path. It was also used to cover the external copper electrodes, helping prevent unwanted electrical discharges through the surrounding air.

### Servo Calibration

The sealing position can be adjusted through the Arduino's push-button interface and stored in **EEPROM**, preserving the calibration after power-off.

The firmware uses servo `attach()` and `detach()` commands to avoid continuously driving the motor when movement is unnecessary.

**Sealing mechanism details:**

<img width="809" height="679" alt="Servo-actuated sealing mechanism" src="https://github.com/user-attachments/assets/3ffd805f-d8e3-44e4-8d7b-0a7fb517ffdf" />

<br>
<br>

## Contactless Temperature Monitoring

A **MLX90614 GY-906 infrared thermometer** was installed beneath the central region of the quartz reactor to measure temperature without physical contact.

This approach avoids the risk of external electrical discharges associated with metallic thermocouples near the high-voltage electrodes.

Temperature measurements are acquired through **I2C communication**, displayed on the LCD, transmitted via serial communication, and used to trigger an audible notification when the reactor reaches a predefined cooling threshold.

**Infrared sensor positioning:**

<img width="579" height="580" alt="Infrared sensor positioning" src="https://github.com/user-attachments/assets/daeccf95-ec1a-4c28-807c-d0794dee6045" />

<br>
<br>

**Temperature monitoring using argon or helium as discharge gas:**

<table>
  <tr>
    <td width="50%">
      <img width="100%" alt="Reactor temperature monitoring" src="https://github.com/user-attachments/assets/831fff3c-87e6-4272-a0f5-b8168387111e" />
    </td>
    <td width="50%">
      <img width="100%" alt="Temperature profiles" src="https://github.com/user-attachments/assets/367735dc-d5ae-41be-9218-58b98adce6f7" />
    </td>
  </tr>
</table>

<br>
<br>

## Automated Operation

The Arduino coordinates sample sealing, plasma switching, temperature monitoring, and audible notifications throughout the analytical procedure.

```text
Reactor ready (low temperature)
      ↓
Servo opens → Manual sample introduction
      ↓
Servo closes and seals the reactor
      ↓
Spectrometer acquisition begins
      ↓
High-voltage power supply ON
      ↓
DBD plasma → Mercury vapor generation and detection
      ↓
High-voltage power supply OFF
      ↓
Buzzer signals measurement completion
      ↓
Reactor cooling + Temperature monitoring
      ↓
Cooling threshold reached → Buzzer notification
      ↓
Ready for the next measurement
```

### Cooling Notification

After plasma operation, the Arduino continuously monitors the reactor temperature and activates a **buzzer** when the predefined cooling threshold is reached, notifying the operator that the reactor has cooled sufficiently.

In the provided firmware version, the threshold is **40 °C**, and the cooling notification is enabled only after the reactor temperature has first reached at least **100 °C**.

The buzzer also signals the completion of the programmed plasma operation time, reducing the need for continuous manual observation.

<br>

## High-Voltage Power Supply Integration

The reactor was connected to a **laboratory-built high-voltage power supply**, developed and assembled by me.

### Optoelectronic Switching

An **infrared LED and phototransistor interface** enables Arduino-controlled switching of the high-voltage power supply without a direct electrical connection between the control signal and the switching circuit.

This allows plasma activation and deactivation to be synchronized with the automated analytical procedure.

**Power supply schematic:**

<img width="970" height="731" alt="High-voltage power supply schematic" src="https://github.com/user-attachments/assets/4b6da56b-1578-44f5-aa87-09a2ce840a2c" />

<br>
<br>

For additional information about the electronic design, transformers, and development of these power supplies, see my related repository in GitHub:

**[High-Voltage Power Supplies for DBD Plasma](https://github.com/gilberto-coelho/High-Voltage-Power-Supplies-for-DBD-Plasma)**

<br>

## Internal Hardware

The Arduino, servo motor, infrared sensor, LCD, buzzer, push-button, and power supply switching interface were integrated into the 3D-printed assembly.

**Internal electronics and wiring:**

<img width="1133" height="766" alt="Internal electronics and wiring" src="https://github.com/user-attachments/assets/ac43954e-0b82-4ec7-85c9-0aae532bc2f9" />

<br>
<br>

### Arduino Connections

| Component | Arduino Pin | Function |
|---|---|---|
| MG90S servo motor | D9 | Sample inlet sealing |
| Buzzer | D5 | Audible notifications |
| High-voltage switching interface | D4 | Plasma ON/OFF control |
| Push-button | D7 | Operation and configuration |
| MLX90614 IR sensor | SDA (A4), SCL (A5) | Temperature monitoring |
| 16×2 LCD (I2C) | SDA (A4), SCL (A5) | Display and user interface |

The LCD (`0x27`) and MLX90614 share the **I2C bus**, while the push-button uses the Arduino's internal pull-up resistor (`INPUT_PULLUP`).

<br>

##Power Supply and Voltage Regulation

The entire system was powered by a 12 V / 2 A external power supply, connected directly to the Arduino Uno through its DC jack connector.

Since the Arduino Uno's onboard 5 V regulator cannot reliably supply the current required by the MG90S servo motor, a separate LM7805 linear voltage regulator was used to convert the 12 V input into 5 V for the servo.

This configuration provides:

- 12 V input: external power supply connected to the Arduino Uno.

- 5 V regulated output: LM7805 supplying the servo motor independently.

Common ground: Arduino, LM7805, and servo motor sharing the same GND reference.

Important: Do not power the servo motor directly from the Arduino Uno's 5 V pin. Servo motors can draw relatively high current, especially during startup or under mechanical load, potentially causing voltage drops, unexpected Arduino resets, or overheating of the onboard regulator.

<br>

## Firmware Development

The automation firmware was developed in **Arduino C/C++** for the ATmega328P microcontroller.

Its main features include:

- **Automated control:** coordination of the servo and plasma power supply.
- **Temperature acquisition:** MLX90614 measurements through I2C.
- **Servo calibration:** push-button adjustment with EEPROM storage.
- **Timed operation:** automatic plasma shutdown after **140 seconds** in the provided firmware.
- **Buzzer notifications:** measurement completion and cooling alerts.
- **LCD interface:** temperature, elapsed time, and configuration display.
- **Serial communication:** temperature and elapsed-time output at **9600 baud**.
- **Manual interruption:** push-button control to stop plasma operation.

The firmware uses the `Wire`, `LiquidCrystal_I2C`, `Servo`, `EEPROM`, and `Adafruit_MLX90614` libraries.

**Firmware:** [code.ino](code.ino)

<br>

## Operation Demonstration

**Plasma reactor operating with a liquid sample (without the automated system for better visualization):**

https://github.com/user-attachments/assets/d942ff1e-d814-4204-b4f6-3eddafce1815

<br>
<br>

**Servo-controlled opening and closing of the sample inlet:**

https://github.com/user-attachments/assets/96c73c88-e5cd-410f-9c77-6a471c6c0aa3

<br>
<br>

**Infrared camera monitoring of a similar reactor:**

https://github.com/user-attachments/assets/30fa5844-3035-44a5-a576-a9d7ddf0cf46

<br>
<br>

## Skills Demonstrated

- **3D CAD modeling and 3D printing:** custom mechanical design, fabrication, and assembly.
- **Mechanical integration:** servo-actuated mechanisms, alignment, and material selection.
- **Embedded programming:** Arduino C/C++, control logic, timers, and hardware interfacing.
- **Sensor integration:** I2C communication and infrared temperature monitoring.
- **Electronics:** servo control, LCD, buzzer, optoelectronic switching, and high-voltage system integration.
- **Data acquisition:** serial communication and temperature measurements.
- **EEPROM:** non-volatile storage of calibration parameters.
- **Laboratory automation:** integration of mechanical, electronic, and software systems.

<br>

## Research Publication

The design and application of this automated DBD system were reported in:

**Plasma-mediated mercury vapor generation after microwave-induced combustion of fish tissue with detection by atomic absorption spectrometry**

**Link:** https://doi.org/10.1016/j.sab.2024.107055

Further technical information, including the electronic schematic, component specifications, mechanical design, automation, and temperature monitoring, is available in the publication's **Supplementary Material**.

<br>

## Author

**Gilberto Coelho**  
Electronics & Automation Developer

I personally carried out the **complete development of this automation system**, including 3D CAD design, fabrication and assembly, electronic integration, Arduino firmware programming, and implementation of the automated control system.

The project was developed during my research activities in analytical chemistry.
