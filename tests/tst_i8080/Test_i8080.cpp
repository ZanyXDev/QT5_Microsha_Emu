#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include  "../../microsha/simple.h"

class Test_i8080 : public QObject
{
    Q_OBJECT

public:
    Test_i8080();
    ~Test_i8080();

private slots:
    void test_init();
    void testNothing();

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

void Test_i8080::testNothing()
{
    Simple s;
    s.setA(3);

    QCOMPARE( s.a(), 3 );
    QCOMPARE( s.a(), 2 );
}

QTEST_MAIN(Test_i8080)

#include "Test_i8080.moc"
