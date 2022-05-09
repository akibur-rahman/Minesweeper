#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 9    // map width
#define col 9    // map height
#define COUNT 10 // number of mine

int SelectionMenu()
{

    printf("1.Play\n");
    printf("0.Exit\n");

    printf("Select Option:");
    int choice = 0;
    scanf("%d", &choice);
    return choice;
}

int main()
{
    int choice = 0;
    srand((unsigned int)time(NULL));
    while (1)
    {
        choice = SelectionMenu();
        if (choice == 1)
        {
            MineSweeper();
        }
        else if (choice == 0)
        {
            printf("Exiting......\n");
            break;
        }
        else
        {
            printf("Invalid Input\n");
        }
    }

    system("pause");
    return 0;
}

void MineSweeper()
{
    char show_map[row][col]; // creating 2d array for map
    char mine_map[row][col];

    InitializeMap(show_map, mine_map); // inertializing maps
    int blank_count = 0;               // counts non mine inputs
    while (1)
    {

        ShowMap(show_map);      // shows the map
        printf("Enter Input:"); // take array locations as input
        int i = 0;
        int j = 0;
        scanf("%d %d", &i, &j);
        if (i < 0 || i >= row || j < 0 || j >= col)
        {
            printf("Invalid Imput:\n");
            continue;
        }
        if (show_map[i][j] != '*')
        {
            printf("Position Flipped, Re Enter:\n");
            continue;
        }

        if (mine_map[i][j] == '1') // checks if the user has entered a mine position
        {
            ShowMap(mine_map);
            printf("game over!\n");
            break;
        }
        blank_count++;
        if (blank_count == row * col - COUNT) // check game win
        {
            printf("Success, You've cleared all the mines\n");
            break;
        }
        UpdateShowMap(show_map, mine_map, i, j);
    }
}

void InitializeMap(char show_map[row][col], char mine_map[row][col])
{

    for (int i = 0; i < row; i++) // print * to all arrays
    {
        for (int j = 0; j < col; j++)
        {
            show_map[i][j] = '*';
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            mine_map[i][j] = '0';
        }
    }

    int mine_count = COUNT; // randomly generating mine locations
    while (mine_count > 0)
    {
        // Generate random coordinates
        int i = rand() % row;
        int j = rand() % col;
        if (mine_map[i][j] == '1')
        {
            continue;
        }
        mine_map[i][j] = '1';
        --mine_count;
    }
}

void ShowMap(char map[row][col])
{
    // 1. Print the first 1 row (coordinate)
    printf(" |");
    for (int j = 0; j < col; j++)
    {
        printf(" %d", j);
    }
    printf("\n");
    // 2. print 1 Line separators
    for (int j = 0; j < col; j++)
    {
        printf("---");
    }
    printf("\n");
    // 3. Print each line separately
    for (int i = 0; i < row; i++)
    {
        printf(" %d|", i);
        for (int j = 0; j < col; j++)
        {
            printf(" %c", map[i][j]);
        }
        printf("\n");
    }
}

void UpdateShowMap(char show_map[row][col], char mine_map[row][col], int i, int j)
{
    // Determine the current position ( i . j ) , around 8 There are several mines in this grid
    int count = 0;
    if (i - 1 >= 0 && j - 1 >= 0 && mine_map[i - 1][j - 1] == '1')
    {
        count++;
    }
    if (i - 1 >= 0 && mine_map[i - 1][j] == '1')
    {
        count++;
    }
    if (i - 1 >= 0 && j + 1 < col && mine_map[i - 1][j + 1] == '1')
    {
        count++;
    }
    if (j - 1 >= 0 && mine_map[i][j - 1] == '1')
    {
        count++;
    }
    if (j + 1 < col && mine_map[i][j + 1] == '1')
    {
        count++;
    }
    if (i + 1 < row && j - 1 >= 0 && mine_map[i + 1][j - 1] == '1')
    {
        count++;
    }
    if (i + 1 < row && mine_map[i + 1][j] == '1')
    {
        count++;
    }
    if (i + 1 < row && j + 1 < col && mine_map[i + 1][j + 1] == '1')
    {
        count++;
    }
    // count  The value inside is already the number of surrounding mines
    show_map[i][j] = count + '0';
}
