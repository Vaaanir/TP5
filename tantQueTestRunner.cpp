/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   tantQueTestRunner.cpp
 * Author: berguert
 *
 * Created on Nov 6, 2019, 2:29:27 PM
 */
 #include <cppunit/extensions/TestFactoryRegistry.h>
 #include <cppunit/CompilerOutputter.h>
 #include <cppunit/TestResult.h>
 #include <cppunit/TestResultCollector.h>
 #include <cppunit/TestRunner.h>
 #include <cppunit/TextTestProgressListener.h>
#include "tantQueTestRunner.h"
#include "ArbreAbstrait.h"
#include <iostream>
#include <fstream>
#include "Interpreteur.h"
#include "Exceptions.h"
CPPUNIT_TEST_SUITE_REGISTRATION(tantQueTestRunner);

tantQueTestRunner::tantQueTestRunner() {
}

tantQueTestRunner::~tantQueTestRunner() {
}

void tantQueTestRunner::setUp() {
}

void tantQueTestRunner::tearDown() {
}
//Ouvrir mon fichier TestTantQue.txt
//Avancer tant qu'on atteint pas la 1ere instruction genre  "test1" 
//Effectuer les sequences 1 par 1
void tantQueTestRunner::testNoeudInstTantQue() {
    Noeud* expression;
    Noeud* sequence;
    NoeudInstTantQue noeudInstTantQue(expression, sequence);
}
    
    
    }
    





