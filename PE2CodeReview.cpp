  
#include <string>
#include <vector>
#include <iostream>

using namespace std;
static constexpr double pi = 3.14159265358979323846;

class Shape {

    private:
        string shape_type;

    public:
        Shape(string shape_name) { this->shape_type = shape_name; }
        virtual int get_area() = 0;
        string get_shape_type() {
            return this->shape_type;
        }


        /*Returns true if the target shape matches
        an existing element in the vector (same name and area)*/
        bool exists(vector<Shape*> v) {
            for(Shape* s: v) {
                if(s->get_shape_type() == this->shape_type && s->get_area() == this->get_area()) {
                    return true;
                }
            }
            return false;
        }
};

class Square : public Shape {
    private:
        int side_size;

    public:
        Square(int side_size) : Shape("Square") {
            this->side_size = side_size ;
        }

        int get_area() {
            return side_size * side_size;
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

        int get_area() {
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

        int get_area() {
            return pi * radius * radius;
        }

};

/*Class to hold all static methods for excersises*/
class Excercises {
        /*Returns the number of occurences of a given shape*/
        static int count_by_shape(vector<Shape*> v, string shape_name) {
            int total = 0;
            for(int i = 0; i < v.size(); i++) {
                if(v[i]->get_shape_type() == shape_name) {
                    total++;
                }
            }
            return total;

        }

        /*Returns the biggest area of a given vector of shapes*/
        static int largest_area(vector<Shape*> v) {
            int largest = v[0]->get_area();
            for(int i = 0; i < v.size(); i++) {
                if(largest < v[i]->get_area()) {
                    largest = v[i]->get_area();
                }
            }
            return largest;
        }

        /*Returns the average area of all the shapes in a vector*/
        static int average_area(vector<Shape*> v) {
            int total = 0;
            for(int i = 0; i < v.size(); i++) {
                total += v[i]->get_area();
            }
            return total / v.size();
        }

        /*Returns wether a vector contains a duplicate of a shape. 
        A duplicate is defined by a shape having the same type and same area.*/
        static bool has_duplicates(vector<Shape*> v) {
            vector<Shape*> uniques;
            for(Shape* s: v) {
                if (!s->exists(v)) {
                    uniques.push_back(s);
                } else {
                    return true;
                }
            }
            return false;
        }

        /*Removes the first shape with the matching area, regardless of the type of shape.
        Does nothing if the a shape with that area does not exist.*/
        static void remove_first(vector<Shape*> &v, int area) {
            for(int i = 0; i < v.size(); i++) {
                if(v[i]->get_area() == area) {
                    v.erase(v.begin()+i);
                    break;
                }
            }
        }

        /*Removes all the shapes with the matching area, regardless of the type of shape.
        Does nothing if the no shapes with that area exist.*/
        static void remove_all(vector<Shape*> &v, int area) {
            int idx = 0;
            while(idx < v.size()) {
                if(v[idx]->get_area() == area) v.erase(v.begin()+idx);
                idx++;
            }
        }

        /*Returns a new vector which represents the union of 2 vectors.
        A union is defined as a new vector containing unique elements from both vectors.
        Example: v1 = [0 1 2 3 4], v2 = [0 1 5 6 7], union(v1, v2) = [0 1 2 3 4 5 6 7]
        Utilize the exists() method to verify if a shape exists in a specific vector.*/
        static vector<Shape*> vector_union(vector<Shape*> v1, vector<Shape*> v2) {
            for(Shape* s: v2) {
                if(!s->exists(v1)) {
                    v1.push_back(s);
                }
            }
            return v1;
        }

        /*Returns a new vector which represents the intersection of 2 vectors.
        An intersection is defined as a new vector containing the elements that are contained in both vectors.
        Example: v1 = [0 1 2 3 4], v2 = [0 1 5 6 7], intersection(v1, v2) = [0 1]
        Utilize the exists() method to verify if a shape exists in a specific vector.*/
        static vector<Shape*> vector_intersection(vector<Shape*> v1, vector<Shape*> v2) {
            vector<Shape*> intersect;
            for(Shape* s: v1) {
                if(s->exists(v2)) {
                    intersect.push_back(s);
                }
            }
            return intersect;
        }
};