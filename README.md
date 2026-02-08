# Smart Library Seat Management System

This project presents a Smart Library Seat Management System designed to prevent false seat reservations and improve fair seat usage in libraries.

## Features
- Detects real occupancy using **FSR (Force Sensor)** and **IR sensor**
- Identifies:
  - **Occupied seat** → Red LED  
  - **Reserved seat** → Yellow LED with 20-minute timer  
  - **Available seat** → Green LED  
- Automatically releases unattended reserved seats after **20 minutes**
- Displays **total vs available seats** on an **LCD screen**
- Real-time monitoring using **ESP32**

## Components Used
- ESP32 microcontroller  
- Force Sensor (FSR)  
- IR sensor  
- LEDs (Red, Yellow, Green)  
- LCD display  
- Connecting wires & power supply  

## Working Principle
The FSR detects weight on the seat while the IR sensor confirms human presence.  
If both are active, the seat is marked **Occupied**.  
If only weight is detected, the seat becomes **Reserved** and a 20-minute timer starts.  
If the user does not return within the time limit, the system automatically marks the seat **Available**.

## Applications
- College and public libraries  
- Study halls  
- Reading rooms  
- Shared seating environments  

## Future Scope
- Mobile app for live seat availability  
- Online reservation system  
- Cloud data storage & analytics  
- Integration with student ID authentication  

---

**Developed as an Embedded Systems project using ESP32.**

## Project Preview

![Simulation](project.png)

