# Detection Capture Vision (MDS)

**Detection Capture Vision (Motion Detection System - MDS)** is a real-time desktop surveillance and motion detection application built with C++/CLI (Windows Forms) and OpenCV. The system monitors live webcam feeds, allows users to define custom Regions of Interest (ROI), and automatically captures and logs snapshots whenever movement is detected within the designated zone.

---

## Key Features

- **Real-Time Webcam Monitoring:** Streams and processes live video feeds smoothly within a Windows Forms GUI.
- **Interactive ROI Selection:** Allows users to draw and customize a specific Region of Interest (ROI) directly on the camera feed using the mouse for targeted surveillance.
- **Computer Vision Motion Pipeline:**
  - **Grayscale Conversion & Gaussian Blur:** Reduces noise and prepares frames for accurate comparison.
  - **Frame Differencing (`absdiff`) & Thresholding:** Calculates pixel intensity changes between consecutive frames to isolate moving objects.
  - **Contour Detection:** Identifies and highlights active movement boundaries in real time.
- **Automated Snapshot & Event Logging:** Features a dedicated Log Form that automatically captures, timestamps, and saves image snapshots whenever unauthorized movement occurs inside the ROI.

---

## Project Structure

```text
detection-capture-vision/
├── MDS/                     # Main C++/CLI source files, Windows Forms UI, and headers
├── MDS.slnx                 # Visual Studio XML Solution file
├── .gitattributes           # Git attributes configuration
├── .gitignore               # Git ignore rules for Visual Studio build artifacts
└── LICENSE                  # Project license information
```

---

## Tech Stack & Requirements

- **Language & Framework:** C++/CLI (.NET Windows Forms)
- **Computer Vision Library:** OpenCV
- **IDE:** Visual Studio (supports `.slnx` solution format)
- **OS:** Windows 10 / 11

---

## Getting Started

### Prerequisites
1. Install **Visual Studio** with the **Desktop development with C++** workload and **C++/CLI support for v143 build tools**.
2. Install **OpenCV** on your machine and configure the system environment variables (or update the Include/Library directories in the project properties).

### Running the Project
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/JULHMSPLOY/detection-capture-vision.git](https://github.com/JULHMSPLOY/detection-capture-vision.git)
   ```
2. Open **`MDS.slnx`** in Visual Studio.
3. Set the solution configuration to **Release** or **Debug** (x64) and ensure OpenCV `.dll` files are accessible in your system `PATH` or output directory.
4. Press `F5` (or click **Start**) to build and run the application.

---

## How to Use

1. **Start Camera:** Launch the application and connect to your active webcam feed on the main Monitor Form.
2. **Select ROI:** Click and drag on the video feed to draw a bounding box around the area you want to monitor.
3. **Monitor & Log:** When motion is detected inside the ROI, the system will trigger an alert, save a snapshot of the frame, and record the event in the Log window.

---

## License

[![CC BY-NC 4.0](https://img.shields.io/badge/License-CC%20BY--NC%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc/4.0/)

This project is licensed under the **[Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0)](https://creativecommons.org/licenses/by-nc/4.0/)** — see the [LICENSE](LICENSE) file for full details.
