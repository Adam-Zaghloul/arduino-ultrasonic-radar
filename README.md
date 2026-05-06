# Arduino Ultrasonic Radar & Motor Control Demo

> HC-SR04 radar with live Web Serial HTML interface · Threat-level audio alerts · L298N DC motor control demo  
> **La Cité collégiale — Arduino / STEM Outreach · 2025–2026**

---

## Wiring Diagram

![Tinkercad Wiring](Radar_Arduino_Simple.png)

---

## Overview

Two Arduino projects built for educational and STEM outreach purposes:

1. **HC-SR04 Ultrasonic Radar** — A real-time radar display running in the browser via the **Web Serial API**, receiving live distance + angle data from an Arduino Uno driving an HC-SR04 sensor on a servo. Includes three-tier audio alerting (Attention / Danger / Critical).

2. **L298N DC Motor Control Demo** — A multi-mode motor demonstration sketch showcasing step response, pulse mode, smooth ramping (oscillation), and direction reversal — used to demonstrate PWM motor control concepts.

---

## Project 1 — HC-SR04 Ultrasonic Radar

### Hardware

| Component | Part | Connection |
|-----------|------|------------|
| Microcontroller | Arduino Uno R3 | — |
| Ultrasonic sensor | HC-SR04 | TRIG → D9, ECHO → D10 |
| Servo motor | Standard servo | Signal → D6 |
| Power | USB / 5V | VCC, GND |

### How It Works

```
[Arduino Uno]
  ├── Servo sweeps 0° → 180° → 0° continuously
  ├── At each angle: HC-SR04 fires TRIG pulse → measures ECHO duration
  ├── Distance = (duration × 0.034) / 2  [cm]
  └── Sends "angle,distance\n" over Serial (9600 baud)

[Browser — Web Serial API]
  ├── Connects to Arduino COM port directly (no drivers needed)
  ├── Parses incoming "angle,distance" lines
  ├── Draws live radar sweep on HTML5 Canvas
  └── Triggers audio alerts based on distance thresholds
```

### Live Radar Interface (`radar_live.html`)

A single self-contained HTML file — open in Chrome/Edge, click **CONNECT**, select the Arduino port.

**Features:**
- 🟢 Military-style green-on-black radar display with scan sweep animation
- 📡 Real-time distance plotting at correct polar coordinates
- 🔊 Three-tier audio alert system:

| Alert | Trigger | Sound File |
|-------|---------|-----------|
| **ATTENTION** | Object detected 50–100 cm | `attention.mp3` |
| **DANGER** | Object detected 20–50 cm | `danger.mp3` |
| **CRITICAL** | Object detected < 20 cm | `dangerS.mp3` |

- 📊 Live readout panel: current angle, distance, status
- 🔌 Web Serial connect/disconnect button with status pill (connected / disconnected / error)
- CRT scanline overlay for aesthetic fidelity

**Interface Stack:**
- HTML5 Canvas (radar sweep rendering)
- Web Serial API (direct browser ↔ Arduino communication)
- Web Audio API (alert sound playback)
- Orbitron + Share Tech Mono fonts (military HUD aesthetic)
- Zero dependencies — pure HTML/CSS/JS, no frameworks

### Running the Radar

1. Upload `final.ino` to the Arduino Uno
2. Connect Arduino via USB
3. Open `radar_live.html` in **Chrome or Edge** (Web Serial requires Chromium)
4. Click **CONNECT** → select the Arduino COM port
5. The radar display starts immediately

> Web Serial API is supported in Chrome 89+ and Edge 89+. Firefox is not supported.

### Arduino Sketch (`final.ino`)

The sketch continuously sweeps the servo from 0° to 180° and back. At each degree increment, it fires the HC-SR04 and sends the result over Serial:

```
Serial output format:  "angle,distance\n"
Example:               "45,87\n"   → 45 degrees, 87 cm
Baud rate:             9600
```

---

## Project 2 — L298N DC Motor Control Demo

### Hardware

| Component | Part | Connection |
|-----------|------|------------|
| Microcontroller | Arduino Uno R3 | — |
| Motor driver | L298N | ENA → D9 (PWM), IN1 → D7, IN2 → D8 |
| DC Motor | Any 5–12 V DC motor | Motor A output of L298N |

### Demo Modes (loop sequence)

The sketch cycles through four demonstration modes automatically:

#### 1. Step Response Demo
```
0%   → stop     (1 sec)
25%  → 64/255   (1.5 sec)
50%  → 128/255  (1.5 sec)
75%  → 191/255  (1.5 sec)
100% → 255/255  (1.5 sec)
STOP            (1 sec)
```

#### 2. Pulse Demo
5 rapid on/off bursts at full speed (300 ms on / 300 ms off) — demonstrates PWM duty cycle control at the driver level.

#### 3. Oscillate Demo
Smooth ramp forward (0→255→0) then reverse (0→255→0), repeated 3 times — demonstrates bidirectional speed ramping.

#### 4. Reverse Demo
Ramp forward to 200 → stop → ramp reverse to 200 → stop — demonstrates direction reversal with a controlled ramp to avoid current spikes.

### Key Functions

```cpp
motorForward(int spd)               // IN1=HIGH, IN2=LOW, ENA=spd
motorReverse(int spd)               // IN1=LOW,  IN2=HIGH, ENA=spd
motorStop()                         // IN1=LOW,  IN2=LOW,  ENA=0
smoothRamp(bool fwd, int from, int to, int stepDelay)  // linear speed ramp
```

All mode transitions are logged to **Serial Monitor** (9600 baud) for real-time visibility.

---

## Files in This Repository

| File | Description |
|------|-------------|
| `final.ino` | Arduino sketch — servo sweep + HC-SR04 distance measurement + Serial output |
| `radar_live.html` | Browser radar display — Web Serial, canvas radar, audio alerts |
| `attention.mp3` | Alert audio — object at 50–100 cm |
| `danger.mp3` | Alert audio — object at 20–50 cm |
| `dangerS.mp3` | Alert audio — object < 20 cm (critical) |
| `motor_control_enhanced.ino` | L298N DC motor demo — step, pulse, oscillate, reverse modes |
| `Radar_Arduino_Simple.png` | Tinkercad wiring diagram |

---

## Skills Demonstrated

`HC-SR04 ultrasonic sensor` `Servo control` `Arduino Serial communication` `Web Serial API` `HTML5 Canvas` `JavaScript` `Web Audio API` `PWM motor control` `L298N motor driver` `Bidirectional DC motor` `STEM outreach` `Embedded C/C++`

---

*Adam Zaghloul · La Cité collégiale · 2025–2026 · [adamzaghloul07@gmail.com](mailto:adamzaghloul07@gmail.com)*
