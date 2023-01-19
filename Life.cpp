#include <vector>
#include <iostream>
#include <SDL2/SDL.h>

using Board = std::vector<std::vector<bool>>;

// Naive implementation.
class Life
{
public:
    Life()
    {
        currentGen[0][0] = 0;
        width = 0;
        height = 0;
    }
    // Precondition: all indexes within seed are also within width and height.
    Life(std::vector<std::vector<int>> seed, int width, int height)
    {
        currentGen.assign(width, std::vector<bool>(height, false));
        // Initalize currentGen from seed list.
        for (int i{0}; i < std::size(seed); ++i)
        {
            currentGen[seed[i][0]][seed[i][1]] = true;
        }
    }
    void iterate()
    {
        /*
        RULES:
        1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
        2. Any live cell with two or three live neighbours lives on to the next generation.
        3. Any live cell with more than three live neighbours dies, as if by overpopulation.
        4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        */
        Board nextGen = currentGen;

        for (int i{0}; i < std::size(currentGen); ++i)
        {
            for (int j{0}; j < std::size(currentGen[i]); ++j)
            {
                int liveCount{0};
                // Wow this is ugly.
                for (int k{-1}; k < 2; ++k)
                {
                    for (int n{-1}; n < 2; ++n)
                    {
                        if (!(n == 0 && k == 0))
                        {
                            liveCount += getCellStatus(i + k, j + n);
                        }
                    }
                }

                if (liveCount < 2)
                {
                    nextGen[i][j] = false;
                }
                else if (liveCount <= 3 && currentGen[i][j])
                {
                    nextGen[i][j] = true;
                }
                else if (liveCount == 3 && !currentGen[i][j])
                {
                    nextGen[i][j] = true;
                }
                else if (liveCount > 3)
                {
                    nextGen[i][j] = false;
                }
            }
        }

        currentGen = nextGen;
    }

    Board *getCurrentGen()
    {
        return &currentGen;
    }

    void render(int onRGB[], int offRGB[], int pixelSize, int windowWidth, SDL_Renderer *renderer)
    {
        for (int i{0}; i < windowWidth; i += pixelSize)
        {
            for (int j{0}; j < windowWidth; j += pixelSize)
            {
                if (currentGen[static_cast<int>(i / pixelSize)][static_cast<int>(j / pixelSize)])
                {
                    drawBox(renderer, i, j, onRGB, pixelSize); // I know there is an SDL function to do this; I chose to implement it myself for the practice.
                }
                else
                {
                    drawBox(renderer, i, j, offRGB, pixelSize);
                }
            }
        }
    }

    void drawBox(SDL_Renderer *renderer, int i, int j, int color[])
    {

        SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
        SDL_RenderDrawPoint(renderer, i, j);
    }

    void drawBox(SDL_Renderer *renderer, int i, int j, int color[], int pixelSize)
    {
        //(i, j) give the coordinates for the top left hand pixel in the box.
        for (int k{i}; k < i + pixelSize; ++k)
        {
            for (int n{j}; n < j + pixelSize; ++n)
            {
                SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
                SDL_RenderDrawPoint(renderer, k, n);
            }
        }
    }

private:
    int width;
    int height;
    Board currentGen;

    /*
    Uses Toridal space.
    */

    // I don't like this code, it's ugly.

    // Returns true if cell is live, false if cell is dead.
    bool getCellStatus(int i, int j)
    {
        int x{getIndexi(i)};
        int y{getIndexj(j)};

        return currentGen[x][y];
    }

    int getIndexi(int i)
    {
        int index{0};
        if (i == -1)
        {
            index = std::size(currentGen) - 1;
        }
        else if (i == std::size(currentGen))
        {
            index = 0;
        }
        else
        {
            index = i;
        }
        return index;
    }
    int getIndexj(int i)
    {
        int index{0};
        if (i == -1)
        {
            index = std::size(currentGen) - 1;
        }
        else if (i == std::size(currentGen[0]))
        {
            index = 0;
        }
        else
        {
            index = i;
        }
        return index;
    }
};
