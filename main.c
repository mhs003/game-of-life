#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define FPS 20
#define GRID_SIZE 40 // 1:1 grid
#define CELL_SIZE 20  // 1:1 cell
#define WINDOW_HEIGHT GRID_SIZE *CELL_SIZE
#define WINDOW_WIDTH GRID_SIZE *CELL_SIZE
#define COLOR_ALIVE BLUE
#define COLOR_DEAD BLACK

typedef struct
{
    // int col;
    // int row;
    bool alive;
} Cell;

typedef struct
{
    Cell cells[GRID_SIZE][GRID_SIZE];
} Grid;

void DrawCell(int x, int y)
{
    DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, COLOR_ALIVE);
}

void ClearCell(int x, int y)
{
    DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, COLOR_DEAD);
}

void RenderGrid(Grid *grid)
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            Cell *cell = &grid->cells[row][col];

            int x = col * CELL_SIZE;
            int y = row * CELL_SIZE;

            if (cell->alive == true)
                DrawCell(x, y);
            else
                ClearCell(x, y);
        }
    }
}

void InitRandomCells(Grid *grid)
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            // grid->cells[row][col].row = row;
            // grid->cells[row][col].col = col;
            grid->cells[row][col].alive = rand() % 2;
        }
    }
}

void ClearGrid(Grid *grid) {
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            grid->cells[row][col].alive = false;
        }
    }
}

int CountNeighbours(int row, int col, Grid *grid)
{
    int count = 0;

    for (int dr = -1; dr <= 1; dr++)
    {
        for (int dc = -1; dc <= 1; dc++)
        {
            if (dr == 0 && dc == 0)
                continue;

            int r = row + dr;
            int c = col + dc;

            if (r < 0 || r >= GRID_SIZE)
                continue;
            if (c < 0 || c >= GRID_SIZE)
                continue;

            count += grid->cells[r][c].alive;
        }
    }

    return count;
}

void ScanGrid(Grid *grid, Grid *scannedGrid)
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        for (int col = 0; col < GRID_SIZE; col++)
        {
            int neighbourCount = CountNeighbours(row, col, grid);
            if (grid->cells[row][col].alive == true)
            {
                if (neighbourCount < 2 || neighbourCount > 3)
                    scannedGrid->cells[row][col].alive = false;
                else
                    scannedGrid->cells[row][col].alive = true;
            }
            else
            {
                if (neighbourCount == 3)
                    scannedGrid->cells[row][col].alive = true;
                else
                    scannedGrid->cells[row][col].alive = false;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game of Life");
    SetTargetFPS(FPS);

    Grid grid;
    Grid scannedGrid;
    InitRandomCells(&grid);
    bool shouldRun = true;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Key Events
        if (IsKeyPressed(KEY_R))
        {
            InitRandomCells(&grid);
        }
        if (IsKeyPressed(KEY_SPACE)) {
            shouldRun = !shouldRun;
        }
        if(IsKeyPressed(KEY_C)) {
            ClearGrid(&grid);
            ClearGrid(&scannedGrid);
        }

        // Mouse Click Event
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int col = GetMouseX() / CELL_SIZE;
            int row = GetMouseY() / CELL_SIZE;
            if(row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
                grid.cells[row][col].alive = !grid.cells[row][col].alive;
            } 
        }

        // Game 
        RenderGrid(&grid);
        if (shouldRun) {
            ScanGrid(&grid, &scannedGrid);
            grid = scannedGrid;
        }

        // 
        DrawFPS(GetScreenWidth() - 85, 10);
        if (shouldRun) {
            DrawText("Running...", 10, 10, 20, GREEN);
        } else {
            DrawText("Paused", 10, 10, 20, ORANGE);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}