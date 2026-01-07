# BMA-01 — BubbaMachina Arm 01

**BMA-01** is a small experimental **2-DOF robotic arm project** focused on learning and demonstrating **inverse kinematics (IK)**, embedded control, and browser-based visualization.

The system uses an **ESP32 programmed via the Arduino IDE** to host a **Wi-Fi–based JavaScript web interface**, allowing real-time simulation of the arm’s movement.

---

## 🚀 Project Overview

- 2 Degrees of Freedom (planar robotic arm)
- Inverse Kinematics–based motion simulation
- ESP32 acts as:
  - Wi-Fi access point / web server
  - Interface between UI and kinematics logic
- Browser-based **JavaScript visualization**
- Designed for learning, prototyping, and experimentation

---

Watch a demonstration:
👉 [https://youtu.be/-KhcPkbhVoQ](https://youtube.com/shorts/BYGnF4vTOc4)

## 🧠 Core Concepts

- Forward and Inverse Kinematics (2DOF planar arm)
- Embedded web servers on microcontrollers
- ESP32 + Arduino IDE development workflow
- Real-time interaction via Wi-Fi
- Modular separation of:
  - Kinematics logic
  - Visualization
  - Hardware control (future)

---

## 🧩 System Architecture

[ Browser (JavaScript Web UI) ]
↓ Wi-Fi
[ ESP32 Web Server ]
↓
[ IK Computation Logic ]
↓
[ Arm State / Simulation ]


> ⚠️ Current version focuses on **simulation and kinematics logic**.  
> Physical motor control is planned for future versions.

---

## 🛠️ Hardware

- ESP32 development board

**Optional / Future:**
- Servo motors
- 3D-printed 2DOF robotic arm
- External power supply

---

## 💻 Software Stack

- Arduino IDE
- ESP32 Arduino Core
- HTML / CSS / JavaScript
- Basic trigonometry for inverse kinematics

---

## 📡 Features

- Wi-Fi–hosted control and visualization page
- JavaScript-based arm simulation
- User-defined target position
- Inverse kinematics computation on the ESP32
- Expandable architecture for:
  - Additional DOF
  - Physical actuation
  - Trajectory planning
  - External control (e.g. ROS)

---

## 🧪 Project Status

- ✅ ESP32 Wi-Fi server
- ✅ Browser-based UI
- ✅ 2DOF inverse kinematics
- 🚧 Physical arm integration
- 🚧 Code cleanup and documentation

---

## 🎯 Project Goals

- Build intuition for robotic kinematics
- Combine embedded systems with web technologies
- Create a reusable robotics learning platform
- Serve as a foundation for more advanced robotic arms

---

## 📄 License

MIT License — free to use, modify, and build upon.

---

## ✨ Name

**BMA-01**  
*BubbaMachina Arm — Revision 01*
