/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testTantQue.cpp
 * Author: berguert
 *
 * Created on Nov 6, 2019, 3:59:38 PM
 */

#include "testTantQue.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(testTantQue);

testTantQue::testTantQue() {
}

testTantQue::~testTantQue() {
}

void testTantQue::setUp() {
}

void testTantQue::tearDown() {
}

void testTantQue::testNoeudInstTantQue() {
    Noeud* expression;
    Noeud* sequence;
    NoeudInstTantQue noeudInstTantQue(expression, sequence);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void testTantQue::testExecuter() {
    NoeudInstTantQue noeudInstTantQue;
    int result = noeudInstTantQue.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void testTantQue::testTraduitEnCPP() {
    ostream& cout;
    unsigned int indentation;
    NoeudInstTantQue noeudInstTantQue;
    noeudInstTantQue.traduitEnCPP(cout, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

