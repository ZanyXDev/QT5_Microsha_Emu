#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include  "../../microsha/i8080.h"

class Test_i8080 : public QObject
{
    Q_OBJECT

public:
    Test_i8080();
    ~Test_i8080();

private slots:
    void test_init();

};

Test_i8080::Test_i8080()
{

}

Test_i8080::~Test_i8080()
{

}

void Test_i8080::test_init()
{

}



QTEST_MAIN(Test_i8080)

#include "Test_i8080.moc"
