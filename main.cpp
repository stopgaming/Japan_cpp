#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

extern "C" uint8_t _binary_MontserratMedium_nRxlJ_ttf_start[];
extern "C" uint8_t _binary_MontserratMedium_nRxlJ_ttf_end[];


int main()
{
    RenderWindow window(VideoMode(800, 800), "Hanjie Japan Nonogram");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    RectangleShape shape(Vector2f(70.f, 70.f));

    Font font;
//    if (!font.loadFromFile("MontserratMedium_nRxlJ.ttf "))
    if (!font.loadFromMemory(_binary_MontserratMedium_nRxlJ_ttf_start,_binary_MontserratMedium_nRxlJ_ttf_end - _binary_MontserratMedium_nRxlJ_ttf_start))
    {
        cout << "error";
    }


    float size = 70.f;

    vector<vector<int>> image =
    {
        {0, 0, 0, 1, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0},
        {1, 1, 0, 1, 0, 1, 0},
    };

    const int rows = image.size();
    const int cols = image[0].size();
    const int n = rows * cols;
    int hint_rows = (cols + 1) / 2;
    int hint_cols = (rows + 1) / 2;

    vector<RectangleShape> arr(n);
    //RectangleShape arr[n];
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            RectangleShape shape(Vector2f(size, size));
            shape.setOutlineColor(Color::Black);
            shape.setOutlineThickness(-5.f);
            shape.setFillColor(Color::White);
            shape.setPosition(hint_rows * size + j * size, hint_cols * size + i * size);
            arr[i * cols + j] = shape;
        }
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::Resized)
            {
                FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(View(view));
            }

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i localPosition = Mouse::getPosition(window);
                    if (
                        (localPosition.x < size * cols + hint_rows * size)
                        && (localPosition.y < size * rows + hint_cols * size)
                        && (localPosition.x > hint_rows * size)
                        && (localPosition.y > hint_cols * size)
                    )
                    {
                        int index = ((localPosition.x - hint_rows * int(size)) / static_cast<int>(size))
                                    + ((localPosition.y - hint_cols * int(size)) / static_cast<int>(size)) * cols;

                        Color color = arr[index].getFillColor();
                        if (color == Color::White) {
                            arr[index].setFillColor(Color::Green);
                        }
                        else if (color == Color::Green)
                        {
                            arr[index].setFillColor(Color::Red);
                        }
                        else
                        {
                            arr[index].setFillColor(Color::White);
                        }
                    }
                }
            }
        }

        window.clear(Color::Cyan);

        for (size_t i = 0; i < n; i++)
        {
            window.draw(arr[i]);
        }

        vector<vector <int>> cols_sums(cols);

        for (size_t i = 0; i < cols; i++)
        {
            int summa = 0;
            int hint_num = hint_cols - 1;

            for (int j = rows - 1; j > -1; j--)
            {
                if ((image[j][i] == 0) && (summa != 0)) {
                    //cout << summa << " ";
                    cols_sums[i].push_back(summa);

                    Text text;
                    text.setFont(font);
                    text.setString(to_string(summa));
                    text.setCharacterSize(size / 3);
                    text.setFillColor(Color::Red);
                    text.setPosition(hint_rows * size + i * size + size / 3, hint_num * size + size / 3);
                    window.draw(text);
                    hint_num -= 1;

                    summa = 0;
                }
                if (image[j][i] == 1) {
                    summa += 1;
                }

            }
            if (summa != 0) {
                //cout << summa << "";
                cols_sums[i].push_back(summa);
                Text text;
                text.setFont(font);
                text.setString(to_string(summa));
                text.setCharacterSize(size / 3);
                text.setFillColor(Color::Red);
                text.setPosition(hint_rows * size + i * size + size / 3, hint_num * size + size / 3);
                window.draw(text);
            }

            //cout << endl;
        }

        vector<vector <int>> rows_sums(rows);

        for (size_t i = 0; i < rows; i++)
        {
            int summa = 0;
            int hint_num = hint_rows - 1;

            for (int j = cols - 1; j > -1; j--)
            {
                if ((image[i][j] == 0) && (summa != 0)) {
                    rows_sums[i].push_back(summa);

                    Text text;
                    text.setFont(font);
                    text.setString(to_string(summa));
                    text.setCharacterSize(size / 3);
                    text.setFillColor(Color::Red);
                    text.setPosition(hint_num * size + size / 3, hint_cols * size + i * size + size / 3);
                    window.draw(text);
                    hint_num -= 1;
                    summa = 0;
                }
                if (image[i][j] == 1) {
                    summa += 1;
                }

            }
            if (summa != 0) {
                rows_sums[i].push_back(summa);
                Text text;
                text.setFont(font);
                text.setString(to_string(summa));
                text.setCharacterSize(size / 3);
                text.setFillColor(Color::Red);
                text.setPosition(hint_num * size + size / 3, hint_cols * size + i * size + size / 3);
                window.draw(text);
            }


        }

        window.display();
    }

    return 0;
}
