import csv

bt_txt_file = open("data.txt", "r")
data = bt_txt_file.readlines()

bt_csv_file = open("data.csv", "w")
fields = ['ax', 'ay', 'az']
csvwriter = csv.writer(bt_csv_file)
csvwriter.writerow(fields)

for line in data:
    curr_line = line.split()
    
    # If not valid line skip
    if (curr_line[0] != '>' or len(curr_line) != 16):
        continue
    
    ax = curr_line[13]
    ay = curr_line[14]
    az = curr_line[15]
    print("ax = ", curr_line[13], "ay = ", curr_line[14], "az = ", curr_line[15])
    ax = int(ax, 16)
    ay = int(ay, 16)
    az = int(az, 16)

    acc_list = [ax, ay, az]

    csvwriter.writerow(acc_list)

