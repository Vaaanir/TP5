/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclassTantQue.cpp
 * Author: berguert
 *
 * Created on Nov 6, 2019, 4:07:30 PM
 */

#include "newtestclassTantQue.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclassTantQue);

newtestclassTantQue::newtestclassTantQue() {
}

newtestclassTantQue::~newtestclassTantQue() {
}

void newtestclassTantQue::setUp() {
}

void newtestclassTantQue::tearDown() {
}

void newtestclassTantQue::testNoeudInstTantQue() {
    Noeud* expression;
    Noeud* sequence;
    NoeudInstTantQue noeudInstTantQue(expression, sequence);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclassTantQue::testExecuter() {
    NoeudInstTantQue noeudInstTantQue;
    int result = noeudInstTantQue.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclassTantQue::testTraduitEnCPP() {
    ostream& cout;
    unsigned int indentation;
    NoeudInstTantQue noeudInstTantQue;
    noeudInstTantQue.traduitEnCPP(cout, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

