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


def displayTable(M):

    for i in range(len(M)):

        for j in range(len(M[i])):

            M[i][j] = "| " + str(M[i][j]) + " |"


    display(M)

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

    for i in range(0, len(X)):

        for j in range(1, len(X[i])):
            X[i][j] = float("%.3f" % X[i][j])

    return X

def matrixId(n):

    result = []

    for i in range(n):
        temp = []
        for j in range(n):
            if i == j:
                temp.append(1)
            else:
                temp.append(0)
        
        result.append(temp)

    return result



def vecToMat(v):

    k = []

    k.append(v)

    return k


def matToVec(m):

    v = []

    for i in range(len(m)):

        for j in range(len(m[0])):

            v.append(m[i][j])

    return v


def elementSwap(A, a, B, b):

    A1 = transposeMatrix(A)

    B1 = transposeMatrix(B)

    hold = A1[a]

    hold2 = B1[b]

    A1[a] = hold2

    B1[b] = hold

    A = transposeMatrix(A1)

    B = transposeMatrix(B1)

    return (A, B)


def simplexOpps(M, col, row, X):

    pivot = M[row][col]

    M[row][0] = X[col]

    for i in range(1, len(M[row])):

        M[row][i] = M[row][i] / pivot

    for i in range(0, len(M)):
        k = (-1) * M[i][col]
        if i != row:

            for j in range(1, len(M[0])):

                M[i][j] = M[row][j] * k + M[i][j]

    return M




OUTPUT_FILE = "output.txt"
INPUT_FILE = ""

inp = ["Assignment3_Spring2020_Data1.txt", "Assignment3_Spring2020_Data2.txt", "Assignment3_Spring2020_Data3.txt"]

numOfFile = len(inp)

f = open(OUTPUT_FILE, "w")

for ii in range(numOfFile):
    INPUT_FILE = inp[ii]
    n = 0
    m = 0
    A = []
    X = []
    A_B1 = []
    z = 0
    B1 = []
    b = []
    nonbasis = []
    basis = []    
    bVec = []
    cB = []
    cN = []        
    xMx = []
    Table = []

    with open(INPUT_FILE) as file:
        line = file.readline()
        m, n = line.strip().split("\t")
        m = int(m)
        n = int(n)

        line = file.readline()
        cN1 = line.strip().split("\t")


        for i in range(len(cN1)):
            cN1[i] = -1 * float(cN1[i])

        cN = cN1

       
        
        for line in file:
            listAB = line.strip().split("\t")
            for i in range(len(listAB)):
                listAB[i] = float(listAB[i])

            A_B1.append(listAB)


    for i in range(m):
        rowMofA = []
        rowMofB1 = []
        for j in range(n + 1):
            if j < n:
                rowMofA.append(A_B1[i][j])
            else:
                rowMofB1.append(A_B1[i][j]) 
    
        A.append(rowMofA)
        B1.append(rowMofB1)

    for i in range(len(B1)):
        for j in range(len(B1[0])):
            bVec.append(B1[i][j])

    b = B1
        
    
    
    for i in range(n+m+1):

        xMx.append("x" + str(i))

    xMx.append("RHS")
    
    for i in range(m+1):
        k = []
        if i == 0:
            k.append("z")

            for j in range(n):
                k.append(cN[j])

            for j in range(m + 1):
                k.append(0)

        elif i < m+1:

            k.append("x" + str(n+i))

            for j in range(len(A[0])):

                k.append(A[i-1][j])

            for j in range(n+1, n+m+1):

                if i + n == j:
                    
                    k.append(1.0)

                else:

                    k.append(0)

            k.append(b[i-1][0])
        
        Table.append(k)

    check = True
    t = 0
    while(check):
        
        indRow = 0

        indCol = 0

        minNeg = 0

        minPos = -1

        for i in range(1, len(Table[0])):

            if Table[0][i] < 0:

                if Table[0][i] < minNeg:

                    minNeg = Table[0][i]

                    indCol = i
        
        if indCol == 0:

            break

        ctrl = True
        for i in range(1, len(Table)):

            top = Table[i][n+m+1]

            bot = Table[i][indCol]

            # print((top,bot))

            if bot > 0:
                
                if ctrl:
                    # print("ctrl works")
                    minPos = top / bot

                    indRow = i

                    ctrl = False

                else:

                    if top / bot < minPos:

                        minPos = top / bot

                        indRow = i

            # print((minPos, indRow))

        if indRow == 0:

            break

        
        
        t = t + 1

        if(t == 5):

            check = False

        Table = simplexOpps(Table, indCol, indRow, xMx)
        # print("\n-------------------")
        # # print((indRow, indCol))
        # # print("\n")
        # display(Table)

    Table = floatReg(Table)
    
    z = Table[0][n+m+1]

    xSol = [0]*n

    for i in range(1, len(Table)):

        for j in range(1, n+1):

            if Table[i][0] == "x" + str(j):

                xSol[j-1] = Table[i][n+m+1]

    f.write("{}\n".format("Optimal Variable Vector: " + str(xSol))) 
    f.write("{}\n\n\n".format("Optimal Result: "+ str(z)))
