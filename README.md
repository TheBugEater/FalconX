# FalconX
### A Cross Platform Flight Controller - ( In Development for ESP32 )

Currently in a Development State and This Branch isn't stable.

<b>Goals For the First Release:</b>
- [ ] Framework
    - [ ] Implement a Factory System to Create/Destroy Modules and Drivers.
    - [ ] Replace all hard coded platform specific classes with interfaces.
- [ ] Modules
    - [X] Gyro Module should retrieve the accurate angle without drifting.
    - [X] WiFi Module to report the connection status to engine.
    - [ ] Altitude Module needs to be integrated
- [ ] Drivers
    - [ ] I2C Driver for ESP32 is hard coded to use in master mode. This should be flexible.
    - [X] BLDC Driver for ESP32 doesn't seem to generate the correct PWM signals. This should be fixed.
- [ ] Flight Controller
    - [ ] Implement a State Machine to Control the flight status. 
    - [X] BLDC Startup Routine.
    - [X] Drive Motors at a Specific Speed
    - [ ] Altitude Hold
    - [X] Self Balance with Gyro's Angle Values
    - [X] Connect to the Mobile Unity App via UDP
  
A Long way to go before I reach these goals, But This list helps me focus on one goal at a time and clear it.
