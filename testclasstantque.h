/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclasstantque.h
 * Author: berguert
 *
 * Created on Nov 7, 2019, 10:17:19 AM
 */

#ifndef TESTCLASSTANTQUE_H
#define TESTCLASSTANTQUE_H


#include <cppunit/extensions/HelperMacros.h>

class testclasstantque : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testclasstantque);

//    CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testExecuter);
  //  CPPUNIT_TEST(testTraduitEnCPP);

    CPPUNIT_TEST_SUITE_END();

public:
    testclasstantque();
    virtual ~testclasstantque();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testExecuter();
    void testTraduitEnCPP();

};

#endif /* TESTCLASSTANTQUE_H */

