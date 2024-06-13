#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <time.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#define WIDTH 600
#define HEIGHT 400
#define PADDING 20
#define HERE "*"

class Button {
private:
    sf::RenderWindow* wn;
    int w;
    int h;
    int x;
    int y;
    int s;
    std::string t;
    sf::Color c;
    sf::Font f;
    sf::Text buttonText;
    sf::RectangleShape buttonShape;

public:
    int id;


    Button(sf::RenderWindow& window, int i, int width, int height, int xpos, int ypos, int size, std::string text, std::string fontPath, sf::Color color)
        : wn(&window), id(i), w(width), h(height), x(xpos), y(ypos), s(size), t(text), c(color) {
        
        if (!f.loadFromFile(fontPath)) {
            // Handle error
        }

        buttonText.setFont(f);
        buttonText.setString(t);
        buttonText.setCharacterSize(s);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(x + w / 2 - buttonText.getGlobalBounds().width / 2, y + h / 2 - buttonText.getGlobalBounds().height / 2);

        buttonShape.setSize(sf::Vector2f(w, h));
        buttonShape.setFillColor(c);
        buttonShape.setPosition(x, y);
    }

    void draw() {
        wn->draw(buttonShape);
        wn->draw(buttonText);
    }

    bool checkInput(sf::Vector2i position) {
        if (position.x - 2100 > x && position.x - 2100 < x + w && position.y < y && position.y > y + h) {
            return true;
        }
        return false;
    }

};


void visual(sf::RenderWindow& window, std::vector<int> el, int m) {
    int n = el.size();
    for (int i=0; i < n; i++){
        int h, w, x, y;
        h = el[i] * ((HEIGHT - 2 * PADDING) / (n-1));
        w = (WIDTH - 20 * PADDING) / (n-1);
        x = 200 + (i * 1.2 * w); 

        y = HEIGHT - PADDING;
        
        //std::cout << el[i] << " " << h << " " << w << " " << x << " " << y << std::endl;
        sf::RectangleShape rectangle(sf::Vector2f(w, h));
        
        if (m == el[i]) {
            rectangle.setFillColor(sf::Color(255, 0, 0));
        }

        rectangle.setPosition(x, y);
        rectangle.rotate(180);
        window.draw(rectangle);
    }
    window.display();

    //std::cout << std::endl;
}

void bubbleSort(sf::RenderWindow& window, std::vector<int>& arr, int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
 
            if (arr[j] > arr[j + 1]) {
                swapped = true;
                std::swap(arr[j], arr[j+1]);
                window.clear();
                visual(window, arr, arr[j]);
            }
        }

        if (swapped == false)
            break;
    }
}

void selectionSort(sf::RenderWindow& window, std::vector<int>& arr, int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {

       min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

       if (min_idx != i) {
            std::swap(arr[min_idx], arr[i]);
            window.clear();
            usleep(100000);
            visual(window, arr, arr[min_idx]);
        }
    }
}

void insertionSort(sf::RenderWindow& window, std::vector<int>& arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        usleep(100000);
        window.clear();
        visual(window, arr, arr[j+1]);
    }
}

void countSort(std::vector<int>& inputArray, int N) {
 
    int M = 0;
 
    for (int i = 0; i < N; i++)
        M = std::max(M, inputArray[i]);
 
    std::vector<int> countArray(M + 1, 0);
 
    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;
 
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];
 
    std::vector<int> outputArray(N);
 
    for (int i = N - 1; i >= 0; i--)
 
    {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
 
        countArray[inputArray[i]]--;
    }
 
    return;
}

//accepts a sorting function, number of elements
void randomize(std::vector<int>& el) {
    
    std::iota(el.begin(), el.end(), 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(el.begin(), el.end(), gen);

    /*for (int i : el) {
        nstd::cout << i << std::endl;
    }*/

    //std::cout << std::endl;

}

void menu(sf::RenderWindow& window) {
    int n, c;

    std::cout << "Enter N: ";
    std::cin >> n;

    std::vector<int> el(n);
    
        while (1) {

            randomize(el);
            std::cout << "Select Sorting Algorithm: " << std::endl;
            std::cin >> c;
            
            if (c == 1) bubbleSort(window, el, n);
            else if (c == 2) selectionSort(window, el, n);
            else if (c == 3) insertionSort(window, el, n);
            else break;

            visual(window, el, -1);
        }
        
}
 
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualization", sf::Style::Titlebar | sf::Style::Close);
 
    window.setFramerateLimit(60);
    
    /*ask for user input
    int n = 37;

    std::vector<int> elements(n);

    randomize(elements);
    */
    
    Button button(window, 0, 100, 25, 150, 140, 12, "test", "./Tiny5.ttf", sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button.checkInput(sf::Mouse::getPosition())) {
            std::cout << sf::Mouse::getPosition().x << " " <<  sf::Mouse::isButtonPressed(sf::Mouse::Left)<< std::endl;    
        }

        window.clear();
        
        button.draw();

        window.display();

        /*menu(window);*/

        /*visual(window, elements, -1);*/

    }

    return 0;
}
