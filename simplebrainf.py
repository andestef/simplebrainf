code = open("hello.bf").read() # Read the file
cell = 0 # initialize variables
values = [0]
jump_to = []
c = 0
skip = 0
while c < len(code):
    char = code[c] #get character at c position
    if skip: # Check if skip != 0
        if char == '[': # +1 to skip if theres an [
            skip += 1
        elif char == ']': # -1 if ]
            skip -= 1
    elif char == '.':
        print(chr(values[cell]),end='') # Print the character value of the ascii value at the current cell
    elif char == ',':
        values[cell] += ord(input()[0]) # Take 1 character of input and add its ascii value to the current cell
    elif char == '+':
        values[cell] += 1 # Add 1 to current cell
    elif char == '-':
        values[cell] -= 1 # Subtr 1 from current cell
    elif char == '>':
        cell += 1 # Move cell Right 1
        if cell > len(values)-1: # If values isnt long enough for the cell, add a new cell to the end
            values.append(0)
    elif char == '<':
        cell -= 1 # Move the current cell left one
    elif char == '[':
        if values[cell] == 0: # If the current cell value is 0, skip up until theres an equal number of [ and ]
            skip = 1
        else:
            jump_to.append(c) # Set the point to return to after running the following code if the current cell value != 0
    elif char == ']': # If it lands on ] (And wasn't skipped because thats already been accounted for above), jump back to starting [
        c = jump_to[-1]-1 # -1 becuase it always adds one at the end
        jump_to.pop()
    while values[-1] == 0 and len(values)-1 != cell: # Garbage collector (Finds unused cells (Cells that are 0 past the current cell) and deletes them)
        values.pop()
    c += 1 # Move onto next char
