#include <vector>
#include <iostream>
using std::vector;

#define HEIGHT 5
#define WIDTH 5

int main() {
  vector<vector<double> > array2D;

  // Set up sizes. (HEIGHT x WIDTH)
  array2D.resize(HEIGHT);
  for (int i = 0; i < HEIGHT; ++i)
    array2D[i].resize(WIDTH);

  // Put some values in
  for(int i=0;i<HEIGHT;i++)
  {
      for(int j=0;j<WIDTH;j++)
      {
          array2D[i][j] = i+j;
      }
  }


  for(int i=0;i<HEIGHT;i++)
  {
      for(int j=0;j<WIDTH;j++)
      {
          std::cout<<array2D[i][j]<<"\t";
      }
      std::cout<<std::endl;
  }


  return 0;
}