from sys import exit
import sys
import math

# Python 3 program to find rank of a matrix 
class rankMatrix(object): 
    def __init__(self, Matrix): 
        self.R = len(Matrix) 
        self.C = len(Matrix[0]) 
          
    # Function for exchanging two rows of a matrix 
    def swap(self, Matrix, row1, row2, col): 
        for i in range(col): 
            temp = Matrix[row1][i] 
            Matrix[row1][i] = Matrix[row2][i] 
            Matrix[row2][i] = temp 
              
    # Function to Display a matrix 
    def Display(self, Matrix, row, col): 
        for i in range(row): 
            for j in range(col): 
                print (" " + str(Matrix[i][j])) 
            print ('\n') 
              
    # Find rank of a matrix 
    def rankOfMatrix(self, Matrix): 
        rank = self.C 
        for row in range(0, rank, 1): 
              
            # Before we visit current row  
            # 'row', we make sure that  
            # mat[row][0],....mat[row][row-1]  
            # are 0.  
      
            # Diagonal element is not zero 
            if Matrix[row][row] != 0: 
                for col in range(0, self.R, 1): 
                    if col != row: 
                          
                        # This makes all entries of current  
                        # column as 0 except entry 'mat[row][row]'  
                        multiplier = (Matrix[col][row] /
                                      Matrix[row][row]) 
                        for i in range(rank): 
                            Matrix[col][i] -= (multiplier *
                                               Matrix[row][i]) 
                                                  
            # Diagonal element is already zero.  
            # Two cases arise:  
            # 1) If there is a row below it  
            # with non-zero entry, then swap  
            # this row with that row and process  
            # that row  
            # 2) If all elements in current  
            # column below mat[r][row] are 0,  
            # then remvoe this column by  
            # swapping it with last column and  
            # reducing number of columns by 1.  
            else: 
                reduce = True
                  
                # Find the non-zero element  
                # in current column  
                for i in range(row + 1, self.R, 1): 
                      
                    # Swap the row with non-zero  
                    # element with this row. 
                    if Matrix[i][row] != 0: 
                        self.swap(Matrix, row, i, rank) 
                        reduce = False
                        break
                          
                # If we did not find any row with  
                # non-zero element in current  
                # columnm, then all values in  
                # this column are 0. 
                if reduce: 
                      
                    # Reduce number of columns  
                    rank -= 1
                      
                    # copy the last column here 
                    for i in range(0, self.R, 1): 
                        Matrix[i][row] = Matrix[i][rank] 
                          
                # process this row again 
                row -= 1
                  
        # self.Display(Matrix, self.R,self.C)  
        return (rank) 



def transposeMatrix(m):
    rez = [[m[j][i] for j in range(len(m))] for i in range(len(m[0]))]
    return rez

def getMatrixMinor(m,i,j):
    return [row[:j] + row[j+1:] for row in (m[:i]+m[i+1:])]

def getMatrixDeternminant(m):
    #base case for 2x2 matrix
    if len(m) == 2:
        return m[0][0]*m[1][1]-m[0][1]*m[1][0]

    determinant = 0
    for c in range(len(m)):
        determinant += ((-1)**c)*m[0][c]*getMatrixDeternminant(getMatrixMinor(m,0,c))
    return determinant

def getMatrixInverse(m):
    determinant = getMatrixDeternminant(m)
    #special case for 2x2 matrix:
    if len(m) == 2:
        return [[m[1][1]/determinant, -1*m[0][1]/determinant],
                [-1*m[1][0]/determinant, m[0][0]/determinant]]

    #find matrix of cofactors
    cofactors = []
    for r in range(len(m)):
        cofactorRow = []
        for c in range(len(m)):
            minor = getMatrixMinor(m,r,c)
            cofactorRow.append(((-1)**(r+c)) * getMatrixDeternminant(minor))
        cofactors.append(cofactorRow)
    cofactors = transposeMatrix(cofactors)
    for r in range(len(cofactors)):
        for c in range(len(cofactors)):
            cofactors[r][c] = cofactors[r][c]/determinant
    return cofactors



def display(M):
    for i in range(len(M)):
        print(M[i])





def multiplication(X, Y):
    
    len1 = len(X)
    len2 = len(Y[0])

    result = []

    for i in range(len1):
        temp = []
        for j in range(len2):
            temp.append(0)
        
        result.append(temp)
    
    
    # iterate through rows of X
    for i in range(len(X)):
        # iterate through columns of Y
        for j in range(len(Y[0])):
            # iterate through rows of Y
            for k in range(len(Y)):
                result[i][j] += X[i][k] * Y[k][j]
                
    return result


def recursionX(A, b, x, j):
    n = len(x)

    if j == 0:
        return x

    else:
        total = 0
        for i in range(j, n, 1):
            total += A[j-1][i] * x[i]

        x[j-1] = (b[j-1] - total) / A[j-1][j-1]
        return recursionX(A, b, x, j-1)



def arbitrary(A, b):

    n = len(b)

    x = []
    for i in range(n):
        x.append(0)

    for i in range(len(A)):
        for j in range(len(A[0])):

            if (A[i][i] == 0 and b[i] == 0):
                
                x[j] = 0
                x = recursionX(A, b, x, j)
                    

    return x


def floatReg(X):

    for i in range(len(X)):
        X[i] = float("%.3f" % X[i])

    return X


OUTPUT_FILE = "output.txt"
INPUT_FILE = ""

if len(sys.argv) > 2:
    print("Wrong Input")
else:
    INPUT_FILE = sys.argv[1]

n = 0
A = []
rankA = 0
A_B = []
rankA_B = 0
B = []
rankB = 0


with open(INPUT_FILE) as file:
    line = file.readline()
    n = line.strip().split()
    n = int(n[0])
   
    
    for line in file:
        list = line.strip().split()
        for i in range(len(list)):
            list[i] = float(list[i])
        A_B.append(list)
b = []
for i in range(n):
    rowMofA = []
    rowMofB = []
    for j in range(n + 1):
        if j < n:
            rowMofA.append(A_B[i][j])
        else:
            rowMofB.append(A_B[i][j]) 
    
    A.append(rowMofA)
    B.append(rowMofB)


for i in range(len(B)):
    for j in range(len(B[0])):
        b.append(B[i][j])

list0 = []



for i in range(n + 1):
    list0.append(0)

A_B.append(list0)

    
RankMatrix1 = rankMatrix(A)
rankA = RankMatrix1.rankOfMatrix(A)

RankMatrix1 = rankMatrix(A)
rankA = RankMatrix1.rankOfMatrix(A)


RankMatrix2 = rankMatrix(A_B)
rankA_B = RankMatrix2.rankOfMatrix(A_B)


RankMatrix2 = rankMatrix(A_B)
rankA_B = RankMatrix2.rankOfMatrix(A_B)



RankMatrix2 = rankMatrix(A_B)
rankA_B = RankMatrix2.rankOfMatrix(A_B)



A1 = []
b1 = []
B1 = []


for i in range(n):
    rowMofA1 = []
    rowMofB1 = []
    for j in range(n + 1):
        if j < n:
            rowMofA1.append(A_B[i][j])
        else:
            rowMofB1.append(A_B[i][j]) 
    
    A1.append(rowMofA1)
    B1.append(rowMofB1)


for i in range(len(B1)):
    for j in range(len(B1[0])):
        b1.append(B1[i][j])


if rankA == n:
    
    Ai = getMatrixInverse(A1)
    X = multiplication(Ai, B1)
    x1 = []
    for i in range(len(X)):
        for j in range(len(X[0])):
            x1.append(X[i][j])

    X = x1


    strX = ""
    for i in range(len(X)):
        strX += str(X[i]) + " "
    
    invA = ""
    for i in range(len(Ai)):
        res = ""
        for j in range(len(Ai[0])):
            res += str(float("%.3f" % Ai[i][j])) + " "
        invA += res + "\n            "

    
    print("Unique Sulotion: " + strX)
    print("Inverted A: "+ invA)
    
    

elif (rankA < n and rankA == rankA_B):

    X = arbitrary(A1, b1)
    X = floatReg(X)
    
    strX = ""
    arb = ""
    for i in range(len(X)):
        strX += str(X[i]) + " "
        if X[i] != 0:
            arb += "x" + str(i) + " "

    print("Arbitrary variables: " + arb)
    print("Arbitrary solutions: " + strX)
    
    

else:
    print("Inconsistent problem")



