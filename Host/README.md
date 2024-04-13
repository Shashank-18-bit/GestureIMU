# Host

## parser.py

This file is responsible for the following things

- Takes a filename as a command-line argument (sys.argv[1]) and constructs input and output file paths based on that filename.
- Reads lines from the input text file (bt_txt_file) and splits each line into a list of strings.
- Checks if the current line is valid (it starts with `>` and has a length of 19 elements). If not, it skips to the next line.
- Converts specific elements of the line from hexadecimal strings to `uint8` values and stores them in raw_values.
- If `raw_values` list is not equal to `[0,0,0,1,0,0]`, it performs further processing:
    - If `end_seq_flag` is set to 1, it creates a new CSV file for writing and increments `file_count`
    - Fuses elements of the list `raw_values` to form `ax`, `ay`, and `az` values.
    - Logs the `ax`, `ay`, and `az` values.
    - Writes the `ax`, `ay`, and `az` values to the CSV file.
    - Resets `end_seq_flag` to 0.
- If `raw_values` list is equal to `[0,0,0,1,0,0]`, it sets `end_seq_flag` to 1 and continues to the next line.

## Fusion of `uint8`s into `int16`
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
- The resulting `int16` values of `ax`, `ay` and `az` are written in the the csv files which are saved in `csv\` directory.