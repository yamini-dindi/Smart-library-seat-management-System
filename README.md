# Smart Library Seat Management System

This project presents a Smart Library Seat Management System designed to prevent false seat reservations and ensure fair seat usage in libraries.

## Features
- Detects real occupancy using **Potentiometer (weight simulation)** and **PIR motion sensor**
- Identifies:
  - **Occupied seat** → Red LED  
  - **Reserved seat** → Yellow LED with 20-minute timer  
  - **Available seat** → Green LED  
- Automatically releases unattended reserved seats after **20 minutes**
- Displays **total vs available seats** on an **LCD screen**
- Real-time monitoring using **ESP32**
## Wokwi Simulation

You can view and run the project simulation here:  
https://wokwi.com/projects/450140854688312321

## Components Used
- ESP32 microcontroller  
- PIR motion sensor  
- Potentiometer (used to simulate force/weight detection)  
- LEDs (Red, Yellow, Green)  
- LCD display  
- Connecting wires & power supply  

## Working Principle
The potentiometer simulates the presence of weight on a seat, while the PIR sensor detects human motion.  
If both signals are active, the seat is marked **Occupied**.  
If only weight is detected, the seat becomes **Reserved** and a 20-minute timer starts.  
If the user does not return within the time limit, the system automatically marks the seat **Available**.

## Applications
- College and public libraries  
- Study halls and reading rooms  
- Shared seating environments  

## Future Scope
- Mobile app for live seat availability  
- Online reservation system  
- Cloud data storage and analytics  
- Integration with student ID authentication  

---

**Developed as an Embedded Systems project using ESP32.**


## Project Preview

![Simulation](project.png)

