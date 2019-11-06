/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testTantQue.h
 * Author: berguert
 *
 * Created on Nov 6, 2019, 3:59:38 PM
 */

#ifndef TESTTANTQUE_H
#define TESTTANTQUE_H

#include <cppunit/extensions/HelperMacros.h>

class testTantQue : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testTantQue);

    CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testTraduitEnCPP);

    CPPUNIT_TEST_SUITE_END();

public:
    testTantQue();
    virtual ~testTantQue();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testExecuter();
    void testTraduitEnCPP();

};

#endif /* TESTTANTQUE_H */

