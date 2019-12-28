#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class Test_i8255 : public QObject
{
    Q_OBJECT

public:
    Test_i8255();
    ~Test_i8255();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

Test_i8255::Test_i8255()
{

}

Test_i8255::~Test_i8255()
{

}

void Test_i8255::initTestCase()
{

}

void Test_i8255::cleanupTestCase()
{

}

void Test_i8255::test_case1()
{

}

QTEST_MAIN(Test_i8255)

#include "Test_i8255.moc"
