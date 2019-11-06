/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclassTantQue.cpp
 * Author: berguert
 *
 * Created on Nov 6, 2019, 4:14:01 PM
 */

#include "testclassTantQue.h"
#include "ArbreAbstrait.h"


CPPUNIT_TEST_SUITE_REGISTRATION(testclassTantQue);

testclassTantQue::testclassTantQue() {
}

testclassTantQue::~testclassTantQue() {
}

void testclassTantQue::setUp() {
}

void testclassTantQue::tearDown() {
}

void testclassTantQue::testNoeudInstTantQue() {
    Noeud* expression;
    Noeud* sequence;
    NoeudInstTantQue noeudInstTantQue(expression, sequence);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(true);
    }
}

void testclassTantQue::testSyntaxe(){
    string nomFich = "TestTantQ";
    ifstream fichier(nomFich.c_str());
    try {
        if (fichier.fail()) throw FichierException();
        Interpreteur interpreteur(fichier);
        interpreteur.analyse();
        // Si pas d'exception levée, l'analyse syntaxique a réussi
        cout << endl << "================ Syntaxe Correcte" << endl;
        // On affiche le contenu de la table des symboles avant d'exécuter le programme
        cout << endl << "================ Table des symboles avant exécution : " << interpreteur.getTable();
        cout << endl << "================ Execution de l'arbre" << endl;
        // On exécute le programme si l'arbre n'est pas vide
        if (interpreteur.getArbre() != nullptr) interpreteur.getArbre()->executer();
        // Et on vérifie qu'il a fonctionné en regardant comment il a modifié la table des symboles
        cout << endl << "================ Table des symboles apres exécution : " << interpreteur.getTable();
        interpreteur.traduitEnCPP(cout,0);
    } catch (InterpreteurException & e) {
        cout << e.what() << endl;
    }
}





