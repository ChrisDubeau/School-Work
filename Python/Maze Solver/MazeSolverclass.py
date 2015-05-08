# This project takes a maze file that must be formated like maze1020 where: Line
# one contains the length of the maze then the width of the maze sepertated by a
# space the second line contains the starting x then ending y locations, The
# Third Line contains the starting y then the ending x location. After this the
# maze us build using +, - and | symbols with white spaces as open rooms.
#******************************************************************************
#  Christopher Dubeau CMPT 200 2013/10/15 (C) Christopher
#  File: MazeSolverclass.py
#******************************************************************************
#******************************************************************************
# Maze: is a class that takes in an opened file and sets the start and finish
# locations from the file and the length and with, then can set up the maze
# as a list of lists
#******************************************************************************
class Maze:
        
    #**************************************************************************
    # __init__() takes in the opened file then reads the first three lines and
    # sets the start and finish loactions as well as the length and width
    #**************************************************************************
    def __init__(self, filename):
        self.file = filename # sets the file to a variable in the class
        a = self.file.readline() # reads the first line
        s = a.split(' ') # makes a list of the values
        self.length = (int(s[0])*2+1) # sets the length
        self.width = (int(s[1])*2+1)  # sets the width
        a = self.file.readline() # reads the second line
        s = a.split(' ') # makes a list of the values
        self.startx = int(s[0])*2-1 # sets the starting x value
        self.endy = int(s[1])*2-1  # sets the ending y value
        a = self.file.readline() # reads the third line
        s = a.split(' ') # makes a list of the values
        self.starty = int(s[0])*2-1 # sets the staring y value
        self.endx = int(s[1])*2-1 # sets the ending x value
        
    #**************************************************************************
    # board() makes a blank list of lists using the length and width of the 
    # maze then reads the rest of the file till the entire maze is set into 
    # board
    #**************************************************************************
    def board(self):
        self.board = [] # sets board to a blank list
        line = [] # a blank line to add to
        # next 5 lines set a blank list of lists having all spaces with " "'s
        for x in range(self.length): 
            for y in range(self.width):
                line.append(' ')
            self.board.append(line)
            line = []
        # next four lines read the remaining lines from the file and sets the list of lists to the characters
        for x in range(self.length):
            a = self.file.readline()
            for y in range(self.width):
                self.board[x][y] = a[y]