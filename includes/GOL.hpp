//
//  GOL.hpp
//  xCodeImplement
//
//  Created by Travis Gershon on 11/30/19.
//  Copyright © 2019 Travis Gershon. All rights reserved.
//

#ifndef GOL_hpp
#define GOL_hpp

#include <stdio.h>

  
#include <iostream>
#include "Node.hpp"
class GOL {
public:
    static int generationIteration;
    static int NNODES;
    Node* m_pNodes;
    const Node * const getNodes() { return m_pNodes; };
    GOL(){
    
        int M = 50, N = 100;
  
        // Intiliazing the grid.
        int ** grid;
        grid = new int*[N];
        
        for (int i = 0; i < M; ++i) {
          grid[i] = new int[N];
          // each i-th pointer is now pointing to dynamic array (size 10) of actual int values
        }
        
        for (int i = 0; i < M; ++i) {   // for each row
          for (int j = 0; j < N; ++j) { // for each column
           grid[i][j] = 0;
          }
        }
        
        grid[1][3] = 1;
        grid[1][4] = 1;
        grid[2][4] = 1;
        grid[6][3] = 1;
        grid[6][4] = 1;
        grid[7][2] = 1;
        grid[7][3] = 1;
        grid[1][8] = 1;
 
        grid[2][8] = 1;
                grid[1][9] = 1;
        // Displaying the grid
        std::cout << "Original Generation" << std::endl;
        
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 0)
                   std::cout << ".";
                else
                    std::cout << "*";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
   
        nextGeneration(grid, M, N);
    }
  
    // Function to print next generation
    static void nextGeneration(int** grid, int M, int N)
    {
        int** future  = new int*[N];
        for (int i = 0; i < M; ++i) {
                 future[i] = new int[N];
                 // each i-th pointer is now pointing to dynamic array (size 10) of actual int values
        }
        for (int i = 0; i < M; ++i) {   // for each row
          for (int j = 0; j < N; ++j) { // for each column
           future[i][j] = grid[i][j];
          }
        }
        
  
        // Loop through every cell
        for (int l = 1; l < M - 1; l++)
        {
            for (int m = 1; m < N - 1; m++)
            {
                  
                // finding # Of Neighbours
                // that are alive
                int aliveNeighbours = 0;
                for (int i = -1; i <= 1; i++){
                    for (int j = -1; j <= 1; j++){
                        aliveNeighbours += grid[l + i][m + j];
                    }
                }
  
                // The cell needs to be subtracted
                // from its neighbours as it was
                // counted before
                aliveNeighbours -= grid[l][m];
  
                // Implementing the Rules of Life
  
                // Cell is lonely and dies
                if ((grid[l][m] == 1) && (aliveNeighbours < 2))
                {
                   future[l][m] = 0;
                }// Cell dies due to over population
                else if ((grid[l][m] == 1) && (aliveNeighbours > 3))
                {
                    future[l][m] = 0;
                }// A new cell is born
                else if ((grid[l][m] == 0) && (aliveNeighbours >= 2))
                {
                    // Remains the same
                    future[l][m] = 1;
                    
                } else{
                    future[l][m] = grid[l][m];
                }
            }
        }
  
       
                                
        std::cout << "Next Generation" <<std::endl;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (future[i][j] == 0)
                    std::cout << ".";
                else
                    std::cout << "*";
            }
            std::cout << std::endl;
        }
        
        generationIteration++;
     
        
        delete[] future;
        
    }
};


#endif /* GOL_hpp */
