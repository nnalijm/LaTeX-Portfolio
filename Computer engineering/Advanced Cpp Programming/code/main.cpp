#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "MyText.h"
#include "Button.h"
using namespace sf;

const int MAXN = 17;

void clearAreaAround(int x, int y);
void openCell(int x, int y);
void dealWithEvent(RenderWindow& app, Event& e, int x, int y, Vector2i mousePosition);
void showDisplay(RenderWindow& app, Sprite& s, int w, int x, int y);
int numberOfFlagsAround(int x, int y);
void calculateNumberOfBombsAroundTheField();
void initializeGameField();
void win();
void initializeButtons();
void calculateBombProbabilities();
int calculateNumberAroundCell(int arr[MAXN][MAXN], int num, int i, int j);
void showProbabilities(RenderWindow& app);


int grid[MAXN][MAXN]{};       //real things in field - is mine or no in cell
int sgrid[MAXN][MAXN]{};      //the field which player see while playing
int used[MAXN][MAXN]{};     //
int probabilities[MAXN][MAXN];
int width{ 10 }, height{ 10 };
int numberOfFlags{ 0 };
bool dead{ false };
bool won{ false };
int showProbs{ 0 };
bool isFirstMoveMade{ false };
float gameTime{ 0.0 };
int numberOfEmptyCells{};
int flag{ 0 };
int bombChance{ 10 };

Button replayButton(105, 40, "Replay");
Button aiProcentButton(50, 40, " AI");

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 600), "Minesweeper!");
    int w = 32; // Width of each tile in the grid


    Texture t;
    t.loadFromFile("images/tiles.jpg");

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("images/background.jpg");
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    Sprite s(t);
    initializeButtons();
    initializeGameField();
    calculateNumberOfBombsAroundTheField();
    Clock clock;



    while (app.isOpen())
    {
        Vector2i mousePosition = Mouse::getPosition(app);
        int x = std::max(mousePosition.x / w, 0);
        int y = std::max((mousePosition.y - 50) / w, 0);



        if (!isFirstMoveMade)
        {
            gameTime = 0;
        }
        else
        {
            if (flag == 0)
            {
                clock.restart();
                flag = 1;
            }
            if (won == true || dead == true)gameTime = gameTime;
            else if (flag == 1)
                gameTime = clock.getElapsedTime().asSeconds();

        }
        Event e;
        while (app.pollEvent(e))
        {
            dealWithEvent(app, e, x, y, mousePosition);
        }

        app.clear(Color::White);
        app.draw(background);
        showDisplay(app, s, w, x, y);


    }

    return 0;
}


void clearAreaAround(int x, int y)
{
    openCell(x, y + 1);
    openCell(x + 1, y + 1);
    openCell(x + 1, y);
    openCell(x + 1, y - 1);
    openCell(x, y - 1);
    openCell(x - 1, y - 1);
    openCell(x - 1, y);
    openCell(x - 1, y + 1);
}

void openCell(int x, int y)
{
    if (x<1 || x > width || y < 1 || y > height || used[x][y] != 0 || sgrid[x][y] == 11) return;
    numberOfEmptyCells--;
    sgrid[x][y] = grid[x][y];
    used[x][y] = 1;
    if (grid[x][y] == 9)dead = true;
    if (grid[x][y] == 0)clearAreaAround(x, y);
}

void showDisplay(RenderWindow& app, Sprite& s, int w, int x, int y)
{
    MyText NumberOfBombsText(""); //NumberOfBombsText
    NumberOfBombsText.setPosition(45, 10);
    NumberOfBombsText.setFillTextColor(120, 6, 19);
    NumberOfBombsText.setCharacterSize(45);

    MyText TimeText(""); //time timer
    TimeText.setPosition(300, 10);
    TimeText.setFillTextColor(120, 6, 19);
    TimeText.setCharacterSize(45);

    MyText WinText("You won!!!"); //time timer
    WinText.setPosition(10, 450);
    WinText.setFillTextColor(120, 6, 19);
    WinText.setCharacterSize(80);

    MyText LoseText("You lose!!!"); //time timer
    LoseText.setPosition(10, 450);
    LoseText.setFillTextColor(120, 6, 19);
    LoseText.setCharacterSize(80);

 

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            if (sgrid[x][y] == 9 || dead == true)
            {
                // std::cout << "BOOM!! " << x << ' ' << y << '\n';
                sgrid[i][j] = grid[i][j];
            }
            s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
            s.setPosition(i * w, 50 + j * w);
            app.draw(s);
        }

    NumberOfBombsText.getChislo(numberOfFlags);
    NumberOfBombsText.draw(app);

    TimeText.getChislo(int(gameTime));
    TimeText.draw(app);
    if (won)
    {
        WinText.draw(app);
    }
    if (dead)
    {
        LoseText.draw(app);
    }
    if (showProbs)
    {
        //calculateBombProbabilities();
        showProbabilities(app);
    }

    replayButton.draw(app);
    aiProcentButton.draw(app);
    app.display();
}

void dealWithEvent(RenderWindow& app, Event& e, int x, int y, Vector2i mousePosition)
{
    //std::cout << endl << x << ' ' << y << endl;
    if (e.type == Event::Closed)
        app.close();
    if (won == false && dead == false) {
        if (e.type == Event::MouseButtonPressed) {
            calculateBombProbabilities();
            if (e.key.code == Mouse::Left)
            {
                std::cout << sgrid[x][y] << ' ' << grid[x][y] << " left\n";
                if (sgrid[x][y] >= 1 && sgrid[x][y] <= 8 && numberOfFlagsAround(x, y) == sgrid[x][y])
                {
                    clearAreaAround(x, y);
                }
                if (!isFirstMoveMade && x > 0 && x <= width && y > 0 && y <= height)
                {
                    std::cout << "FMNM\n";
                    if (grid[x][y] == 9)
                    {
                        grid[x][y] = 0;
                        numberOfFlags--;
                        numberOfEmptyCells++;
                        calculateNumberOfBombsAroundTheField();
                    }

                }
                isFirstMoveMade = true;

                openCell(x, y);
                std::cout << numberOfEmptyCells << "\n";
                if (numberOfEmptyCells == 0) win();
            }
            else if (e.key.code == Mouse::Right)
            {
                std::cout << "right\n";
                if (sgrid[x][y] == 10)
                {
                    sgrid[x][y] = 11;
                    numberOfFlags--;
                }
                else if (sgrid[x][y] == 11)
                {
                    sgrid[x][y] = 10;
                    numberOfFlags++;
                }
                // std::cout << numberOfFlags << '\n';
            }
            calculateBombProbabilities();
        }
    }

    if (replayButton.navediaMouse(e, mousePosition))
    {
        replayButton.setFillRacktengelColor(255, 0, 0);
    }
    else
    {
        replayButton.setFillRacktengelColor(140, 140, 137);
    }
    if (replayButton.pressed(e, mousePosition))
    {
        cout << "PRESSED" << endl;
        std::cout << mousePosition.x << ' ' << mousePosition.y << '/n';
        std::cout << won << ' ' << dead << '/n';
        initializeGameField();
        calculateNumberOfBombsAroundTheField();
        won = false;
        dead = false;
        isFirstMoveMade = false;
        flag = 0;
        gameTime = 0.0;
        calculateBombProbabilities();
    }

    if (aiProcentButton.navediaMouse(e, mousePosition))
    {
        aiProcentButton.setFillRacktengelColor(255, 0, 0);
    }
    else
    {   if(!showProbs)
            aiProcentButton.setFillRacktengelColor(105, 34, 29);
        else
            aiProcentButton.setFillRacktengelColor(16, 143, 20);
    }
    if (aiProcentButton.pressed(e, mousePosition))
    {
        cout << "PRESSED" << endl;
        calculateBombProbabilities();
        showProbs = 1 - showProbs;
        for (int r = 1; r <= width; r++) {
            for (int c = 1; c <= height; c++) {
                cout << probabilities[r][c] << " ";
            }
            cout << endl;
        }

    }


}

int numberOfFlagsAround(int x, int y)
{
    int k = 11;
    return sgrid[x][y + 1] / 11 +
        sgrid[x + 1][y + 1] / 11 +
        sgrid[x + 1][y] / 11 +
        sgrid[x + 1][y - 1] / 11 +
        sgrid[x][y - 1] / 11 +
        sgrid[x - 1][y - 1] / 11 +
        sgrid[x - 1][y] / 11 +
        sgrid[x - 1][y + 1] / 11;
}




void initializeGameField()
{
    numberOfFlags = 0;
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= height; j++)
        {
            used[i][j] = 0;
            sgrid[i][j] = 10;
            if (rand() % bombChance == 0) {
                grid[i][j] = 9;
                numberOfFlags++;
            }

            else grid[i][j] = 0;
        }
    numberOfEmptyCells = width * height - numberOfFlags;
}
void calculateNumberOfBombsAroundTheField()
{
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= height; j++)
        {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;
            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;
            grid[i][j] = n;
        }
}

void win()
{
    won = true;
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= height; j++)
        {
            if (sgrid[i][j] == 10)sgrid[i][j] = 11;

        }
    numberOfFlags = 0;

}

void initializeButtons()
{
    replayButton.setFillRacktengelColor(140, 140, 137);
    replayButton.setFillTextColor(0, 255, 90);
    replayButton.setPosition(140, 15);
    replayButton.setFillTextColor(255, 205, 5);
    replayButton.setCharacterSize(30);

    aiProcentButton.setFillRacktengelColor(105, 34, 29);
    aiProcentButton.setFillTextColor(0, 255, 90);
    aiProcentButton.setPosition(40, 420);
    aiProcentButton.setFillTextColor(255, 205, 5);
    aiProcentButton.setCharacterSize(30);

}


void calculateBombProbabilities() {
    for (int r = 1; r <= width; r++) {
        for (int c = 1; c <= height; c++) {
            probabilities[r][c] = 0.0;
        }
    }
    int numOfEmptyCells{};
    int numOfFlags{};
    int chance{};
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= height; j++)
        {
            if (sgrid[i][j] >= 1 && sgrid[i][j] <= 8)
            {
                //// numOfEmptyCells = calculateNumberAroundCell(sgrid, 10, i, j);
                // numOfFlags = calculateNumberAroundCell(sgrid, 11, i, j);
                numOfEmptyCells = 0;
                numOfFlags = 0;


                if (sgrid[i + 1][j] == 10) numOfEmptyCells++;
                if (sgrid[i][j + 1] == 10) numOfEmptyCells++;
                if (sgrid[i - 1][j] == 10) numOfEmptyCells++;
                if (sgrid[i][j - 1] == 10) numOfEmptyCells++;
                if (sgrid[i + 1][j + 1] == 10) numOfEmptyCells++;
                if (sgrid[i - 1][j - 1] == 10) numOfEmptyCells++;
                if (sgrid[i - 1][j + 1] == 10) numOfEmptyCells++;
                if (sgrid[i + 1][j - 1] == 10) numOfEmptyCells++;

                numOfFlags = numberOfFlagsAround(i, j);

                if (numOfEmptyCells > 0)
                {
                    chance = ((sgrid[i][j] - numOfFlags) * 100) / numOfEmptyCells;
                    if (chance == 0 && numOfEmptyCells > 0)chance = 111;
                    //std::cout << chance << ' ' << numOfEmptyCells << ' ' << numOfFlags << ' ' << sgrid[i][j] << ' ' << i << 'a  ' << j << '\n';
                    if (sgrid[i + 1][j] == 10) probabilities[i + 1][j] = max(probabilities[i + 1][j], chance);
                    if (sgrid[i][j + 1] == 10) probabilities[i][j + 1] = max(probabilities[i][j + 1], chance);
                    if (sgrid[i - 1][j] == 10) probabilities[i - 1][j] = max(probabilities[i - 1][j], chance);
                    if (sgrid[i][j - 1] == 10) probabilities[i][j - 1] = max(probabilities[i][j - 1], chance);
                    if (sgrid[i + 1][j + 1] == 10) probabilities[i + 1][j + 1] = max(probabilities[i + 1][j + 1], chance);
                    if (sgrid[i - 1][j - 1] == 10) probabilities[i - 1][j - 1] = max(probabilities[i - 1][j - 1], chance);
                    if (sgrid[i - 1][j + 1] == 10) probabilities[i - 1][j + 1] = max(probabilities[i - 1][j + 1], chance);
                    if (sgrid[i + 1][j - 1] == 10) probabilities[i + 1][j - 1] = max(probabilities[i + 1][j - 1], chance);
                }
            }

        }

}

int calculateNumberAroundCell(int arr[MAXN][MAXN], int num, int i, int j)
{
    int n{ 0 };
    if (arr[i + 1][j] == num) n++;
    if (arr[i][j + 1] == num) n++;
    if (arr[i - 1][j] == num) n++;
    if (arr[i][j - 1] == num) n++;
    if (arr[i + 1][j + 1] == num) n++;
    if (arr[i - 1][j - 1] == num) n++;
    if (arr[i - 1][j + 1] == num) n++;
    if (arr[i + 1][j - 1] == num) n++;
    return n;
}

void showProbabilities(RenderWindow& app)
{
    int w = 32;
    MyText probText[MAXN][MAXN]; //time timer 
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= height; j++)
        {
            if (sgrid[i][j] == 10 && probabilities[i][j] != 0)
            {
                probText[i][j].setPosition(5 + i * w, 50 + j * w);
                probText[i][j].setString(to_string(probabilities[i][j]));
                probText[i][j].setFillTextColor(209, 113, 40);
                probText[i][j].setCharacterSize(20);
                if (probabilities[i][j] == 100)
                {
                    probText[i][j].setCharacterSize(14);
                    probText[i][j].setPosition(5 + i * w, 52 + j * w);
                }
                if (probabilities[i][j] == 111)
                {
                    probText[i][j].setString("0");
                    probText[i][j].setCharacterSize(20);
                    probText[i][j].setPosition(10 + i * w, 50 + j * w);
                }
                probText[i][j].draw(app);
            }
        }
}
