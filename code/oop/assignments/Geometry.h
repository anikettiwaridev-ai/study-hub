#ifndef GEOMETRY_H
#define GEOMETRY_H

// The guard stops the header being pasted twice into ONE .cpp file.
// 'inline' is what stops two DIFFERENT .cpp files each producing a
// definition that the linker then sees twice.

inline double rectangleArea(double l, double b)      { return l * b; }
inline double rectanglePerimeter(double l, double b) { return 2 * (l + b); }
inline double circleArea(double r)                   { return 3.14159 * r * r; }
inline double circlePerimeter(double r)              { return 2 * 3.14159 * r; }
inline double squareArea(double s)                   { return s * s; }
inline double squarePerimeter(double s)              { return 4 * s; }

#endif
