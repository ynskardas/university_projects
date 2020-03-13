from sys import exit
import sys
import math

# output and input file variable

def sort(tupple):
    for i in range(1, len(tupple)):
        item_to_insert = tupple[i]
        # And keep a reference of the index of the previous element
        j = i - 1
        # Move all items of the sorted segment forward if they are larger than
        # the item to insert
        while j >= 0 and tupple[j][0] < item_to_insert[0]:
            tupple[j + 1] = tupple[j]
            j -= 1
        # Insert the item
        tupple[j + 1] = item_to_insert


OUTPUT_FILE = "output.txt"
INPUT_FILE = ""

KNAPSACK_LIST = []
INPUT_LIST = []


if len(sys.argv) > 2:
    print("Wrong Input")
else:
    INPUT_FILE = sys.argv[1]

n = 0
B = 0
with open(INPUT_FILE) as file:
    line = file.readline()
    n, B = line.strip().split("\t")
    n = int(n)
    B = int(B)
    
    for line in file:
        pi, vi = line.strip().split("\t")
        pi = int(pi)
        vi = int(vi)
        ri = pi / (vi * 1.0)
        INPUT_LIST.append((ri, (pi, vi)))

W = 0
sort(INPUT_LIST)

for i in range(len(INPUT_LIST)):
    pi = INPUT_LIST[i][1][0]
    vi = INPUT_LIST[i][1][1]


    if W + vi <= B:
        KNAPSACK_LIST.append(INPUT_LIST[i][1])
        #print(INPUT_LIST[i][1])
        W = W + vi

totalProfit = 0
for i in range(len(KNAPSACK_LIST)):
    pi = KNAPSACK_LIST[i][0]
    totalProfit = totalProfit + pi

f = open(OUTPUT_FILE, "w")
f.write("{}: {}\n".format("TOTAL PROFIT", totalProfit))
f.write("{}: {}\n".format("INPUT LIST", KNAPSACK_LIST))
f.close()
