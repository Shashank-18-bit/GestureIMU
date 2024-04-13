# File Structure

The project contains two folders

## ModuleIMU
This folder contains the esp idf project. It will handle the following things
- [x] Interfacing of MPU6050
- [x] Sending the data acquired from MPU6050 to the host via BLE protocol

## Host
This folder contains the code that will run on the host. It will handle the following things
- [x] Parsing the data.txt which will be the dump of the data received via BLE. The dump will be generated using the hcidump tool.
- [x] Generating the data.csv which will be our data for the ML model.
- [ ] Training and running ML model on the data.

# Usage

## Clone the repo
```
git clone git@github.com:RISHI27-dot/GestureIMU.git
cd GestureIMU
```

## Sensor Data Acquisition
Connect the module to your PC and open two terminals.

Terminal 1:
```
cd Host
sudo hcidump -R > data.txt
```
After this whatever will be received from BLE will be logged in data.txt.

Terminal 2:
```
cd ModuleIMU
get_idf
idf.py flash monitor
```
These commands will signal MPU6050 will start recording gestures/end sequence and sending them to PC via BLE depending on the switch pressed.
```
/* Pseudo Code */

if (SWITCH_1 hold) {
    send gesture data
} else if (SWITCH_2 hold) {
    send end sequence
}
```

## Generation of data.csv
Terminal 1:
```
python3 parser.py
```
This will generate multiple data*.csv files according to the number of gestures found in the data.txt file.