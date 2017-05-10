#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <QMainWindow>
#include <QDebug>
#include <cstdlib>
#include <fstream>

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
    double rrcost;
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
        scost = 20;
        material = "";
        color = "";
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
    double strcost;
    string_pack(){
        strcost = s1.scost*4 + 20;
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
        Hcost = 200;
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
    void set_hcircles(double x1, double y1, double x2, double y2, double r1){
        c1.radius = r1;
        c2.radius = r1;
        c1.center.x = x1;
        c2.center.x = x2;
        c1.center.y = y1;
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
        color = "Brown";
        material = "Mahogany";
        neck.rrcost = 80;
        tail.rrcost = 80;
        Tcost = neck.rrcost + tail.rrcost + head.Hcost + str.strcost;

    }
    Ukulele operator = (const Ukulele &obj) {
        head.c1.center.x = obj.head.c1.center.x;
        head.c1.center.y = obj.head.c1.center.y;
        head.c2.center.x = obj.head.c2.center.x;
        head.c2.center.y = obj.head.c2.center.y;
        head.c1.radius = obj.head.c1.radius;
        head.c2.radius = obj.head.c2.radius;
        head.oval.a = obj.head.oval.a;
        head.oval.b = obj.head.oval.b;
        head.oval.ecenter.x = obj.head.oval.ecenter.x;
        head.oval.ecenter.y = obj.head.oval.ecenter.y;
        neck.length = obj.neck.length;
        neck.width = obj.neck.width;
        tail.length = obj.tail.length;
        tail.width = obj.tail.width;
        str.setstrlengths(obj.str.s1.slength);
        return *this;
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
    void print_device(){
        cout << "Information about Ukulele" << endl;
        cout << "--------------------------" << endl;
        cout << "Color of Ukulele: " << color << endl;
        cout << "Material used: " << material << endl;
        cout << "1. Head  " << endl;
        cout << "  circles centered at (" << head.c1.center.x<<","<< head.c1.center.y<<") and (" <<head.c2.center.x<<","<< head.c2.center.y<<")" << endl;
        cout << "  Radius: " << head.c1.radius << endl;
        cout << "  cost:" << head.Hcost << endl;
        cout << "2. strings";
        cout << "  Length: " << str.s1.slength << endl;
        cout << "  Cost: " << str.strcost << endl;
        cout << "3. neck" << endl;
        cout << "  Length: " << neck.length << " and Width " << neck.width << endl;
        cout << "  cost: " << neck.rrcost << endl;
        cout << "4. tail" << endl;
        cout << "  Length: " << tail.length << " and Width " << tail.width << endl;
        cout << "  cost: " << tail.rrcost << endl;
        cout << "---- Total Cost:  " << Tcost << endl;
        cout << endl;

    }
    void printUinfo(){
        cout << "| Color of Ukulele: " << color << endl;
        cout << "| Material used: " << material << endl;
        cout << "| Head: (" << head.c1.center.x<<","<< head.c1.center.y<<") and (" <<head.c2.center.x<<","<< head.c2.center.y<<")" <<"R= " << head.c1.radius << endl;
        cout << "| Strings: " << "L = " << str.s1.slength << "C = " << str.strcost << endl;
        cout << "| Neck: " << "L = " << neck.length << "B = " << neck.width << "C = " << neck.rrcost << endl;
        cout << "| Tail: " << "L = " << tail.length << "B = " << tail.width  << "C = " << tail.rrcost << endl;
        cout << "| Total: " << Tcost << endl;
    }
};

// supplier for the head
class Head_supplier{
public:
    string hsname;
    double head_cost;
    int numHead;
    Head_supplier(){
        head_cost = 0;
        numHead = 0;
    }
    void supply_head(Head hh, vector<Head>& v, int n){
        numHead = n;
        head_cost = hh.Hcost * double(n);
        for(int i = 0; i < n; i++){
            v.push_back(hh);
        }
    }
    void print_head(){
        cout << "Head supplier: " << hsname << endl;
        cout << "Total head supply cost: " << head_cost << endl;
        cout << "Number of head: " << numHead << endl;
        cout << endl;
    }

};
class strings_supplier{
public:
    string ssname;
    double strings_cost;
    int numstrings;
    strings_supplier(){
        ssname ="";
        numstrings = 0;
        strings_cost = 0;
    }
    void supply_string(string_pack ss, vector<string_pack> &v, int n){
        numstrings = n;
        strings_cost = ss.strcost*double(n);
        for(int i = 0; i < n; i++){
            v.push_back(ss);
        }
    }
    void print_string(){
        cout << "String supplier: " << ssname << endl;
        cout << "Total string supply cost: " << strings_cost << endl;
        cout << "Number of string: " << numstrings << endl;
        cout << endl;
    }

};
// supplier for the neck
class neck_supplier{
public:
    string nsname;
    double neck_cost;
    int numNeck;
    neck_supplier(){
        nsname = "";
        numNeck = 0;
        neck_cost = 0;
    }
    void supply_neck(Rectangle nn, vector<Rectangle>& v,int n){
        numNeck = n;
        neck_cost = nn.rrcost*double(n);
        for(int i = 0; i < n; i++){
            v.push_back(nn);
        }
    }
    void print_neck(){
        cout << "neck supplier: " << nsname << endl;
        cout << "Total neck supply cost: " << neck_cost << endl;
        cout << "Number of neck: " << numNeck << endl;
        cout << endl;
    }
};
// supplier for the rectangular end
class Rectangular_end_supplier{
public:
    string rename;
    double End_cost;
    int numEnd;
    Rectangular_end_supplier(){
        rename = "";
        numEnd = 0;
        End_cost = 0;
    }
    void supply_end(Rectangle en, vector<Rectangle>& v, int n){
        numEnd = n;
        End_cost = double(n)*en.rrcost;

        for(int i = 0; i < n; i++){
            v.push_back(en);
        }
    }
    void print_end(){
        cout << "End supplier: " << rename  << endl;
        cout << "Total end supply cost: " << End_cost << endl;
        cout << "Number of end: " << numEnd << endl;
        cout << endl;
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
    void printpack(){
        cout << "-----------------------------------------" << endl;
        cout << "Retriving package with serial number #" << serial_number << endl;
        item.printUinfo();
        cout << "-----------------------------------------" << endl;
        cout << endl;

    }
};

class storage_container{
public:
    double storeCost;
    double storeTime;
    double volume;
    int capacity;
    vector <package> packed_item;
    storage_container(){
        storeCost = 0;
        capacity = 100;
        volume = 1000;
    }
    void reserve_pack(vector<Ukulele>& items){
        package pacitm;
        for(unsigned int i = 0; i < items.size(); i++){
            pacitm.serial_number = i+1;
            pacitm.item = items[i];
            packed_item.push_back(pacitm);
        }
        items.clear();
    }
    int number_items(){
        return (packed_item.size());
    }
    void print_container(){
        cout << " ************Container*************" << endl;
        for(unsigned int i = 0; i < packed_item.size(); i++){
            package x = packed_item[i];
            x.printpack();
        }
    }
    int get_item_pack(){
        return packed_item.size();
    }

};

class supply_ukulele{
public:
    string company_name;
    int supply_amount;
    string location;
    double price;
    supply_ukulele(){
        company_name = "";
        location = "";
        supply_amount = 0;
        price = 80;
    }
    bool supply(storage_container& it, int number){
        if(it.packed_item.size() > 0){
            supply_amount = number;
            price = double(80.0*number);
            for(int i = 0; i < number; i++){
                it.packed_item.pop_back();
            }
            return true;
        } else{
            return false;
        }
    }
    void printSUP(){
        cout << "-----------------Supply product by the factory -----------------" << endl;
        cout << " Company Name:   " << company_name << endl;
        cout << " Location:    " << location << endl;
        cout << " Number of items supplied:   " << supply_amount << endl;
        cout << " Total Price:  " << price << endl;
        cout << endl;

    }

};

class supplier_diary{
public:
    // supplier input from a database
    int NOhead, NOneck, NOstring, NOtail;
    ofstream copy;
    ofstream outfile;
    supplier_diary(){
        NOhead = NOneck = NOstring = NOtail = 0;
        ifstream infile;
        vector<int> input;
        infile.open("supplier.txt");
        if (infile.is_open())
        {
            int in = 0;
            while (infile >> in){
                input.push_back(in);
                in = 0;
            }
            NOhead = input[0];
            NOneck = input[1];
            NOstring = input[2];
            NOtail = input[3];
            input.clear();
        } else{
            cout << "Invalid file" << endl;
            exit(0);
        }
        infile.close();
        remove("supplier.txt");
        if(NOhead <= 0) NOhead=500;
        if(NOneck <= 0) NOneck = 500;
        if(NOstring <= 0) NOstring = 500;
        if(NOtail <= 0) NOtail = 500;
        copy.open("supplier.txt");
        outfile.open("result.txt");
        outfile << "****************************************************************" << endl;
    }
    void value_change_head(int h){
        if(NOhead <= 0) NOhead=500;
        if(NOhead > 0) NOhead = NOhead - h;
    }
    void value_change_neck(int n){
        if(NOneck <= 0) NOneck = 500;
        if(NOneck > 0) NOneck = NOneck - n;

    }
    void value_change_str(int s){
        if(NOstring <= 0) NOstring = 500;
        if(NOstring > 0) NOstring = NOstring - s;
    }
    void value_change_tail(int t){
        if(NOtail <= 0) NOtail = 500;
        if(NOtail > 0) NOtail = NOtail - t;
    }
    void update_print(){
        outfile << " The number of items in supply: " << endl;
        outfile << "  Head -> " << NOhead << endl;
        outfile << "  Tail -> " << NOtail << endl;
        outfile << "  Neck -> " << NOneck << endl;
        outfile << "  strings in pack -> " << NOstring << endl;
        outfile << endl;
    }
    ~supplier_diary(){
        if(NOhead <= 0) NOhead=500;
        if(NOneck <= 0) NOneck = 500;
        if(NOstring <= 0) NOstring = 500;
        if(NOtail <= 0) NOtail = 500;
        copy << NOhead << endl;
        copy << NOtail << endl;
        copy << NOneck << endl;
        copy << NOstring << endl;
        outfile << "****************************************************************" << endl;
        outfile << endl;
        copy.close();
        outfile.close();
    }

};

class Ukulele_factory{
public:
    // general info
    string factory_name;
    int factory_id;
    string factory_location;
    double factory_area;
    string licence;
    // products
    vector<Ukulele> produced_Ukuleles;
    vector<Head> inhead;
    vector<Rectangle> inneck;
    vector<Rectangle> intail;
    vector<string_pack> instr;
    Ukulele ideal_ukulele;
    int default_prod;
    // storage and supply
    storage_container scontain;
    supply_ukulele item_list;
    //suppliers
    Head_supplier he1;
    neck_supplier ne1;
    strings_supplier st1;
    Rectangular_end_supplier te1;
    supplier_diary file;


    Ukulele_factory(){
        factory_name = "";
        factory_id = 0;
        factory_location = "";
        factory_area = 0;
        licence = "";
        default_prod = 10;
    }
    bool valid_product(Ukulele item1){
        // validity tests
                bool proceed = false;
                bool result = false;
                if(item1.head.valid_Head() == true && item1.head.oval.valid_ellipse() == true && item1.str.s1.valid_string() == true)
                    proceed = true;
                else{
                    return false;
                }
                if(proceed == true && item1.neck.valid_rectangle() == true && item1.tail.valid_rectangle()==true)
                    result = true;
                else{
                    return false;
                }
                file.outfile << " The Ukulele is valid..." << endl;
                ideal_ukulele = item1;
        return result;
    }
    void refill_head(int nohead){
        he1.supply_head(ideal_ukulele.head, inhead, nohead);
        file.value_change_head(nohead);
    }
    void refill_neck(int noneck){
        ne1.supply_neck(ideal_ukulele.neck, inneck, noneck);
        file.value_change_neck(noneck);
    }
    void refill_string(int nostr){
        st1.supply_string(ideal_ukulele.str, instr, nostr);
        file.value_change_str(nostr);
    }
    void refill_tail(int notail){
        te1.supply_end(ideal_ukulele.tail, intail, notail);
        file.value_change_tail(notail);
    }

    void production_phase(Ukulele item1, int number){
        if(scontain.packed_item.size()>0)
            number = number - scontain.packed_item.size();
        ideal_ukulele = item1;
        int reshead = inhead.size();
        int restail = intail.size();
        int resneck = inneck.size();
        int resstr = instr.size();
        cout << endl;
        cout << "-----------------------stock stats before producing -----------------" << endl;
        cout << " The requested number of Ukulele:   " << number << endl;
        cout << " The number of items in stock: " << endl;
        cout << "  Head -> " << reshead << endl;
        cout << "  Tail -> " << restail << endl;
        cout << "  Neck -> " << resneck << endl;
        cout << "  strings in pack -> " << resstr << endl;
        cout << endl;
        int difH = reshead - number;
        int difT = restail - number;
        int difN = resneck - number;
        int difS = resstr - number;

        if(difH < 0){
            int hx = abs(difH);
            refill_head(hx);
            difH = difH + hx;
            cout << "Insufficient head, so asked supplier to refill by << " << hx << " >> amount" << endl;
            file.outfile << "Insufficient head, so asked supplier to refill by << " << hx << " >> amount" << endl;
        }
        if(difT < 0){
            int tx = abs(difT);
            refill_tail(tx);
            difT = difT + tx;
            cout << "Insufficient tail, so asked supplier to refill by << " << tx << " >> amount" << endl;
            file.outfile << "Insufficient tail, so asked supplier to refill by << " << tx << " >> amount" << endl;
        }
        if(difN < 0){
            int nx = abs(difN);
            refill_neck(nx);
            difN = difN + nx;
            cout << "Insufficient neck, so asked supplier to refill by << " << nx << " >> amount" << endl;
            file.outfile << "Insufficient neck, so asked supplier to refill by << " << nx << " >> amount" << endl;
        }
        if(difS < 0){
            int sx = abs(difS);
            refill_string(sx);
            difS = difS + sx;
            cout << "Insufficient string pack, so asked supplier to refill by << " << sx << " >> amount" << endl;
            file.outfile << "Insufficient string pack, so asked supplier to refill by << " << sx << " >> amount" << endl;
        }
        if(difH >= 0 && difT >= 0 && difN >= 0 && difS>=0){
            for(int i = 0; i < number; i++){
                Ukulele x;
                x.set_shead(inhead[i]);
                x.set_sstrings(instr[i]);
                x.set_sneck(inneck[i]);
                x.set_stail(intail[i]);
                produced_Ukuleles.push_back(x);
                inhead.pop_back();
                instr.pop_back();
                inneck.pop_back();
                intail.pop_back();
            }
        }
        cout << "-----------------------stock stats after producing -----------------" << endl;
        cout << " The number of items in stock: " << endl;
        cout << "  Head -> " << inhead.size() << endl;
        cout << "  Tail -> " << intail.size() << endl;
        cout << "  Neck -> " << inneck.size() << endl;
        cout << "  strings in pack -> " << instr.size() << endl;
        cout << endl;

        file.outfile << "-----------------------supply stats after producing -----------------" << endl;
        file.update_print();


        cout << "Automatic refill done by calling supplier if item in stock runs out .." << endl;
        if(difH == 0) refill_head(default_prod);
        if(difT == 0) refill_tail(default_prod);
        if(difN == 0) refill_neck(default_prod);
        if(difS == 0) refill_string(default_prod);
        cout << endl;

        cout << "------------------stock stats after refill if zero left -------------" << endl;
        cout << " The number of items in stock: " << endl;
        cout << "  Head -> " << inhead.size() << endl;
        cout << "  Tail -> " << intail.size() << endl;
        cout << "  Neck -> " << inneck.size() << endl;
        cout << "  strings in pack -> " << instr.size() << endl;
        cout << endl;

        file.outfile << "--------------supply stats after refill if zero left -----------------" << endl;
        file.update_print();

    }
    void factory_storage(){
        scontain.reserve_pack(produced_Ukuleles);
    }
    void print_storage(){
        scontain.print_container();
    }
    bool factory_supply(int num){
        bool result = item_list.supply(scontain, num);
        return result;
    }
    void print_supply(){
        item_list.printSUP();
        cout << " Remaining Ukulele in stock:   " << scontain.packed_item.size() << endl;
    }
    void print_factory_info(){
                cout << "The information about the factory" << endl;
                cout << "--------------------------------" << endl;
                cout << "   Factory Name: " << factory_name << endl;
                cout << "   Factory Id: " << factory_id << endl;
                cout << "   Factory Location: " << factory_location << endl;
                cout << "   Area covered: " << factory_area << endl;
                cout << "   Location: " << factory_location << endl;
                cout << "   License no.: " << licence << endl;
                cout << endl;
    }
    void print_production(){
        for(unsigned int i = 0; i < produced_Ukuleles.size(); i++){
            Ukulele x;
            x = produced_Ukuleles[i];
            x.print_device();
        }
    }

    void print_testUku(){
        ideal_ukulele.print_device();
    }
};





#endif // MAINWINDOW_H
