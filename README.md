# Agribot for Precision Agriculture 🌱🤖

### Project Overview
Agribot is a cutting-edge robotic solution designed for precision agriculture, specifically for weed management. It autonomously navigates through agricultural fields, detects weeds among crops using a **computer vision** system, and eliminates them using a **laser**. The system leverages a **machine learning** model trained on real field data to enhance weed detection accuracy.

This project was developed as part of my graduation project at **Cairo University** and received an **A grade** for its innovative design and practical implementation.

### Key Features
- **Autonomous Navigation**: The robot autonomously navigates agricultural fields using **LiDAR** and **SLAM** techniques.
- **Computer Vision for Weed Detection**: A machine learning model, trained on real-world field data, identifies and distinguishes weeds from crops.
- **Laser Elimination**: Once weeds are identified, the robot eliminates them using a **laser system**.
- **Real-time Robot Control**: The robot's movements are controlled using **ROS nodes** with real-time feedback for navigation and actuation.

### Hardware Components
- **Raspberry Pi**: Acts as the brain of the robot, handling processing and communication.
- **Arduino**: Used for interfacing with various hardware components.
- **LiDAR Sensor**: For obstacle detection and environment mapping.
- **Cytron Motor Driver**: Controls the robot's motors with precise movement control.
- **Encoders**: Provide feedback for accurate distance and speed calculations.
- **PCB**: Custom-designed and soldered to manage hardware connections.
- **Suspension System**: Designed to ensure smooth operation in uneven terrain.

### Software Architecture
- **ROS (Robot Operating System)**: Used for handling robot control, communication between nodes, and sensor integration.
  - **C++ ROS Nodes**: Written to control robot movement using kinematics and **PID** equations.
  - **Python ROS Node**: Allows manual robot control via keyboard inputs.
- **Gazebo & RViz**: Simulated environments for testing and developing navigation algorithms.
- **rqt_reconfigure & Matplotlib**: Created a GUI for real-time PID tuning.
- **SLAM (Simultaneous Localization and Mapping)**: Applied in both simulation and real-world scenarios to enable navigation in unknown environments.

### Key Contributions
- **Navigation and Control Algorithms**: Developed the autonomous navigation algorithms and implemented the **PID controller** for precise movement.
- **Hardware Design**: 
  - Connected the Raspberry Pi to LiDAR, and Arduino to other hardware components.
  - Soldered and welded a custom PCB.
  - Designed motor and encoder brackets, as well as the suspension system.
- **Software Development**:
  - Wrote ROS nodes to control robot movement in **Gazebo** and real-world environments.
  - Developed drivers for the **Cytron motor driver** and encoders.
  - Created a local network over WiFi to connect the Raspberry Pi with the master machine.
  - Applied SLAM and created navigation algorithms for real-time field operation.
  
### Achievements
- Represented **Cairo University** at the **ITC-EGYPT ADC 2024**, hosted by the **Egyptian Military Academy**.
- Gained recognition from **Al-Ahram Establishment**, **Middle East News Agency (MENA)**, and **UNESCO's Future Builders Club** for the project.
- Received an **A grade** for the project.

### Special Thanks
A special thanks to:
- **Dr. Abd El Fattah** for his continuous supervision and guidance.
- **Mr. Walid Diab** for his invaluable help in bringing Agribot to life.
- My teammate **Bahga Mohammed** for her great contribution and collaboration throughout this journey.

### How to Run the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/username/agribot.git
   ```
2. Install ROS and necessary dependencies:
   ```bash
   sudo apt-get install ros-noetic-desktop-full
   ```
3. Build the ROS workspace:
   ```bash
   cd catkin_ws
   catkin_make
   ```
4. Run the simulation in **Gazebo**:
   ```bash
   roslaunch agribot_simulation agribot_world.launch
   ```
5. For real-world deployment:
   - Connect the hardware components as specified in the hardware section.
   - Run the navigation and control nodes:
     ```bash
     roslaunch agribot_control agribot_navigation.launch
     ```

### Future Improvements
- **Enhanced Weed Detection**: Further training of the machine learning model on more diverse datasets for higher accuracy.
- **Expanded Field Tests**: More testing in varied agricultural conditions to improve the robustness of navigation and control systems.
- **Solar Power Integration**: Explore integrating solar power to make the robot energy-independent for long-term field deployment.

### Contact
For more details about the project or collaboration opportunities, feel free to connect with me, **Mohamed Newir**, via [LinkedIn](https://www.linkedin.com/in/mohamed-newir-a8a572182?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app).
