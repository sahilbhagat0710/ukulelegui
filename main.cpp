#include "mainwindow.h"
#include <QApplication>


//Main program with an instance of the device
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Producing 1 Ukulele for testing if it is valid or not
        cout << "*****               << 1 >>                *****" << endl;
        Ukulele device1;

                Point2D centerOval;
                centerOval.x = centerOval.y = 0;
                device1.set_headOval(10, 5, centerOval);
                device1.head.set_majorminor(8.8, 5.4);


                // setting center  and radius of the circles of the Ukulele
                device1.head.set_hcircles(-4, 0, 4, 0, 3.4);

                device1.set_neck(25, 7);
                device1.set_tail(8, 4);
                device1.set_strings(20);

                // Initializing a factory
                Ukulele_factory factory1;

                // General information

                factory1.factory_name = "Ukulele Co.";
                factory1.factory_id = 12345;
                factory1.factory_location = "Berlin";
                factory1.factory_area = 126374;
                factory1.licence = "#1356BBRE";

                // validity tests
                cout << factory1.valid_product(device1) << endl;;
                if (factory1.valid_product(device1) == true){
                    cout << "The specifications of the demanded Ukulele fulfills requirements" << endl;;
                }else{
                    cout << "Not a valid product... exiting.." << endl;;
                    exit(0);
                }
                factory1.print_factory_info();
                factory1.print_testUku();


                // Putting the number of heads, tails, strings and neck in the stock by calling in the supplier
                factory1.he1.hsname = "head wood works and brothers";
                factory1.st1.ssname = "real iron suppliers";
                factory1.ne1.nsname = "perfect wood co";
                factory1.te1.rename = "wood craft and supply";

                // Initial stock in the factory
                // initial demand from the supplier is 10,8,7 and 4 parts.
                cout << "Initially there is no stock so we refill the stock in factory" << endl;
                factory1.refill_head(10);
                factory1.refill_neck(8);
                factory1.refill_string(7);
                factory1.refill_tail(4);

                // printing the supply

                factory1.he1.print_head();
                factory1.st1.print_string();
                factory1.ne1.print_neck();
                factory1.te1.print_end();

                factory1.production_phase(device1, 7);

                //factory1.print_production();

                factory1.factory_storage();
                //factory1.print_storage();
                factory1.item_list.company_name = "Music Mylife retailers --";
                factory1.item_list.location = "Bremen";
                bool isSupplied = factory1.factory_supply(5);
                if(isSupplied == true){
                    cout << "The product is supplied" << endl;
                } else{
                    cout << "We need to produce!!!!!! Out of Ukulele!!!";
                }
                factory1.print_supply();

        cout << "*****               << 2 >>                *****" << endl;

                factory1.production_phase(device1, 14);
                factory1.factory_storage();
                isSupplied = factory1.factory_supply(10);
                if(isSupplied == true){
                    cout << "The product is supplied" << endl;
                } else{
                    cout << "We need to produce!!!!!! Out of Ukulele!!!";
                }
                factory1.print_supply();


         // Producing 1 Ukulele for testing if it is valid or not

    return a.exec();
}
