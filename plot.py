import matplotlib.pyplot as plt
import csv

filename = input("Enter filename without extension (.csv) to take data from: ")

rows = []
with open(f"{filename}.csv", 'r') as file:
    csvreader = csv.reader(file, delimiter=';')
    header = next(csvreader)
    for row in csvreader:
        rows.append(row)

xpoints, ypoints = [], []
for row in rows:
    xpoints.append(int(row[0]))
    ypoints.append(float(row[1]))

plt.title("Chromatic number of scale-free graphs (BA model)\nwith initial no. of vertices M = 5")
plt.xlabel("Number of vertices")
plt.ylabel("Median chromatic number")
plt.plot(xpoints, ypoints)
plt.savefig("plt2.png")