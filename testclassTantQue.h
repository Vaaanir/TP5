/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclassTantQue.h
 * Author: berguert
 *
 * Created on Nov 6, 2019, 4:14:01 PM
 */

#ifndef TESTCLASSTANTQUE_H
#define TESTCLASSTANTQUE_H

#include <cppunit/extensions/HelperMacros.h>

class testclassTantQue : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testclassTantQue);

    CPPUNIT_TEST(testNoeudInstTantQue);
//    CPPUNIT_TEST(testExecuter);
 //   CPPUNIT_TEST(testTraduitEnCPP);
    CPPUNIT_TEST(testSyntaxe);
    CPPUNIT_TEST_SUITE_END();

public:
    testclassTantQue();
    virtual ~testclassTantQue();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testSyntaxe();
    void testExecuter();
    void testTraduitEnCPP();

};

#endif /* TESTCLASSTANTQUE_H */

