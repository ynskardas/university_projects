class GoldenSection:

    def __init__(self, I):
        self.index = 0
        self.L = I
        self.a = 0
        self.b = 0
        self.landa = 0
        self.miuo = 0
        self.f_landa = 0
        self.f_miuo = 0 
        self.answer = 0
        self.f_answer = 0
        self.alfa = 0.618
        self.y = []
        self.d = []

     #..............................................................................
    def initialStep(self):

        self.landa = self.a + (1.0 - self.alfa) * (self.b - self.a)
        self.miuo = self.a + (self.alfa * (self.b - self.a))
        self.f_landa = self.function1(self.landa)
        self.f_miuo = self.function1(self.miuo)
        self.index = 1

     #..............................................................................
    def mainStep(self):

         #int yy = 7
        if ((self.b - self.a) < self.L):

            self.answer = (self.a + self.b) / 2
            self.f_answer = self.function1(self.answer)
            return

        elif (self.f_landa > self.f_miuo):

            self.step2()

        elif (self.f_landa <= self.f_miuo):

            self.step3()


     #..............................................................................
    def step2(self):

        self.a = self.landa
         #b = b
        self.landa = self.miuo
        self.f_landa = self.f_miuo
        self.miuo = self.miuo = self.a + (self.alfa * (self.b - self.a))
        self.f_miuo = self.function1(self.miuo)
        self.step4()

     #..............................................................................
    def step3(self):

         #a = a
        self.b = self.miuo
        self.miuo = self.landa
        self.f_miuo = self.f_landa
        self.landa = self.a + ((1.0 - self.alfa) * (self.b - self.a))
        self.f_landa = self.function1(self.landa)
        self.step4()

     #..............................................................................
    def step4(self):

        self.index += 1
        self.mainStep()

     #..............................................................................
    def function1(self, x):

        value = 0
         #double clone1 = (x * d[0]) + y[0] - 2
         #double clone2 = ((d[0] - 2 * d[1]) * x) + y[0] - (2 * y[1])
        clone1 = 5 * (self.y[0] + (x * self.d[0])) - (self.y[1] + (x * self.d[1]))
        clone2 = (self.y[0] + (x * self.d[0])) - 2
        clone3 = (self.y[0] + (x * self.d[0])) - 2 * (self.y[1] + (x * self.d[1])) 
        
        value = clone1 ** 4 + clone2 ** 2 + clone3 + 12
        return value






class Cyclic_Coordinate:
    

     #..................................................................
    def __init__(self, I):  
        
        self.epsilon = 0.001
        self.d1 =   [1, 0]  
        self.d2 =   [0, 1] 
        self.x = I[:]
        self.y = [0] * 2
        self.f_x = 0
        self.j = 0
        self.k = 0
        self.landa = 0
        # self.dataTable = DataTable()
        # self.dataTable.Columns.Add("k")
        # self.dataTable.Columns.Add("x f(x)")
        # self.dataTable.Columns.Add("j")
        # self.dataTable.Columns.Add("d")
        # self.dataTable.Columns.Add("y(j)")
        # self.dataTable.Columns.Add("landa")
        # self.dataTable.Columns.Add("y(j+1)")
     
     #..................................................................
    def initialStep(self):

        self.y = self.x[:]
        self.k = 0
        self.j = 1

    #  #..................................................................
    def mainStep(self):

        self.cloneY = [0] * 2
        while (self.j <= 2):
        
            gs = GoldenSection(0.001)
            gs.a = -10.0
            gs.b = 2.0
            gs.y = self.y[:]
            if (self.j == 1):
        
                gs.d = self.d1[:]
        
            else:
        
                gs.d = self.d2[:]
        
            gs.initialStep()
     #      while ((gs.b - gs.a) > gs.L):
     #  
            gs.mainStep()
     # 
     #       yy = 9
     #      answer
            self.landa = gs.answer
            if (self.j == 1):
                print(str(self.k) + " " * 5 + str(self.j) + " " * 5 + str(self.x)  + " " * 5 + str(self.y) + " " * 5 + str(self.d1) + " " * 5 + str(self.landa))
                

                cloneY = self.y[:]
                self.y[0] = cloneY[0] + (self.landa * self.d1[0])
                self.y[1] = cloneY[1] + (self.landa * self.d1[1])
                # self.dataTable.Rows.Add(k, "(" + self.x[0] + " , " + self.x[1] + ")",
                # j,"("+ self.d1[0]+" , "+ self.d1[1]+")", "(" + cloneY[0] + " , "
                # + cloneY[1] + ")", self.landa, "(" + self.y[0] + " , " + self.y[1] + ")")

                # print(str(self.k) + "----" + str(selfop8/8)

            elif (self.j == 2):
                print(str(self.k) + " " * 5 + str(self.j) + " " * 5 + str(self.f_x)  + " " * 5 + str(self.y) + " " * 5 + str(self.d2) + " " * 5 + str(self.landa))
                
                cloneY = self.y[:]
                self.y[0] = cloneY[0] + (self.landa * self.d2[0])
                self.y[1] = cloneY[1] + (self.landa * self.d2[1])
                self.f_x = self.function(self.x)
                # self.dataTable.Rows.Add(self.k, self.f_x, self.j, "(" + self.d2[0] + " , " + self.d2[1] +
                # ")", "(" + cloneY[0] + " , " + cloneY[1] + ")",
                # self.landa, "(" + self.y[0] + " , " + self.y[1] + ")")

            self.j += 1

        return self.step2()
     
     #..................................................................
    def step2(self):  
        
        cloneX = self.x[:]
        self.x = self.y[:]
         #Norm 2
        minusX = [0] * 2
        minusX[0] = self.x[0] - cloneX[0] 
        minusX[1] = self.x[1] - cloneX[1] 
        norm2 = self.Norm2(minusX)
        if (norm2 < self.epsilon):

            return False 

        else:

            self.y = self.x[:]
            self.j = 1
            self.k += 1
            return self.mainStep()

     #..................................................................
    def Norm2(self, variable):

        clone = variable[0] ** 2 + variable[1] ** 2
        value = clone ** (1/2)
        return value

     #..................................................................
    def function(self, x):

        value = 0
        clone1 = (5 * x[0] - x[1])
        clone2 = x[0] - 2
        clone3 = x[0] - 2 * x[1]
        value = clone1 ** 4 + clone2 ** 2 + clone3 + 12
        return value


class HookeAndJeeves:
 

 #.................................................................................
    def __init__(self, I):

        self.epsilon = 0.001
        self.L = 0.001
        self.dj1 = [1, 0] 
        self.dj2 = [0, 1] 
        self.y = [0] * 2
        self.x = I[:]
        self.x_previous = self.x[:]
        self.f_x = 0 
        self.j = 0 
        self.k = 0 
        self.landa = 0 
        # self.dataTable = DataTable() 
        # self.dataTable.Columns.Add("k") 
        # self.dataTable.Columns.Add("x f(x)") 
        # self.dataTable.Columns.Add("j") 
        # self.dataTable.Columns.Add("y(j)") 
        # self.dataTable.Columns.Add("d(j)") 
        # self.dataTable.Columns.Add("landa") 
        # self.dataTable.Columns.Add("y(j+1)") 
        # self.dataTable.Columns.Add("d") 
        # self.dataTable.Columns.Add("landa_had") 
        # self.dataTable.Columns.Add("y(j) + landa_had*d") 
        # self.indexDataTable = -1 
        self.d = [0] * 2
        self.answer = 0
        self.cloneY = [0] * 2
        self.a = -10.0
        self.b = 2.0

 #.................................................................................
    def initialStep(self):

        self.y = self.x[:]
        self.k = 0 
        self.j = 1 

 #.................................................................................
    def mainStep(self):
     
    #double[] cloneY = new double[2] 
        while (self.j <= 2):
         
            gs = GoldenSection(0.001) 
            gs.a = self.a 
            gs.b = self.b 
            gs.y = self.y[:]
            if (self.j == 1):
             
                gs.d = self.dj1[:]
             
            else:
             
                gs.d = self.dj2[:]
             
            gs.initialStep() 
            gs.mainStep() 
            self.landa = gs.answer 
            if (self.j == 1):
                
                print(str(self.k) + " " * 5 + str(self.j) + " " * 5 + str(self.x)  + " " * 5 + str(self.y) + " " * 5 + str(self.dj1) + " " * 5 + str(self.landa))
                
                self.cloneY = self.y[:]
                self.y[0] = self.cloneY[0] + (self.landa * self.dj1[0]) 
                self.y[1] = self.cloneY[1] + (self.landa * self.dj1[1]) 
                # self.indexDataTable += 1 
                # self.dataTable.Rows.Add(self.k, "(" + self.x[0] + " , " + self.x[1] + ")", self.j, "("+
                # self.cloneY[0]+" , "+ self.cloneY[1] + ")",
                # "(" + self.dj1[0] + " , " + self.dj1[1] + ")", self.landa, "(" + self.y[0] + " , " + self.y[1]
                # + ")", "_", "_", "_") 
                #j++ 
             
            elif (self.j == 2):
                
                print(str(self.k) + " " * 5 + str(self.j) + " " * 5 + str(self.f_x)  + " " * 5 + str(self.y) + " " * 5 + str(self.dj2) + " " * 5 + str(self.landa))
                
                self.cloneY = self.y[:]
                self.y[0] = self.cloneY[0] + (self.landa * self.dj2[0]) 
                self.y[1] = self.cloneY[1] + (self.landa * self.dj2[1]) 
                self.f_x = self.function(self.x) 
             
            self.j += 1 
         
        self.j = 2 
        #different from Cyclic Coordinate
        #double[] cloneX = new double[2] 
        self.x_previous = self.x
        self.x = self.y
        if (not self.haltCondition(self.x_previous, self.x)):
         
            return False
         
        else:
         
            self.step2()
            return True 
         
     
 #.................................................................................
    def haltCondition(self, a, b):
    
        minus = [0] * 2
        minus[0] = b[0] - a[0] 
        minus[1] = b[1] - a[1] 
        norm2 = self.Norm2(minus) 
        if (norm2 < self.epsilon):
            return False 
        
        else:
            return True 
    
 #.................................................................................
    def Norm2(self, variable):
    
        clone = variable[0] ** 2 + variable[1] ** 2 
        value = clone ** (1/2) 
        return value 
    
 #.................................................................................
    def step2(self):
     
        #double[] d = new double[2] 
        self.d[0] = self.x[0] - self.x_previous[0] 
        self.d[1] = self.x[1] - self.x_previous[1] 
        gs2 = GoldenSection(0.001) 
        gs2.a = self.a 
        gs2.b = self.b 
        gs2.d = self.d 
        gs2.y = self.x[:]
        gs2.initialStep() 
        gs2.mainStep() 
        #double answer = gs.landa 
        self.answer = gs2.answer 
        #answer == landa_had
        y2 = [0] * 2
        y2[0] = self.x[0] + (self.answer * self.d[0]) 
        y2[1] = self.x[1] + (self.answer * self.d[1]) 
        # self.indexDataTable += 1 
        # self.dataTable.Rows.Add(self.k, self.f_x, self.j, "(" + self.cloneY[0] + " , " +
        # self.cloneY[1] + ")", "(" + self.dj2[0] + " , " + self.dj2[1] + ")", self.landa, "(" +
        # self.y[0] + " , " + self.y[1] + ")", "(" + self.d[0] + " , " + self.d[1] + ")", self.answer,
        # "(" + y2[0] + " , " + y2[1] + ")") 
        self.y = y2[:]
        self.k += 1 
        self.j = 1 
        return self.mainStep()
     
 #.................................................................................
    def function(self, x):
     
        value = 0
        clone1 = (5 * x[0] - x[1])
        clone2 = x[0] - 2
        clone3 = x[0] - 2 * x[1]
        value = clone1 ** 4 + clone2 ** 2 + clone3 + 12
        return value
     
 

print ("For Cyclic Coordinate\n")
cyclic = Cyclic_Coordinate([5, 35])
cyclic.initialStep()
cyclic.mainStep()
print("\n" * 2)


print ("For Hooke And Jeeves\n")
huve = HookeAndJeeves([5, 35])
huve.initialStep()
huve.mainStep()