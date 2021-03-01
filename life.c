//***************************************************
// Filename: life.c
//
// Author(s): Tyler West
//***************************************************

#include "life.h"

// Constructs and returns a string (printable) representation of the grid
char *toString(int rows, int cols, char **grid)
{
	char *str = (char *) calloc(4 * rows * cols, sizeof(char));
	char *ptr = str;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '0') {
                sprintf(ptr," . ");
            } else {
                sprintf(ptr," X ");
            }
			ptr += 3;;
		}
		sprintf(ptr,"\n");
		ptr++;
	}

	return str;
}

// Creates a grid of rows x cols and initializes the grid with data from specified file
char **loadGridFromFile(char *filename, int *rows, int *cols)
{
	char **grid = NULL;
    char buf[1024]; // max length of line in input file
    FILE *file = fopen(filename,"r");

    // read line from file
    fgets(buf,1024,file);
    fclose(file); 

    // get number of rows from the line read
    *rows = atoi(strtok(buf," "));

    // get number of columns from the line read
    *cols = atoi(strtok(NULL," "));

	// COMPLETE THIS PART OF THIS FUNCTION
	char *value;

	for(int i = 0; i < *rows; i++){
		for(int j = 0; j < *cols; j++){
			value = strtok(NULL, " ");
			if(value != NULL){
				grid[i][j] = *value;
			} 
		}
	}
	//Maybe done
    return grid;
}

// Saves the grid data to the specified file
void saveGridToFile(char *filename, int rows, int cols, char **grid)
{
    FILE *file = fopen(filename,"w");

	// COMPLETE THIS PART OF THIS FUNCTION
	
	//put in rows and cols here 

	char buf[1024];
	sprintf(buf, "%d %d ", rows, cols);
	fputs(buf, file);

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			fputc(grid[i][j], file);
			fputc(' ', file);
		}
	}
	//maybe done
    fclose(file);
}

// Creates and returns a new grid that is a duplicate of the given grid
char **copyGrid(int rows, int cols, char **grid)
{
    char **dup = NULL;

	// COMPLETE THIS PART OF THIS FUNCTION
	dup = malloc(cols * rows * sizeof(char));
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			dup[i][j] = grid[i][j];
		}
	}
    return dup;
}

// Mutates the given grid one generation and return a new grid
char **mutateGrid(int rows, int cols, char **grid)
{
	char** newgrid = copyGrid(rows,cols,grid);

	/*
		A live cell with less than two live neighbors dies -> grid[i][j] == '1' and neighbors < 2 to '0'
		A live cell with two or three live neighbors lives -> nothing
		A live cell with more than three neighbors dies -> grid[i][j] == '1' and neighbors > 3 to '0'
		A dead cell with three live neighbors becomes live -> grid[i][j] == '0' and neighbors == 3 to '1'
	*/

	// COMPLETE THIS PART OF THIS FUNCTION
	int numNeighbors = 0;
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			//sets num of neighbors
			numNeighbors = nbrOfNeighbors(i,j,rows,cols,grid);

			if(grid[i][j] == '1' && numNeighbors < 2){
				newgrid[i][j] = '0';
			}
			if(grid[i][j] == '1' && numNeighbors > 3){
				newgrid[i][j] = '0';
			} 
			if(grid[i][j] == '0' && numNeighbors == 3){
				newgrid[i][j] = '1';
			}
		}
	}
	return newgrid;
}

// Returns the number of neighbors at postion (i,j) in the grid
int nbrOfNeighbors(int i, int j, int rows, int cols, char **grid)
{
	int neighbors = 0;

	// COMPLETE THIS PART OF THIS FUNCTION
	for(int rowOff = -1; rowOff <= 1; rowOff++){
		for(int colOff = -1; colOff <= 1; colOff++){
			//does nothing for itself
			if(rowOff == 0 && colOff == 0){
				continue;
			}
			int currentRow = i + rowOff;
			int currentCol = j + colOff;

			if(currentRow < 0 || currentRow >= rows){
				continue;
			}
			if(currentCol < 0 || currentCol >= cols){
				continue;
			}

			if(grid[i][j] == '1'){
				neighbors++;
			}
		}
	}
	return neighbors;
}

