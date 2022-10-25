  
#include <string>
#include <vector>
#include <iostream>
#define pi 3.14159265358979323846

using namespace std;

class Shape {

    private:
        string shapeType;

    public:
        Shape(string shapeName) { this->shapeType = shapeName; }
        virtual double getArea() = 0;
        string getShapeType() {
            return this->shapeType;
        }


        /*Returns true if the target shape matches
        an existing element in the vector (same name and area)*/
        bool exists(vector<Shape*> v) {
            for(Shape* s: v) {
                if(s->getShapeType() == this->shapeType && s->getArea() == this->getArea()) {
                    return true;
                }
            }
            return false;
        }
};

class Square : public Shape {
    private:
        int sideSize;

    public:
        Square(int sideSize) : Shape("Square") {
            this->sideSize = sideSize ;
        }

        double getArea() {
            return sideSize * sideSize;
        }
};

class Triangle : public Shape {

    private:
        int base;
        int height;
    
    public:
        Triangle(int base, int height) : Shape("Triangle"){
            this->base = base;
            this->height = height;
        }

        double getArea() {
            return (base * height) / 2;
        }
};

class Circle : public Shape {
    private:
        int radius;

    public:
        Circle(int radius) : Shape("Circle") {
            this->radius = radius;
        }

        
        double getArea() {
            return pi * radius * radius;
        }

};

/*Class to hold all static methods for excersises*/
class Excercises {
        /*Returns the number of occurences of a given shape*/
        static int countByShape(vector<Shape*> v, string shape_name) {
            int total = 0;
            for(int i = 0; i < v.size(); i++) {
                if(v[i]->getShapeType() == shape_name) {
                    total++;
                }
            }
            return total;

        }

        /*Returns the biggest area of a given vector of shapes*/
        static double largestArea(vector<Shape*> v) {
            double largest = v[0]->getArea();
            for(int i = 0; i < v.size(); i++) {
                if(largest < v[i]->getArea()) {
                    largest = v[i]->getArea();
                }
            }
            return largest;
        }

        /*Returns the average area of all the shapes in a vector*/
        static int averageArea(vector<Shape*> v) {
            double total = 0;
            for(int i = 0; i < v.size(); i++) {
                total += v[i]->getArea();
            }
            return total / v.size();
        }

        /*Returns wether a vector contains a duplicate of a shape. 
        A duplicate is defined by a shape having the same type and same area.*/
        static bool hasDuplicates(vector<Shape*> v) {
            vector<Shape*> uniques;
            for(Shape* s: v) {
                if (!s->exists(uniques)) {
                    uniques.push_back(s);
                } else {
                    return true;
                }
            }
            return false;
        }

        /*Removes the first shape with the matching area, regardless of the type of shape.
        Does nothing if the a shape with that area does not exist.*/
        static void removeFirst(vector<Shape*> &v, int area) {
            for(int i = 0; i < v.size(); i++) {
                if(v[i]->getArea() == area) {
                    v.erase(v.begin()+i);
                    break;
                }
            }
        }

        /*Removes all the shapes with the matching area, regardless of the type of shape.
        Does nothing if the no shapes with that area exist.*/
        static void removeAll(vector<Shape*> &v, int area) {
            int idx = 0;
            while(idx < v.size()) {
                if(v[idx]->getArea() == area) v.erase(v.begin()+idx);
                idx++;
            }
        }

        /*Returns a new vector which represents the union of 2 vectors.
        A union is defined as a new vector containing unique elements from both vectors.
        Example: v1 = [0 1 2 3 4], v2 = [0 1 5 6 7], union(v1, v2) = [0 1 2 3 4 5 6 7]
        Utilize the exists() method to verify if a shape exists in a specific vector.*/
        static vector<Shape*> vectorUnion(vector<Shape*> v1, vector<Shape*> v2) {

            vector<Shape*> v_union = vector<Shape*>(v1);

            for(Shape* s: v2) {
                if(!s->exists(v1)) {
                    v_union.push_back(s);
                }
            }
            return v_union;
        }

        /*Returns a new vector which represents the intersection of 2 vectors.
        An intersection is defined as a new vector containing the elements that are contained in both vectors.
        Example: v1 = [0 1 2 3 4], v2 = [0 1 5 6 7], intersection(v1, v2) = [0 1]
        Utilize the exists() method to verify if a shape exists in a specific vector.*/
        static vector<Shape*> vectorIntersection(vector<Shape*> v1, vector<Shape*> v2) {
            vector<Shape*> intersect;
            for(Shape* s: v1) {
                if(s->exists(v2)) {
                    intersect.push_back(s);
                }
            }
            return intersect;
        }
};