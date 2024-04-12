import csv
import numpy as np

bt_txt_file = open("data.txt", "r")
data = bt_txt_file.readlines()

bt_csv_file = open("data.csv", "w")
fields = ['ax', 'ay', 'az']
csvwriter = csv.writer(bt_csv_file)
csvwriter.writerow(fields)

for line in data:

    # Obtain the current line
    curr_line = line.split()
    curr_line_len = len(curr_line)
    
    # If not valid line skip
    if (curr_line[0] != '>' or curr_line_len != 19):
        continue

    # Convert all elements to uint8, later they will be fused to form int16
    raw_values = [np.uint8(int(curr_line[i], 16)) for i in range(13, curr_line_len)]
    
    # Fuse the readings and convert it to int16 so that the sign is preserved
    ax = np.int16(((raw_values[0] << 8) + raw_values[1]))
    ay = np.int16(((raw_values[2] << 8) + raw_values[3]))
    az = np.int16(((raw_values[4] << 8) + raw_values[5]))

    # Log
    print("ax = ", ax, "ay = ", ay, "az = ", az)

    # Write to the CSV
    acc_list = [ax, ay, az]
    csvwriter.writerow(acc_list)

