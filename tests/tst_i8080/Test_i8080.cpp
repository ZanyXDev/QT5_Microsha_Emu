#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class Test_i8080 : public QObject
{
    Q_OBJECT

public:
    Test_i8080();
    ~Test_i8080();

private slots:
    void test_case1();

};

Test_i8080::Test_i8080()
{

}

Test_i8080::~Test_i8080()
{

}

void Test_i8080::test_case1()
{

}

QTEST_MAIN(Test_i8080)

#include "Test_i8080.moc"
