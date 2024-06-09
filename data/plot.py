import matplotlib.pyplot as plt
import csv

filename = input("Enter filename without extension (.csv) to take data from: ")
pltfile = input("Enter filename with extension to save plot to: ")
M = int(input("Enter the initial no. of vertices of the graph: "))

rows = []
with open(f"{filename}.csv", 'r') as file:
    csvreader = csv.reader(file, delimiter=';')
    header = next(csvreader)
    for row in csvreader:
        rows.append(row)

xpoints, ypoints = [], [list() for _ in range(len(header) - 1)]
for row in rows:
    xpoints.append(int(row[0]))
    for i in range(1, len(row)):
        ypoints[i - 1].append(float(row[i]) if i == 1 else int(float(row[i])))

plt.title(f"Chromatic number of scale-free graphs (BA model)\nwith initial no. of vertices M = {M}")
plt.xlabel("Number of vertices")
plt.ylabel("Median chromatic number")

cnt = 1
for _ypoints in ypoints:
    plt.plot(xpoints, _ypoints, label=header[cnt])
    cnt += 1

plt.legend(loc="lower right")
plt.savefig(pltfile)
