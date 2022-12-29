#Scale for Measuring Carbs

1. Features
2. Materials
3. To Do
4. Updates
5. Notes
6. References
---

## 1 Features

#### v1.0
- Weigh food to display carbs
- Add/Remove/Update foods via web interface
- Rechargable battery
- Deep Sleep / Wake on touch

---

## 2 Materials

- ESP32
- LCD Display
- 3D Printed case/enclosure
- Rotary encoder
- Tactile buttons (Temporary?)
- MPR121 capacitive buttons (Easy clean front)
- 3x18650 Battery Pack
- Strain gauge load cell
- HX711 24-bit ADC
- TP4056 Lipo charger

---

## 3 To Do

- [ ] **HARDWARE:** Wire up and test LCD
- [ ] **HARDWARE:** Wire up and test rotary encoder
- [x] **CODE:** Create github repo
- [x] **CODE:** Create and test Arduino project
- [ ] **CODE:** Connect ESP32 to Wifi
- [ ] **CODE:** Setup webserver
- [ ] **CODE:** Design web interface
- [ ] **CODE:** Add Calibration functions
- [ ] **CODE:** Add Tare function
- [ ] **CODE:** Read ADC Val
- [ ] **CODE:** Display Foods for user to select
- [ ] **CODE:** Prompt User to select food
- [ ] **3D Print:** Deisgn 3D prited enclosure
- [ ] **3D Print:** Design/Add Load Cell model to Project
- [ ] **3D Print:** Design/Add LCD model to Project
- [ ] **3D Print:** Design/Add ESP32 model to Project
- [ ] **3D Print:** Design/Add Rotary encoder model to Project
- [ ] **3D Print:** Design/Add Load Cell model to Project
- [ ] **3D Print:** Design/Add Momentary switch model to Project
- [ ] **HARDWARE:** Layout breadboard circuit

---

## 4 Updates

### 12/28/22
Began project in ernest. Doing it "right" this time by starting with a written plan (this markdown file) instead of jumping right in with hardware and adding code as neeeded. Hopefully a well thought out plan will keep me from acruing tiny mistakes and inefficiencies over time that will eventually turn into road blocks and points of stress down and make me not want to continue with the project. 

---

## 5 Notes

- Foods
  - List of foods should be stored as a CSV.
  - For now we're not going to worry about classifying the foods as breakfast, lunch, snack, etc.