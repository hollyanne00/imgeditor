imgeditor
=========

A simple c++ application for manipulating the byte data of images 

###Filters

- Invert
  - Inverts image by applying the function f(x) = 255-x to every pixel

- Difference
  - Computes the difference of two images with function d = |a-b|
  
- Median Filter
  - Given a size n, applies an n x n median filter to an image
  - Takes the rgb values of the n x n neighbours of each pixel
  - Sets the final pixel as the median of its neighbours
