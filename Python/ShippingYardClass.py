# The shipping container project uses linked lists to store and sort, by destination
# , user imputed packages. Packages are added into a virtual shipping container
# where they are sorted by weight. Each container has a maximum capacity of
# 2000lps. This project is a virtual shipping yard.
#******************************************************************************
#  Christopher Dubeau CMPT 200 2013/11/13 (C) Christopher
#  File: ShippingYardClass.py
#******************************************************************************
packnum = 0 # a globle variable that is used to make the Package IDs
conNum = 0 # a globle variable that is used to make the container IDs
#******************************************************************************
# Package is the class used to make a package for the shipping yard
#******************************************************************************
class Package:
    #**************************************************************************
    # __init__ takes in the owner destination and weight and makes a package 
    # with those values
    #**************************************************************************
    def __init__(self,owner,destination,weight):
        self.weight = weight # sets the package weight to the weight that is input
        self.destination = destination # sets the package destination to the destination that was input
        self.owner = owner # sets the package owner to the owner that was input
        self.ID = self.ID() # calls the ID function to make a unique ID
        self.nPack = None # used to singuly link list in a container
        
    #**************************************************************************
    # ID() uses the global variable packnum to make a unique ID for input packages
    #**************************************************************************
    def ID(self):
        global packnum
        package = 100000 + packnum # adds the package number to 100000 to make the ID
        packnum += 1 # increases pack num by 1
        return package # returns the ID
    
    #**************************************************************************
    # readIn() is sent an id from a file and sets the package id to that ID only
    # used when reading a package and container list
    #**************************************************************************
    def readIn(self,Id):
        self.ID = Id # sets the package.id to the sent id
        
    
#**************************************************************************
# Container is a class that represents a single container that has packages
# in it
#**************************************************************************
class Container:
    #**************************************************************************
    # __init__ is sent a package that does not fit into an existing container
    # and makes a container to the package destinations
    #**************************************************************************
    def __init__(self,P):
        self.destination = P.destination # makes the container desintaion to that of the first package
        self.weight = P.weight # makes the container weigh as much as the only package in the list
        self.fpackage = P # a pointer that points to the first package in the container
        self.ID = self.ID() # calls ID() to make a custom conainer ID
        self.nt = None # pointer that points to the next container in the yard
        self.lt = None # pointer that points to the previous container in the yard
        
    #**************************************************************************
    # readIn() is called after a temp package is used to make a container it 
    # makes it into an empty conainer that will be filled with the packages 
    # ead in from the file
    #**************************************************************************
    def readIn(self,Id):
        self.ID = Id # sets the container ID to that of the file
        self.fpackage = None # makes it so there is no package in the container
        self.weight = 0 # sets teh weight to 0
        
    #**************************************************************************
    # ID() uses the global variable to make a unique Id for the container
    #**************************************************************************
    def ID(self):
        global conNum # holds the number of container that exist + 1
        contain = 300000 + conNum # adds conNum to 300000 to make an ID
        conNum += 1 # increments conNum
        return contain #returns the ID
    
    #**************************************************************************
    # maxweight() checks if the container can add a package with out going over
    # the 2000 pound limit
    #**************************************************************************
    def maxweight(self,P):
        if (self.weight + P.weight) > 2000: # if the package will put the container over the limit
            return 1 # returns true
        else:
            return 0 # if the package will fit returns false
    
    #**************************************************************************
    # add() recurses throught the containers list of packages and places the
    # package in its place that sorts teh container by weight
    #**************************************************************************
    def add(self,P,N):
        if self.fpackage == None: # if there are no packages in the container
            self.fpackage = P # makes the new package equal the head
            self.weight += P.weight # adds the weigh into the container
        elif P.weight < self.fpackage.weight: # if the package is lighter than the current first package
            P.nPack = self.fpackage # makes the P.nPack point to the current head
            self.fpackage = P # makes P the new head
            self.weight += P.weight # adds the weight of P to the container
        elif N.nPack == None: # if the current package being looked at is the end of the list
            N.nPack = P # makes the end point to P making P the new end
            self.weight += P.weight # adds the weight to the container
        elif N.nPack.weight >= P.weight: # if the next package is larger than the new package
            P.nPack = N.nPack # makes p point the the next package
            N.nPack = P # makes the current package point to the new package
            self.weight += P.weight # adds teh weight of P into the container
        else: # if none of the above are true
            self.add(P, N.nPack) # recurses forward in the list
        
    #**************************************************************************
    # search() recurses through the container from the start till the end to
    # find the specific ID
    #**************************************************************************
    def search(self,Id,pack):
        found = 0 # a variable used to indicate if the ID is found in the container
        noin = 0 # a variable used to indicate if the ID was not found in the container
        while found == 0 and noin == 0: # runs till one of teh two variable are make true
            if pack.ID == Id: # if the current package is the one being looked for
                found = 1 # makes found = 1
            elif pack.nPack == None: # if the current package being looked at is the last in the list
                noin = 1 # sets noin to 1
            else: # if neather of the above is true
                pack = pack.nPack # moves to the next package in the list
        if found == 0 and noin == 1: # if the package was not found
            return 2 # returns 2
        elif found == 1: # if the package was found in the container
            return 1 # returns 1
                
    #**************************************************************************
    # remove() recurses through a container looking for a package and if its
    # found it removes it from the list
    #**************************************************************************
    def remove(self,Id,pack):
        found = 0 # a variable used to indicate if the package was removed
        noin = 0 # a variable used to indicate if the package was not found in the current container
        while found == 0 and noin == 0: # while both variable are false
            if self.fpackage.ID == Id: # if the first package in the list is the target
                self.weight -= pack.weight # removes the weight of the package from the container
                self.fpackage = pack.nPack # makes the head point to the second package in the container
                found = 1 # sets found to 1
            elif pack.nPack == None: # if the current package is the end of the list
                noin = 1 # sets noin to 1
            elif pack.nPack.ID == Id: # if the next package is the target
                self.weight -= pack.nPack.weight # removes the targest weight from the container
                pack.nPack = pack.nPack.nPack #  makes the current package point to the package after the target
                found = 1 # sets found to 1
            else: # if none of the above are true
                pack = pack.nPack # moves to the next package in the list
        if found == 0 and noin == 1: # if the package was not found
            return 2 # returns 2
        elif found == 1: # if the package was found
            return 1 # returns 1
    
    #**************************************************************************
    # writeall() is used to write the information of all the packages of the
    # container into a file
    #**************************************************************************
    def writeall(self,pack,file):
        if pack != None: # if its not the last package
            file.write(str(pack.ID) + ', ' + pack.owner +', ' + str(pack.weight) +'\n') # creates a string of the ID, Ownerm weight of the package
            self.writeall(pack.nPack,file) # recurses to the next package in the list
        
    #**************************************************************************
    # printall() prints out all the contents of the container in order of 
    # weight into the display window
    #**************************************************************************
    def printall(self,pack):
        if pack != None: # if its not the last package in the container
            print ('  ' + str(pack.ID) + ' , ' + pack.owner + ' , ' + pack.destination + ' , ' + str(pack.weight)) # prints out the ID, owner and weight of the package
            self.printall(pack.nPack) # recureses to the next package in the list

#**************************************************************************
# Yard is the class that holds all the containers and packages and contains
# most of the functions called by the main program, the functions are 
# in the class so that any changes are saved without returning
#**************************************************************************
class Yard:
    #**************************************************************************
    # __init__ makes an empty yard with no container in it
    #**************************************************************************
    def __init__(self):
        self.cCount = 0 # sets teh number of container to 0
        self.FContainer = None # sets the first container refrence to None
        
    #**************************************************************************
    # readIn() reads a file that has the container and package information in it
    # it then reads trhough and makes container and packages with the read in 
    # values (I assume that the user will read the file first before doing anything
    # else)
    #**************************************************************************
    def readIn(self,file):
        n = file.readline()
        while n != '': # while not at the end of the file
            if n[0] == '%': # if the read in information is for a container
                line = [] # a blank list to put the good character into
                for x in n: # goes through all the letters
                    if x.isalpha() == 1 or x.isdigit() or x == ' ': # checks if its a character to keep
                        line.append(x) # puts the character into the list
                l = ''.join(line) # reforms all the words from the individual charcters
                l = l.split(' ') # makes a list fo the values
                l.pop(0) # removes the blank value in the 0 spot of teh list
                dest = l[1] # makes the destination equal the input value(used when adding packages)
                tem = Package('temp',l[1].capitalize(),2000) # makes a temporary package that will make a new container
                temp = Container(tem) # makes a container with the temp package
                temp.readIn(int(l[0])) # makes the container empty but set to the destination
                self.place(temp,self.FContainer) # puts the container in its appropriate place in teh yard(alphabeticly by destination)
                n = file.readline() # reads the next line of the file
            else: # if the line was a package
                line = [] # a blank list to put the good character into
                for x in n: # goes through all the letters
                    if x.isalpha() == 1 or x.isdigit() or x == ' ' or x == '_': # checks if its a character to keep
                        line.append(x) # puts the character into the list
                l = ''.join(line) # reforms all the words from the individual charcters
                l = l.split(' ') # makes a list of the read values
                if len(l) == 4: # if the file input is like the exapmle with the name seperated
                    a = l[0] # sets a to the ID
                    b = str(l[1] + '_' + l[2]) # combins the first and last name seperated by a _
                    c = l[3] # makes c = weight
                    l = [a,b,c] # remakes the list of values
                P = Package(l[1], dest.capitalize(), int(l[2])) # makes a package using the values in the list
                P.readIn(int(l[0])) # sets the package Id to that from the file
                self.fillContainer(P,self.FContainer) # adds the package into the appropriate container
                n = file.readline() # eads teh next line in the file
                
    #**************************************************************************
    # place() puts an empty container from readIn() into its spot alphabeticaly 
    # in the yard
    #**************************************************************************
    def place(self,P,F):
        if self.FContainer == None: # if there are no containers in the yard
            self.FContainer = P # sets the first container to the empty container
        elif P.destination < self.FContainer.destination: # if the destaintion of the empty container comes before the first container
            self.FContainer.lt = P # make the current first container previous point to the empty container
            P.nt = self.FContainer # sets the empty conainers next pointer to point at the current first Container
            self.FContainer = P # sets the empty container to the yards first containers
        elif F.nt != None and P.destination >= F.nt.destination: # if the destination of the empty container comes after the next container in the list
            self.place(P,F.nt) # recurse so with the next container in the list being the current
        elif F.nt != None and P.destination < F.nt.destination: # if the next containers destination comes after the new containers destination
            F.nt.lt = P # sets the next containers previous pointer to point to the new container
            P.nt = F.nt # sets the new container's next pointer to point to the next container
            P.lt = F # sets the new container's previous pointer to point to the current container
            F.nt = P  # sets the current container's next pointer to point to the new container
        elif F.nt == None: # if the current container is the end of the list
            F.nt = P # makes the current container's next pointer point to the new container
            P.lt = F # makes the new container's previous pointer point to the current container
            
    #**************************************************************************
    # search() goes throught the list of containers till it hits the end or 
    # finds a container that has a matching destination to the one sent as a 
    # peramiter
    #**************************************************************************
    def Search(self,Id,dest,cont):
        found = 0 # a variable that is used to keep track if the package is found
        while cont.destination == dest and found == 0: # if the current container's destination is the same as the input one and the package is not found
            found = cont.search(Id,cont.fpackage) # searches throught the packages of the current container looking for the matching package ID
        if found == 1: # if the package was found
            return cont # it returns the container class of the current container
        elif cont.nt != None and cont.nt.destination <= dest and found != 1: # if the package was not found and the next container's destination is less than or matches the target
            return self.Search(Id,dest,cont.nt) # recurses with the next container being the current
        elif cont.nt == None or cont.nt.destination > dest: # if there is no next container or the next container's destination is larger than the target
            return 0   # return 0
        
    #**************************************************************************
    # fillContainer() take a new package as a peramiter then eather puts the 
    # package into an existing container with enough space or makes a new 
    # container using the new packages destination
    #**************************************************************************
    def fillContainer(self,New,cont):
        if self.FContainer == None: # if there are no containers in the yard yet
            self.FContainer = Container(New) # makes the first container point to the new container
        elif New.destination == cont.destination: # if the current container has the same destination as the package
            # the next if statment checks if there is no room in the container and if the next container is to a diffrent destination
            if cont.maxweight(New) == 1 and cont.nt != None and cont.nt.destination != New.destination:
                self.newcontainer(cont,cont.nt,New) # if it passes it inserts a new container between the two
            # the next if statment passes if there is no room in the container and the next container is to the same destination
            elif cont.maxweight(New) == 1 and cont.nt != None and cont.nt.destination == New.destination: 
                self.fillContainer(New,cont.nt) # it recurses with with the next container being the current
            elif cont.maxweight(New) == 1 and cont.nt == None: # this checks if this container is the last in line and there is no room left in the container
                c = Container(New) # makes a new container set to c
                c.lt = cont # makes c's previous pointer point to the current container
                cont.nt = c # makes the current container's next point point to c
            else: # if it fails all the above if statments
                cont.add(New,cont.fpackage) # it adds the package to the current container
        elif cont.nt != None and cont.nt.destination <= New.destination: # if the next container's destination is less than or equal to the package destination
            self.fillContainer(New,cont.nt) # puts the packahe into the next container
        elif cont.nt != None and cont.nt.destination > New.destination and cont.destination < New.destination: # if the next container's destination is larger than the package destination
            self.newcontainer(cont,cont.nt,New) # makes a new container with the package in it that is placed between the current and next container
        else: # if the current container is the first or last container
            if New.destination < cont.destination: # if the package destination comes before the first containers destination
                c = Container(New) # makes a new container with the package
                c.nt = cont # makes the new container point to current container
                cont.lt = c # makes the current container point back to the new container
                self.FContainer = c # makes the new container the first container in the yard
            else: # if the current container is the last in the list
                c = Container(New) # makes a new container with the package
                c.lt = cont # makes the new container point back to the last in the list
                cont.nt = c # makes the last container in the list point to the new container

    #**************************************************************************
    # newcontainer() creates a container using the New package and insets it
    # between cont and contn
    #**************************************************************************
    def newcontainer(self,cont,contn,New):
        new = Container(New) # makes the new container
        contn.lt = new # makes the later container point back to new
        cont.nt = new  # makes the first container point to new
        new.nt = contn # makes new point forward to the later container
        new.lt = cont  # makes new point back to the first container

    #**************************************************************************
    # locate() fins the first container that has a matching destination to that
    # is sent as a peramiter
    #**************************************************************************
    def locate(self,dest,cont):
        if cont.destination == dest: # if the containers destination is the same as the peramiter
            return cont # returns the container
        elif cont.nt != None: # if the next container is not none 
            return self.locate(dest,cont.nt) # recurses to the next container
        else:
            return 0 # returns 0 if no matching container is found
        
    #**************************************************************************
    # remove() locates containers that could contain the target package then
    # goes through the container and if the package is found it removes the 
    # package from the container and yard
    #**************************************************************************
    def remove(self,Id,dest,cont):
        found = 0 # if package has been found
        while cont.destination == dest and found == 0: # while the container is for the same destination and the package has not been found
            found = cont.remove(Id,cont.fpackage) # it goes through the contianer to try and find the package
        if found == 1: # if the package was found in the container
            if cont.fpackage == None: # if there is no more packages in the container
                if cont.lt == None and cont.nt == None: # if there are no more packages in the yard
                    self.FContainer = None # sets the first container in the yard to None
                elif cont.lt == None and cont.nt != None: # if the container is the first container
                    self.FContainer = cont.nt # makes the first container pointer point to the next container
                elif cont.lt != None and cont.nt == None:
                    cont.lt.nt = None
                else: # if there is a before and after the current container
                    cont.lt.nt = cont.nt # makes the previous container point to the next container
                    cont.nt.lt = cont.lt # makes the next container point back to the previous container
        elif cont.nt != None and cont.nt.destination <= dest and found != 1: # if the next container has a lower or equal destination as the target
            self.remove(Id,dest,cont.nt) # recurses with the next container being set as the current
            
    #**************************************************************************
    # printMD() finds all containers going to a destination and prints the
    # container information then the packages in the container with the information
    #**************************************************************************    
    def printMD(self,dest,cont):
        if cont.destination == dest: # if the container is going to the target destination
            print('% ' + str(cont.ID) + ', ' + cont.destination + ', ' + str(cont.weight)) # prints out the information for the destination
            cont.printall(cont.fpackage) # calls print all that prints the packages in the container
        if cont.nt != None: # if not at the end of the list of containers
            self.printMD(dest,cont.nt) # moves to the next container
            
    #**************************************************************************
    # fileWrite() writes the container information to the given file then calls
    # writeall to write the containers packages to the file.
    #**************************************************************************
    def fileWrite(self,cont,file):
        if cont == None: # if there is no more containers
            file.close() # closes the file
        else: # if there is still containers to be writen
            file.write('% ' + str(cont.ID) + ', ' + cont.destination + '\n') # writes the container information to the file
            cont.writeall(cont.fpackage,file) # writes the packages in the container to the file
            self.fileWrite(cont.nt,file) # uses recursion to go to the next container
            
    #**************************************************************************
    # printMA() print out all of the containers and their contents into the
    # interface window
    #**************************************************************************
    def printMA(self,cont):
        if cont == None: # if there are no more containers
            None # terminates the function
        else:
            print('% ' + str(cont.ID) + ', ' + cont.destination + ', ' + str(cont.weight)) # prints out the container information
            cont.printall(cont.fpackage) # prints out all the packages in the container
            self.printMA(cont.nt) # goes to the next container in the list
        
    #**************************************************************************
    # printCC() prints out all of the containers that are in the yard with their
    # id and remaining capacity
    #**************************************************************************
    def printCC(self,cont):
        if cont == None: # if there are no more containers
            None # terminates teh function
        else:
            print('% ' + str(cont.ID) + ', ' + cont.destination + ', Has ' + str(2000 - cont.weight) + ' Pounds of space left') # prints the information for the current container
            self.printCC(cont.nt) # goes to the next container
    
    #**************************************************************************
    # shipout() send out containers to a user determined destination removing
    # them from the yard and prints out the number of containers sent and their
    # combined weight of the containers
    #**************************************************************************
    def shipout(self):
        weight = 0 # a variable that keeps track of the weight of the containers shiped out
        count = 0 # keeps track of the number of containers shipped out
        dest = input("What destinations do you want to send containers to") # gets the target destination from the user
        dest = dest.capitalize()
        first = self.locate(dest,self.FContainer) # finds the first container with a matching destination
        if first == 0: # if no containers have a matching destination
            print("There are no container to go to that destination") # prints a message stating there are no containers
        else: # else there were containers
            st = first # keeps track of the first container
            while first.nt != None and first.destination == dest: # while the container equals the target
                count += 1 # increases the container count by 1
                weight += first.weight # adds the weight of the container to the weight
                first = first.nt # moves first to the next container
            if st.lt == None and first.destination != dest: # if the first container was the start
                first.lt = None # makes the last container looked at point back to None
                self.FContainer = first # makes thefirst container in the yard equal first
                print("There were " + str(count) + " Containers shipped out weighing " + str(weight)) # prints out the final statment
            elif st.lt != None and first.nt == None and first.destination == dest: # if the final container is the end of the list
                weight += first.weight # adds the weight of the last container
                count += 1 # adds 1 to the count of containers
                st.lt.nt = None # makes the container before st point to None
                print("There were " + str(count) + " Containers shipped out weighing " + str(weight)) # prints out the end statment
            elif st.lt == None and first.nt == None and first.destination == dest: # if the all of the containers were shipped out
                weight += first.weight # adds the weight of the last container to the count
                count += 1 # increases the number of container by one
                self.FContainer = None # sets the first container in the yard to none
                print("There were " + str(count) + " Containers shipped out weighing " + str(weight)) # prints out the end statment
            else: # if the containers sent out were in the middle of the list
                st.lt.nt = first # sets the next pointer of the preceding container to point to the last container
                first.lt = st.lt # sets the last container to point to the container preceding the ones being shipped out
                print("There were " + str(count) + " Containers shipped out weighing " + str(weight)) # print the end statement