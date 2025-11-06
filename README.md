# ♻️ ESP32 Waste Sorter Project

An automated **smart waste sorting system** using an **ESP32 microcontroller**, and servo motors etc.  
The project detects and classifies waste items (e.g., plastic, cardboard, paper) and sorts them into separate bins automatically.

---

## 📂 Project Files

| File | Description |
|------|--------------|
| **ESP32WSCOM.ino** | Main code handling wireless communication (Serial COM). |
| **esp32_camera3_copy.ino** | Code for the ESP32-CAM module to capture and process images. |
| **Waste Sorter Schematic.png** | Circuit schematic showing connections between the OLED, servos, and ESP32. |
| **Bin** | Setup image or system screenshot. |
| **ei-waste-sorter-1-arduino-1.0.1.zip** | Edge Impulse / model file for waste detection AI. |
| **README.md** | Project documentation file (this file). |

---

## 🧠 Features

- Automatic waste sorting using **image recognition**
- Built on the **ESP32** platform
- Uses **servo motors** for bin movement
- Optional **camera support** with ESP32-CAM
- Can communicate data over **ESP32-NOW One-Way Communication**

---

## 🧩 Components Used

- ESP32 or ESP32-CAM
- OLED
- LEDs and resistors
- Servo motor(s)
- Power supply; four 1.5V Li-ion batteries
- Jumper wires and breadboard
- AI model from Edge Impulse

---

## Bin & Schematic

_Add images or GIFs of the project in action here._  
<img width="737" height="710" alt="Waste S" src="https://github.com/user-attachments/assets/22fd9875-1c5c-4767-915b-ad1dfd032dd8" />
<img width="1536" height="1024" alt="Waste Sorter Schematic" src="https://github.com/user-attachments/assets/1175480d-80f5-4ae9-ac87-6dadeb93415f" />

---

## ⚙️ How It Works

1. The ESP32-CAM  detects an object placed in front of it, whethe it is a waste matrial of plastic, paper or cardboard. 
2. The system classifies the object using: 
   - Image recognition (via ESP32-CAM + Edge Impulse model).  
3. The servo opens the lid to direct the object to the correct bin.  
4. Data can be displayed via the OLED.

---

## 🧪 Setup & Usage

1. Clone or download this repository:
   ```bash
   git clone https://github.com/<your-username>/<your-repo-name>.git
