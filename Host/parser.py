import csv
import numpy as np
import sys

txt_prefix = "txt/"+sys.argv[1]
bt_txt_file_name = txt_prefix + ".txt"
bt_txt_file = open(bt_txt_file_name, "r")
data = bt_txt_file.readlines()

csv_prefix = "csv/"+sys.argv[1]
bt_csv_file_name = csv_prefix + "_" + "0" + ".csv"
bt_csv_file = open(bt_csv_file_name, "w")
fields = ['ax', 'ay', 'az']
csvwriter = csv.writer(bt_csv_file)
csvwriter.writerow(fields)

print("-------------------------------------")
print("writing to the file", bt_csv_file_name)
print("-------------------------------------")

end_seq_flag = 0
file_count = 1

for line in data:
    # Obtain the current line
    curr_line = line.split()
    curr_line_len = len(curr_line)
    
    # If not valid line skip
    if (curr_line[0] != '>' or curr_line_len != 19):
        continue

    # Convert all elements to uint8, later they will be fused to form int16
    raw_values = [np.uint8(int(curr_line[i], 16)) for i in range(13, curr_line_len)]

    if(raw_values != [0,0,0,1,0,0]):

        if(end_seq_flag == 1):
            new_file_name = csv_prefix + "_" + str(file_count) + ".csv"

            print("-------------------------------------")
            print("writing to the file", new_file_name)
            print("-------------------------------------")

            bt_csv_file = open(new_file_name, "w")
            csvwriter = csv.writer(bt_csv_file)

            file_count = file_count + 1
        
        # Fusion
        ax = np.int16(((raw_values[0] << 8) + raw_values[1]))
        ay = np.int16(((raw_values[2] << 8) + raw_values[3]))
        az = np.int16(((raw_values[4] << 8) + raw_values[5]))

        # Log
        print("ax = ", ax, "ay = ", ay, "az = ", az)

        # Write to the CSV
        acc_list = [ax, ay, az]
        csvwriter.writerow(acc_list)
        end_seq_flag = 0
    else:
        end_seq_flag = 1
        continue
        

        


