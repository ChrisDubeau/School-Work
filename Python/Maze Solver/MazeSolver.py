# This project takes a maze file that must be formated like maze1020 where: Line
# one contains the length of the maze then the width of the maze sepertated by a
# space the second line contains the starting x then ending y locations, The
# Third Line contains the starting y then the ending x location. After this the
# maze us build using +, - and | symbols with white spaces as open rooms.

#******************************************************************************
#  Christopher Dubeau CMPT 200 2013/10/15 (C) Christopher
#  File: MazeSolver.py
#******************************************************************************
around = [[-1,0],[1,0],[0,1],[0,-1]] # global varable with all possible directions
moves = [] # global variable that will contain all moves to the end of the maze
been = []  # global variable that will contain all spaces that are visited
from MazeSolverclass import * #imports the maze class
        
#******************************************************************************
# testfile(): takes in the file name and test if its valid and if not it loads
# a pre set maze.txt
#******************************************************************************
def testfile(name):
    try: # trys to open the file and returns it if it can be opened
        file = open(name) #trys opening a file
        return file
    except: # if it fails it prints an error message and opens the default maze.txt
        raise SystemExit("the file you entered was invalid")

#******************************************************************************
# run() takes in the current and previous x,y values and the maze class then
# recurses on itself till a solution is found or till all spaces have been
# visited
#******************************************************************************
def run(x,y,b):
    global moves # takes in the global moves for setting when soluion is found
    d = directions(x,y,b) # checks what dirsction it can move
    if len(d) >= 1: # if there are directions to move keeps moving
        for i in d: # runs till all movable directions are gone through
            if (x + i[0]) == b.endx and (y + i[1]) == b.endy: # if the next space is the finish
                moves.append([x+i[0],y+i[1]]) # sets the final space to moves
                moves.append([x,y]) # sets current loaction into moves
                return 1
            else:
                good = run(x + i[0], y + i[1], b) # recurses with next space as the current
                if good == 1: # when the end is found
                    moves.append([x,y]) # sets current space into moves
                    return 1
        return 0 # returns zero if runs into a dead end

#******************************************************************************
# directions(): takes in the current and previous x,y coordinates and then
# finds all legal spaces that can be moved into using global around
#******************************************************************************
def directions(x,y,b):
    global around # global of all avalable directions
    global been # global list of all visited spaces
    been.append([x,y]) # adds the current to the list of visited spaces
    d = [] # a blank list that will hold all possible directions
    for m in around:
        # next lines check to see if the there is an open door and that it has not been visited before
        if b.board[y+m[1]][x+m[0]] == ' ' and [x + m[0] + m[0],y + m[1] + m[1]] not in been:
                d.append([m[0]+m[0],m[1]+m[1]]) # adds the open space to the possibe dirrections
    return d # returns the list of possible moves

#******************************************************************************
# setmoves() uses the global moves to set the path used of a solved maze into 
# the board with '*'
#******************************************************************************
def setmoves(b):
    global moves # list of all spaces that are used to get to the end of the maze
    for x in moves: # go through all the spaces
        b.board[x[1]][x[0]] = '*' # sets the space to '*'

#******************************************************************************
# printmaze() prints out all the lines of the maze into the input window
#******************************************************************************
def printmaze(b):
    for x in b.board: # goes through all the lines in the maze
        l = ''.join(x) # joins the list into a string
        print(l) # prints the current string
        
#******************************************************************************
# readfile() gets the file name from the user then tries to open it and if it
# fails then opens a preset maze.txt and uses the maze class to set up the maze
#******************************************************************************  
def readfile():
    File = input("what is the name of the file you want to load: ") # gets the file name
    if File == '':
        opened = testfile('maze1020')
    else:
        opened = testfile(File) # error cheker that returns a good file
    b = Maze(opened) # sets the start and finish values and length and width
    b.board() # sets up the maze
    return b # returns the maze

#******************************************************************************
# solver() takes a maze file and then uses recursion to find if the maze has a
# solution and if it does prints the solution on the maze and if there is no
# solution prints the maze and a message saying ther is no solution
#******************************************************************************
def solver():
    global been
    global moves
    been = [] # resets been if running solver more than once in a row
    moves = [] # resets moves if running solver more than onece in a row
    b = readfile() # load the maze into b
    end = run(b.startx,b.starty,b) # runs the recursion till a solution is found or not
    if end == 1: # if there is a solution
        setmoves(b) # sets the moves to the board
        printmaze(b) # prints the maze with the solution
    else: # if there is no solution
        printmaze(b) # prints the maze with out any changes
        print("there is no solution to this") # prints the message