#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono> 
#include <thread>
#include <iostream>
#include<stdio.h>
sf::RenderWindow window(sf::VideoMode(1575, 720), "QuickSort Visualization");

void drawArr(int arr[], int g1, int g2, int p)
{
    window.clear();
    for (int i = 0; i < 100; i++)
    {
        sf::RectangleShape rec(sf::Vector2f(10, arr[i]*7));
        if(i == g1 || i == g2)
            rec.setFillColor(sf::Color::Green);
        else if (i == p)
            rec.setFillColor(sf::Color::Blue);
        else
            rec.setFillColor(sf::Color::White);        
        rec.setOutlineColor(sf::Color::Black);
        rec.setOutlineThickness(1);
        rec.setPosition(45+i*15, 720 - (arr[i]*7) / 2.0);
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
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    for (int j = low; j <= high- 1; j++)
    {   
        drawArr(arr, i, j, high);
        window.display();
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(arr, i, j);
        }
        drawArr(arr, i, j, high);
        window.display();
    }
    swap(arr, i + 1, high);
    return (i + 1);
}
 
void checkIfSorted(int arr[], int min, int max)
{
    bool notSorted = false;
    window.setFramerateLimit(15);
    for (int i = min; i < max && !notSorted; i++)
    {   
        window.clear();
        int s = 0;
        
        if( i+1 < max && arr[i+1] >= arr[i] && !notSorted)
        {
           s = i;  
        }
        else{ 
            notSorted = true;         
        }
        for(int j = 0; j < 100;j++)
        {
            sf::RectangleShape rec(sf::Vector2f(10, arr[j]*7));
            rec.setOutlineThickness(1);
            rec.setPosition(45+j*15, 720 - (arr[j]*7) / 2.0);
            if( j>=min && j <= s && j < max)
            {
                rec.setFillColor(sf::Color::Green);     
            }
            else{
                rec.setFillColor(sf::Color::White);            
            }
            window.draw(rec);
        }
        window.display();
    }
    window.setFramerateLimit(60);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    
    //checkIfSorted(arr, low, high+1);
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        drawArr(arr, -1, -1, -1);
        window.display(); 
        int pi = partition(arr, low, high);
        
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
    drawArr(arr, -1, -1, -1);
    window.display();
}


int main()
{
    window.setFramerateLimit(60);
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        window.setMouseCursor(cursor);
    int offset = 50;
    int randArray[100];
    for(int i=0;i<100;i++)
      randArray[i]=rand()%101;  //Generate number between 0 to 100

    quickSort(randArray, 0, 99);
    for(int i=0;i<100;i++)
      std::cout << randArray[i] << " "; 
    window.close();
    sf::Event event;
    return 0;
}