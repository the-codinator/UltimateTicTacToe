#ifndef io_
#define io_

#define SOURCE "Board.dat"

// @Returns a pointer to the board read from @SOURCE and
// fills values pointed by x,y up with the location of
// next play. Note: does NOT allocate memory for x and y.
// Board is read as a 2D char array
char** input2D(int* x, int* y);

// @Returns a pointer to the board read from @SOURCE and
// fills values pointed by x,y up with the location of
// next play. Note: does NOT allocate memory for x and y.
// Board is read as a 4D char array
char**** input4D(int* x, int* y);


// Displays the board to the user through user interface
// x,y denotes next position to play
// Board is input as a 2D char array
void output2user(char** board, int x, int y);

// Prints the board to @SOURCE
// x,y denotes next position to play
// Board is input as a 4D char array
void output2file(char** board, int x, int y);

#endif //io_
