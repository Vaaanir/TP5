/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclassTantQueunit.h
 * Author: berguert
 *
 * Created on Nov 6, 2019, 4:27:54 PM
 */

#ifndef TESTCLASSTANTQUEUNIT_H
#define TESTCLASSTANTQUEUNIT_H

#include <cppunit/extensions/HelperMacros.h>

class testclassTantQueunit : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testclassTantQueunit);

   // CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testSyntaxe);
    //CPPUNIT_TEST(testExecuter);
    //CPPUNIT_TEST(testTraduitEnCPP);

    CPPUNIT_TEST_SUITE_END();

public:
    testclassTantQueunit();
    virtual ~testclassTantQueunit();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testSyntaxe();
    void testExecuter();
    void testTraduitEnCPP();

};

#endif /* TESTCLASSTANTQUEUNIT_H */

