/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclassTantQue.h
 * Author: berguert
 *
 * Created on Nov 6, 2019, 4:07:30 PM
 */

#ifndef NEWTESTCLASSTANTQUE_H
#define NEWTESTCLASSTANTQUE_H

#include <cppunit/extensions/HelperMacros.h>

class newtestclassTantQue : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(newtestclassTantQue);

    CPPUNIT_TEST(testNoeudInstTantQue);
    CPPUNIT_TEST(testExecuter);
    CPPUNIT_TEST(testTraduitEnCPP);

    CPPUNIT_TEST_SUITE_END();

public:
    newtestclassTantQue();
    virtual ~newtestclassTantQue();
    void setUp();
    void tearDown();

private:
    void testNoeudInstTantQue();
    void testExecuter();
    void testTraduitEnCPP();

};

#endif /* NEWTESTCLASSTANTQUE_H */

