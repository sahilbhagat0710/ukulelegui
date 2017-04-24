#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

// Point class for the circle and ellipse
class Point2D{
public:
    double x, y;
    Point2D(){
        x = y = 0;
    }
};

// This is what makes up the neck and tail of Ukulele
class Rectangle{
public:
    double length, width;
    Rectangle(){
        length = width = 0;
    }
    bool valid_rectangle(){
        if(length <= 0 || width <= 0) return false;
        return true;
    }
    void set_LW(double ll, double ww){
        length = ll;
        width = ww;
    }
};

// This is the inner circle of the head of Ukulele
class circle{
public:
    double radius;
    Point2D center;
    circle(){
        radius = 2;
        center.x = center.y = 0;
    }
    bool valid_circle(){
        if(radius <= 0) return false;
        return true;
    }

};

// This is a class of a single string for Ukulele
class strings{
public:
    string material, color;
    double scost, slength;
    strings(){
        slength = 12;
        scost = 0;
    }

    bool valid_string(){
        if(slength <= 0){
            return false;
        }
        return true;
    }
};
class string_pack{
public:
    strings s1, s2, s3, s4;
    double sslengths;
    string_pack(){
        sslengths = 0;
    }
    void setstrlengths(double length){
        s1.slength = s2.slength = s3.slength = s4.slength = length;
    }

};
// This is actually the outer ellipse that makes up the major part of head.
class Ellipse{
public:
    double a, b;
    Point2D ecenter;
    Ellipse(){
        a = 7;
        b = 4;
        ecenter.x = ecenter.y = 0;
    }
    void set_ecenter(double val1, double val2){
        ecenter.x = val1;
        ecenter.y = val2;
    }

    bool valid_ellipse(){
        if(a <= 0 || b <= 0) return false;
        return true;
    }
};

// The main head part which has Oval and two circles in it.
class Head{
public:
    Ellipse oval;
    circle c1, c2;
    double Hcost;
    Head(){
        oval.a = oval.b = 0;
        Hcost = 0;
        c1.radius = c2.radius = 0;
        c1.center.x = c2.center.y =0;
    }

    bool valid_Head(){
        bool res = true;
        double dist = sqrt(pow((c2.center.x- c1.center.x), 2)-pow((c2.center.y - c1.center.y), 2));
        if(dist == 0)
            res = false;
        if(dist < c1.radius || dist < c2.radius)
            res = false;
        return res;
    }
    void set_ecenter(double val1, double val2){
        oval.ecenter.x = val1;
        oval.ecenter.y = val2;
    }
    void set_majorminor(double ea, double eb){
        oval.a = ea;
        oval.b = eb;
    }
    void set_hcircles(double x1, double x2, double y1, double y2, double r1){
        c1.radius = r1;
        c2.radius = r1;
        c1.center.x = x1;
        c2.center.y = y1;
        c1.center.x = x2;
        c2.center.y = y2;
    }
};

// This is the class which is the final product with 1. head 2. neck 3. tail 4. four strings
class Ukulele{
public:
    string material, color;
    double Tcost;
    Head head;
    Rectangle neck, tail;
    string_pack str;
    Ukulele(){
        Tcost = 0;
    }

    void set_headOval(double a1, double b1, Point2D cent){
        head.oval.a = a1;
        head.oval.b = b1;
        head.set_ecenter(cent.x, cent.y);
    }
    void set_neck(double x, double y){
        neck.length = x;
        neck.width = y;
    }
    void set_tail(double x, double y){
        tail.length = x;
        tail.width = y;
    }
    void set_strings(double l){
        str.setstrlengths(l);
    }

    void set_shead(Head hh){
        head.set_ecenter(hh.oval.ecenter.x, hh.oval.ecenter.y);
        head.set_majorminor(hh.oval.a, hh.oval.b);
        head.set_hcircles(hh.c1.center.x, hh.c1.center.y, hh.c2.center.x, hh.c2.center.y, hh.c1.radius);
    }
    void set_sstrings(string_pack ss){
        str.s1.slength = str.s2.slength = str.s3.slength = str.s4.slength = ss.s1.slength;
    }
    void set_sneck(Rectangle nn){
        neck.set_LW(nn.length, nn.width);
    }
    void set_stail(Rectangle tt){
        tail.set_LW(tt.length, tt.width);
    }
};

// supplier for the head
class Head_supplier{
public:
    double head_cost;
    int numHead;
    Head_supplier(){
        head_cost = numHead = 0;
    }
    vector<Head> supply_head(Head hh, int n){
        vector<Head> ret;
        for(int i = 0; i < n; i++){
            ret.push_back(hh);
        }
        return ret;
    }

};
class strings_supplier{
public:
    double strings_cost;
    int numstrings;
    strings_supplier(){
        numstrings = 0;
    }
    vector<string_pack> supply_string(string_pack ss, int n){
        vector<string_pack> ret;
        for(int i = 0; i < n; i++){
            ret.push_back(ss);
        }
        return ret;
    }

};
// supplier for the neck
class neck_supplier{
public:
    double neck_cost;
    int numNeck;
    neck_supplier(){
        numNeck = 0;
    }
    vector<Rectangle> supply_neck(Rectangle nn, int n){
        vector<Rectangle> ret;
        for(int i = 0; i < n; i++){
            ret.push_back(nn);
        }
        return ret;
    }
};
// supplier for the rectangular end
class Rectangular_end_supplier{
public:
    double End_cost;
    int numEnd;
    Rectangular_end_supplier(){
        numEnd = 0;
    }
    vector<Rectangle> supply_end(Rectangle en, int n){
        vector<Rectangle> ret;
        for(int i = 0; i < n; i++){
            ret.push_back(en);
        }
        return ret;
    }

};

// final production class
class production{
public:
    double Production_cost;
    int numdemand;
    production(){
        numdemand = 0;
    }
    vector<Ukulele> packaged_ukulele(Ukulele Uprod, int n){
        vector <Ukulele> demandedUkulele;
        Head_supplier H1;
        strings_supplier S1;
        neck_supplier N1;
        Rectangular_end_supplier R1;
        vector<Head> heads = H1.supply_head(Uprod.head, n);
        vector<string_pack> strs = S1.supply_string(Uprod.str, n);
        vector<Rectangle> necks = N1.supply_neck(Uprod.neck,n);
        vector<Rectangle> tails = R1.supply_end(Uprod.tail, n);
        for(int i = 0; i < n ; i++){
            Ukulele x;
            x.set_shead(heads[i]);
            x.set_sstrings(strs[i]);
            x.set_sneck(necks[i]);
            x.set_stail(tails[i]);
            demandedUkulele.push_back(x);
        }
        return demandedUkulele;
    }

};
class package{
public:
    double serial_number;
    double blen, bwid, bheight;
    Ukulele item;
    package(){
        serial_number = 0;
    }
    void set_pack(int num){
        serial_number = num;
    }
};

class storage_container{
public:
    double storeCost;
    double storeTime;
    double volume;
    vector <package> packed_item;
    storage_container(){
        storeCost = 0;
    }
    void reserve_pack(vector<Ukulele> items){
        package pacitm;
        for(unsigned int i = 0; i < items.size(); i++){
            pacitm.serial_number = i;
            pacitm.item = items[i];
            packed_item.push_back(pacitm);
        }
    }

};



#endif // MAINWINDOW_H
