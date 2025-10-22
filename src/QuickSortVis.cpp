#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <chrono> 
#include <thread>
#include <iostream>
#include<stdio.h>

int arr_size = 200; //Change this to alter the array to sort size

const int WINDOW_WIDTH = 1575;
const int WINDOW_HEIGHT = 720;
const int RECTANGLE_WIDTH = WINDOW_WIDTH / (arr_size);

void drawArr(int arr[], int g1, int g2, int p, sf::RenderWindow& window)
{   
    window.clear();
    for (int i = 0; i < arr_size; i++)
    {
        float rec_height = (WINDOW_HEIGHT)*arr[i]/arr_size;

        // Create a rectangle shape
        sf::RectangleShape rec(sf::Vector2f(RECTANGLE_WIDTH, rec_height));
        if(i == g1 || i == g2)
            rec.setFillColor(sf::Color::Green);
        else if (i == p)
            rec.setFillColor(sf::Color::Blue);
        else
            rec.setFillColor(sf::Color::White);        
        rec.setOutlineColor(sf::Color::Black);
        rec.setOutlineThickness(1);
        rec.setPosition(sf::Vector2f((RECTANGLE_WIDTH+1)*i,WINDOW_HEIGHT/2-((rec_height) / 2.0)));
        window.draw(rec);

 
    }
}

static void swap(int arr[], int i, int j)
{
    
    int* a = &arr[i];
    int* b = &arr[j];

    int t = *a;
    
    *a = *b;

    *b = t;

}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high, sf::RenderWindow& window)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++)
    {   
        drawArr(arr, i, j, high, window);
        window.display();
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(arr, i, j);
        }
        drawArr(arr, i, j, high, window);
        window.display();
    }
    swap(arr, i + 1, high);
    return (i + 1);
}
 

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high, sf::RenderWindow& window)
{
    
    //checkIfSorted(arr, low, high+1);
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        drawArr(arr, -1, -1, -1, window);
        window.display(); 
        int pi = partition(arr, low, high, window);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1, window);
        quickSort(arr, pi + 1, high, window);
    }
    drawArr(arr, -1, -1, -1, window);
    window.display();
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "QuickSort Visualization");

    window.setFramerateLimit(60);
    sf::Cursor cursor(sf::Cursor::Type::Arrow);
    window.setMouseCursor(cursor);
    int offset = 50;
    
    int randArray[arr_size];
    for(int i=0;i<arr_size;i++)
      randArray[i]=rand()%arr_size;  

    quickSort(randArray, 0, arr_size-1, window);
    for(int i=0;i<arr_size;i++)
      std::cout << randArray[i] << "\n "; 
    window.close();
    return 0;
}