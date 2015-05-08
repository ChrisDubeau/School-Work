# The shipping container project uses linked lists to store and sort, by destination
# , user imputed packages. Packages are added into a virtual shipping container
# where they are sorted by weight. Each container has a maximum capacity of
# 2000lps. This project is a virtual shipping yard.
#******************************************************************************
#  Christopher Dubeau CMPT 200 2013/11/13 (C) Christopher Dubeau
#  File: ShippingYard.py
#******************************************************************************
from ShippingYardClass import * # imports the 3 classes Yard, Container and Package
#******************************************************************************
# main() starts the program, it then gets the action to be performed from the
# user then executes the appropriate function
#******************************************************************************
def Main():
    shipyard = Yard() #  creates an empty yard to start storing packages
    print("The commands that this program takes are:") # informational print statement
    print("a = add package, s = search for a package, p = print, r = remove package, sh = ship containers, d = done")# the basic requirments for the program
    print("As well the program accepts rc = reads from a file with containers, ra = reads a list of packages from file, w = write to file") # the bonus actions for the program
    order = input("What Would you like to do ") # gets what the user wants to do
    while order != 'd': # while the user is not done
        # this block runs if the user want to manualy add a package to the yard.
        if order == 'a':
            # the next line gets the owner destination and weight from the user(i assume that the user will follow the rules
            values = input("Enter the owner, destination and weight(seperate them with a space, if ther is a space in the owner or destination use a _ to represent it) ") 
            i = values.split(' ') # creates a list with input seperating at spaces
            while len(i) != 3: #if the user input the wrong number of values
                # the next line gets the new input form the user
                values = input("Error: enter the owner, destination and weight(seperate them with a space, if ther is a space in it use a _ to represent it) ")
                i = values.split(' ') # creates a new list of values from the user input
            while i[2].isdigit() == 0 or int(i[2]) > 2000: # if the user entered to large a package or the weight was not a number
                i[2] = input("You did not enter a valid weight ") # gets a new weight value form the user
            New = Package(i[0].capitalize(),i[1].capitalize(),int(i[2])) # creates a new package with the inputted values for destination, owner, and weight
            shipyard.fillContainer(New,shipyard.FContainer) # calls the fillContainer to add the package into the yard (creating a container if needed)
            
        # this block gets the information for the package the user wants to find then calls a search function to find it and prints the container ID that the package is in
        if order == 's':
            # the next line gets the ID number and destination of the of the package to look ups(I assume the user knows the ID number and destinations)
            values = input("Enter the ID number then the Destination of the package(seperate them with a space, Use _ for spaces in destination) ")
            i = values.split(' ')# creates a list of the 2 inputed values
            while len(i) != 2 and i[0].isdigit != 1: # while the user has not put in acceptable ID or Destination
                values = input("Enter the ID number then the Destination of the package(seperate them with a space) ") # gets the new values
                i = values.split(' ') # makes a list of the new data
            r = shipyard.Search(int(i[0]),i[1].capitalize(),shipyard.FContainer) # calls the yard serch function that returns the container that has the package in it
            if r != 0: # if the search did find the package in the yard
                print("Package " + i[0] + " going to " + i[1].capitalize() + " is in Container " + str(r.ID)) # prints a statment that that says the package was found and wear it is
            else: # if the search did not find the package
                print("There is no Package with the ID " + i[0] + " going to " + i[1].capitalize() + " is not in the yard") # a statment that says the package was not found
                
        # this block provides 3 diffrent styles to print out data if the user chose to print
        if order == 'p':
            t = input("what would you like to print(md = manifest for a destination, ma = manifest for the yard, cc = list of containors) ") # gets the style of printing thhe user wants to do
            if t == 'md': # if the user chose to print a manifest for the destination
                dest = input("what is the destination you want a manifest for ") # asks what destination they want to print the manifest for
                shipyard.printMD(dest,shipyard.FContainer) # calls the yard printMD function using the given destination
            if t == 'ma': # If the user chose to print a full manifest for the yard
                shipyard.printMA(shipyard.FContainer) # calls the yard printMA function
            if t == 'cc': # if the user chose to print a list of the containers in the yard
                shipyard.printCC(shipyard.FContainer) # calls the printCC function in yard
            
        # this blck runs if the user wants to remove a package from the yard
        if order == 'r':
            # the next line gets the ID and destination of the package thst the user wants to remove
            values = input("enter the ID and Destination of the package you want removed(seperate them with a space) ")
            i = values.split(' ') # creates a list of the 2 inputed values
            while len(i) != 2 and i[0].isdigit() == 0: # while the input is not what is required
                # the next line gets the new input from the user
                values = input("enter the ID and Destination of the package you want removed(seperate them with a space) ")
                i = values.split(' ') # creates a new list with the new input
            shipyard.remove(int(i[0]),i[1].capitalize(),shipyard.FContainer) # calls the remove function from Yard
            
        # this block is used to ship out containers to a destination.
        if order == 'sh': 
            shipyard.shipout() # calls the shipout function in Yard
            
        # this block runs if the user wanted to read in containers and packages from a file( I assume the user enters a file formated like your example and that the user will not load a manifest twice)
        if order == 'rc':
            file = input("whats the name of the file") # gets the name of the file from the user
            error = testfile(file) # tests if the file name is a good file
            while error == 0: # while the file is not a good file
                file = input("whats the name of the file") # gets new file name from the user
                error = testfile(file) # tests if the new filename is good
            f = open(file) # if the file is good it opens the file
            shipyard.readIn(f) # sends the open file to readIn in the Yard function
        
        # this block reads in a list of packages from a file( I assume the user enters a file that is formated like your example)
        if order == 'ra':
            file = input("whats the name of the file") # gets the file name form the user
            error = testfile(file) # tests if the file is good
            while error == 0: # while the file is not able to open
                file = input("whats the name of the file") # gets a new file name from the user
                error = testfile(file) # error checks the new file name
            file = open(file) # opens the good file
            n = file.readline() # reads the first packages informtation
            while n != '': # while not at the end of the file
                line = [] # a blank list to put the good character into
                for x in n: # goes through all the letters
                    if x.isalpha() == 1 or x.isdigit() or x == ' ': # checks if its a character to keep
                        line.append(x) # puts the character into the list
                l = ''.join(line) # reforms all the words from the individual charcters
                l = l.split(' ') # makes a list of all the words seperated by spaces
                if len(l) == 4:
                    a = str(l[0] + '_' + l[1])
                    l = [a,l[2],l[3]]
                P = Package(l[0], l[1].capitalize(), int(l[2])) # sends the values read in to make a new package (I assume that the owner is saves as first and last name like your exapmle)
                shipyard.fillContainer(P,shipyard.FContainer) # puts the package into the containers in the yard
                n = file.readline() # reads the next line and loops back to the while statement
                
        # this block runs if the user wants to twrite the manifest of the yard into a txt file( This overwrites the contents of the file, I assume your are updating a manifest from the past)
        if order == 'w':
            file = input("whats the name of the file you want to write to(will write over whats in there)") # gets teh file name from the user
            error = testfile(file) # tests the file to see if it exists
            while error == 0:# while the file does not exist
                file = input("whats the name of the file") # keeps getting a file name from the user
                error = testfile(file) # checks if the file can be opened
            file = open(file,'r+') # opens the file to write into
            shipyard.fileWrite(shipyard.FContainer,file) # calls the fileWrite function from Yard
        order = input("What Would you like to do( a(add), s(search), p(print), r(remove), sh(shipout), rc(read cont), ra(read pack), w(write), d(done)") # after the action finds out what the user wants to do next
    
#******************************************************************************
# testfile(): takes in the file name and test if its valid
#******************************************************************************
def testfile(name):
    try: # trys to open the file and returns 1 if it can be opened
        file = open(name) #trys opening a file
        return 1
    except: # if it fails it returns 0
        return 0