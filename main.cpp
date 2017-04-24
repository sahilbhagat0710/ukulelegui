#include "mainwindow.h"
#include <QApplication>


//Main program with an instance of the device
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Ukulele device1;

    Point2D centerOval;
    centerOval.x = centerOval.y = 0;

    device1.set_headOval(10, 5, centerOval);
    device1.set_neck(25, 7);
    device1.set_tail(8, 4);
    device1.set_strings(20);

    production valid_ukulele_copies;

    vector<Ukulele> Ten_Ukuleles = valid_ukulele_copies.packaged_ukulele(device1, 10);
    storage_container packed_stored;
    packed_stored.reserve_pack(Ten_Ukuleles);

    return a.exec();
}
