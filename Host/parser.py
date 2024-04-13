import csv
import numpy as np

bt_txt_file = open("data.txt", "r")
data = bt_txt_file.readlines()

bt_csv_file = open("data0.csv", "w")
fields = ['ax', 'ay', 'az']
csvwriter = csv.writer(bt_csv_file)
csvwriter.writerow(fields)

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
            file_name = "data" + str(file_count) + ".csv"
            print("writing to a new file", file_name)

            bt_csv_file = open(file_name, "w")
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
        

        


