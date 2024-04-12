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

Terminal 2:
```
cd ModuleIMU
get_idf
idf.py flash monitor
```

When the output on Terminal 2 is `MAIN: . . .` kill the command in Terminal 1 using `Ctrl + C` and Terminal 2 using `Ctrl + ]`

## Generation of data.csv
Terminal 1:
```
python3 data_parser.py
```
This will generate the data.csv which will be our data for the ML model.




