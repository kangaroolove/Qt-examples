#pragma once

#include <QObject>
#include <QTest>

class TestFunctions : public QObject {
    Q_OBJECT
public:
    TestFunctions();
    ~TestFunctions();
private slots:
    void testSum();
    void testSumError();
};