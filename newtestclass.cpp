/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   newtestclass.cpp
 * Author: berguert
 *
 * Created on Nov 6, 2019, 3:55:16 PM
 */

#include "newtestclass.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(newtestclass);

newtestclass::newtestclass() {
}

newtestclass::~newtestclass() {
}

void newtestclass::setUp() {
}

void newtestclass::tearDown() {
}

void newtestclass::testNoeudInstTantQue() {
    Noeud* expression;
    Noeud* sequence;
    NoeudInstTantQue noeudInstTantQue(expression, sequence);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testExecuter() {
    NoeudInstTantQue noeudInstTantQue;
    int result = noeudInstTantQue.executer();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void newtestclass::testTraduitEnCPP() {
    ostream& cout;
    unsigned int indentation;
    NoeudInstTantQue noeudInstTantQue;
    noeudInstTantQue.traduitEnCPP(cout, indentation);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

