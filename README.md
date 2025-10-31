# Smart Luas Entrance Density Estimation System

A real-time, privacy-preserving system for estimating crowd density at Luas tram entrances using ultrasonic sensors, an ESP32, and a Raspberry Pi backend. Results are displayed on a web dashboard for visualizing crowd levels at each entrance.

---

## Overview

This project provides a low-cost, non-invasive alternative to camera-based monitoring. It estimates relative crowd density using ultrasonic sensors that feed processed data through an ESP32 to a FastAPI backend and web dashboard.

**Data Flow:**

```
Ultrasonic Sensors → ESP32 → Raspberry Pi (FastAPI) → Web Dashboard
```

---

## System Architecture

| Component    | Role                                                                      |
| ------------ | ------------------------------------------------------------------------- |
| ESP32        | Reads and filters sensor data, classifies crowd level, sends JSON packets |
| Raspberry Pi | Receives and stores readings in SQLite, serves FastAPI endpoints          |
| Frontend     | Displays live density visualization with auto-refresh                     |

---

## License

Licensed under the [MIT License](./LICENSE).
© 2025 Glenks123
