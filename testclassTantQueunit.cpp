/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclassTantQueunit.cpp
 * Author: berguert
 *
 * Created on Nov 6, 2019, 4:27:54 PM
 */

#include "testclassTantQueunit.h"
#include "ArbreAbstrait.h"
#include "Interpreteur.h"
#include "Exceptions.h"

CPPUNIT_TEST_SUITE_REGISTRATION(testclassTantQueunit);

testclassTantQueunit::testclassTantQueunit() {
}

testclassTantQueunit::~testclassTantQueunit() {
}

void testclassTantQueunit::setUp() {
}

void testclassTantQueunit::tearDown() {
}




void testclassTantQueunit::testSyntaxe(){
    string nomFich = "test02-TantQue.txt";
    ifstream fichier(nomFich.c_str());
    try {
        if (fichier.fail()) throw FichierException();
        Interpreteur interpreteur(fichier);
        interpreteur.analyse();
        if (!interpreteur.getNbErreurs()) {
            if (interpreteur.getArbre() != nullptr) interpreteur.getArbre()->executer();
            // Et on vérifie qu'il a fonctionné en regardant comment il a modifié la table des symboles
            interpreteur.traduitEnCPP(cout,0);
            CPPUNIT_ASSERT(true);
        } else
            cout << interpreteur.getNbErreurs() << " erreur(s) de syntaxe" << endl;
    } catch (InterpreteurException & e) {
        CPPUNIT_ASSERT(false);
    }
}

