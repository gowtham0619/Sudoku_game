#include <iostream>
#include <vector>
#include <random>
using namespace std;

 

// Size of the Sudoku grid
const int GRID_SIZE = 9;

 

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    cout << "+-------+-------+-------+" <<endl;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (col == 0) {
                cout << "| ";
            }
            if (grid[row][col] != 0) {
                cout << grid[row][col] << " ";
            } else {
                cout << "  ";
            }
            if ((col + 1) % 3 == 0) {
                cout << "| ";
            }
        }
        cout << '\n';
        if ((row + 1) % 3 == 0) {
            cout << "+-------+-------+-------+" <<endl;
        }
    }
}

// Function to check if a number can be placed at the given position in the grid
bool isValid(const vector<vector<int>>& grid, int row, int col, int num) {

    // Check if the number exists in the same row
    for (int c = 0; c < GRID_SIZE; c++) {
        if (grid[row][c] == num) {
            return false;
        }
    }

    // Check if the number exists in the same column
    for (int r = 0; r < GRID_SIZE; r++) {
        if (grid[r][col] == num) {
            return false;
        }
    }

    // Check if the number exists in the same 3x3 grid         //----------------------change needed !!
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (grid[startRow + r][startCol + c] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            if (grid[row][col] == 0) {
                for (int number = 1; number <= GRID_SIZE; ++number) {
                    if (isValid(grid, row, col, number)) {
                        grid[row][col] = number;
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}


// Function to generate a random Sudoku grid
vector<vector<int>> generateRandomGrid() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 9);

    vector<vector<int>> grid(GRID_SIZE, vector<int>(GRID_SIZE, 0));

    // Fill the grid with random numbers
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {

            // Generate a random number between 1 and 9
            int num = dis(gen);

            // Check if the number is valid at the current position
            if (isValid(grid, row, col, num)) {
                grid[row][col] = num;
            }
        }
    }
    return grid;
}

// Function to check if the Sudoku grid is completely filled
bool isGridFilled(const vector<vector<int>>& grid) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Function to get user input for filling a cell
void getUserInput(int& row, int& col, int& num) {
    cout<< "Enter the row (1-9), column (1-9), and number (1-9) to fill & number 0 to solve (space-separated): ";
    cin>>row>>col>>num;
    row--;
    col--;
}

int main() {
    cout<<"Welcome to Sudoku!"<<endl;
    vector<vector<int>> grid = generateRandomGrid();  //Generating Grid
    vector<vector<int>> solvedgrid = grid;
    int i=0;
    while(!solveSudoku(solvedgrid)){
        i++;
        solvedgrid = generateRandomGrid();
        grid = solvedgrid;
    }

    while (true) {
        cout<<endl;
        printGrid(grid);      //Printing Grid after every input and validation
        int row, col, num;
        getUserInput(row, col, num);   //taking user data
      
        if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && num >= 0 && num <= 9) {     //verifying the position of the number entered
            if(num==0){
                cout<<"The final grid : ";
                if(solveSudoku(grid))
                    printGrid(grid);
                else
                    cout<<"Not solvable!!";
                return 0;
            }
                
            // Check if the cell is empty
            if (grid[row][col] == 0) {
                // Check if the number can be placed in the cell
                if (isValid(grid, row, col, num)) {
                    // Fill the cell with the number
                    grid[row][col] = num;
                    // Check if the grid is completely filled
                    if (isGridFilled(grid)) {
                        cout<<endl;
                        cout<< "Congratulations! You solved the Sudoku puzzle!"<<endl;
                        break;
                    }
                } else {
                    cout<< "Invalid number! Please try again." <<endl;
                }
            } else {
                cout<< "The cell is already filled! Please try again." <<endl;
            }
        } else {
            cout<< "Invalid input! Please try again." <<endl;
        }
    }
    return 0;
}
