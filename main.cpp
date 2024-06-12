#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include "button.hpp"

#define WIDTH 600
#define HEIGHT 400
#define PADDING 20
#define HERE "*"

void visual(sf::RenderWindow& window, std::vector<int> el, int m) {
    int n = el.size();
    window.clear();
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
                visual(window, arr, arr[j]);
            }
        }

        if (swapped == false)
            break;

        /*visual(window, arr, -1);*/
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
            usleep(100000);
            visual(window, arr, arr[min_idx]);
        }
    }
    /*visual(window, arr, -1);*/
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
        visual(window, arr, arr[j+1]);
    }
    /*visual(window, arr, -1);*/
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

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting Visualization");
 
    window.setFramerateLimit(60);
    
    int n = 37;

    std::vector<int> elements(n);

    randomize(elements);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
    
        bubbleSort(window, elements, n);

        visual(window, elements, -1);
    }

    return 0;
}
