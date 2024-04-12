# Host

## data_parser.py

This file is responsible for the following things
- Parsing the `data.txt` file to extract raw acceleration values.
- The raw acceleration values is an array of `uint8` containing 6 elements. The arrangement is as follows.
```
    MSB       LSB       MSB       LSB       MSB       LSB   
+---------+---------+---------+---------+---------+---------+
|  uint8  |  uint8  |  uint8  |  uint8  |  uint8  |  uint8  |
+---------+---------+---------+---------+---------+---------+
|___________________|___________________|___________________|
          ax                  ay                  az        
```
- The two `uint8` are combined to form `ax` `ay` and `az` of the type `int16` so that the sign of the data is preserved. Python does not have `uint8` and `int16` builtin, thus we need to use numpy that will provide the required data type for us to use.
- The resulting `int16` values of `ax`, `ay` and `az` are written in the `data.csv` file.