#include <iostream>
#include <algorithm>
#include <random>
#include <unistd.h>
#include <SFML/Graphics.hpp>


#define WIDTH 600
#define HEIGHT 400
#define PADDING 20

typedef void (*SortingAlgo)(std::vector<int>&, int);

void visual(sf::RenderWindow& window, std::vector<int> el) {
    int n = el.size();
    for (int i; i < n; i++){
        sleep(1);
        int h, w, x, y;
        h = el[i] * ((HEIGHT - 2 * PADDING) / (n-1));
        w = (WIDTH - 20 * PADDING) / (n-1);
        x = 200 + (i * 1.1 * w); 
        y = HEIGHT;
        
        std::cout << el[i] << " " << h << " " << w << " " << x << " " << y << std::endl;
        sf::RectangleShape rectangle(sf::Vector2f(w, h));

        rectangle.setPosition(x, y);
        rectangle.rotate(180);
        window.draw(rectangle);
    }
    window.display();
    std::cout << std::endl;
}

void bubbleSort(sf::RenderWindow& window, std::vector<int>& arr, int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
                visual(window, arr);
            }
        }

        if (swapped == false)
            break;
    }
}

//accepts a sorting function, number of elements
void randomize(std::vector<int>& el) {
    
    std::iota(el.begin(), el.end(), 1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(el.begin(), el.end(), gen);

    for (int i : el) {
        std::cout << i << std::endl;
    }

    std::cout << std::endl;

}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualization");
    //sf::RectangleShape rectangle(sf::Vector2f(20.f, 20.f));
    //rectangle.setPosition(300, 200);
    window.setFramerateLimit(60);
    
    //ask for user input
    int n = 10;

    std::vector<int> elements(n);

    randomize(elements);

    bubbleSort(window, elements, n-1);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        //window.draw(rectangle);        
        //window.display();

    }

    return 0;
}
