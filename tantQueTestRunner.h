/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   tantQueTestRunner.h
 * Author: berguert
 *
 * Created on Nov 6, 2019, 2:29:27 PM
 */

#ifndef TANTQUETESTRUNNER_H
#define TANTQUETESTRUNNER_H

#include <cppunit/extensions/HelperMacros.h>

class tantQueTestRunner : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(tantQueTestRunner);

    CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testTraduitEnCPP);

    CPPUNIT_TEST_SUITE_END();

public:
    tantQueTestRunner();
    virtual ~tantQueTestRunner();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testSyntaxe();
    void testValeur();
    void testExecuter();
    void testTraduitEnCPP();

};

#endif /* TANTQUETESTRUNNER_H */

