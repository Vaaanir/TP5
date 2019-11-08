/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclasstantque.cpp
 * Author: berguert
 *
 * Created on Nov 7, 2019, 10:17:20 AM
 */

#include "testclasstantque.h"
#include "ArbreAbstrait.h"
#include "Exceptions.h"
#include "Interpreteur.h"
#include "Symbole.h"
CPPUNIT_TEST_SUITE_REGISTRATION(testclasstantque);

testclasstantque::testclasstantque() {
}

testclasstantque::~testclasstantque() {
}

void testclasstantque::setUp() {
}

void testclasstantque::tearDown() {
}



void testclasstantque::testExecuter() {
    string nomFich = "test02-TantQue.txt";
    ifstream fichier(nomFich.c_str());
    try {
        if (fichier.fail()) throw FichierException();
        Interpreteur interpreteur(fichier);
        interpreteur.analyse();
        if (!interpreteur.getNbErreurs()) {
            if (interpreteur.getArbre() != nullptr){
                //Test syntaxe
                CPPUNIT_ASSERT_NO_THROW(interpreteur.getArbre()->executer());  
                string finInstruction = "fintantque";
                string variableATester = "test1";
                //Test Variables
                int j = 0;
                    for(int i = 0;i < interpreteur.getTable().getTaille(); i++){
                        if(interpreteur.getTable()[i] == variableATester)
                       // cout<<SymboleValue(interpreteur.getTable()[i]).getChaine() <<"\n";
                       // cout<<SymboleValue(interpreteur.getTable()[i]).executer();
                        j = i;
                    }       
                 CPPUNIT_ASSERT_EQUAL(11,SymboleValue(interpreteur.getTable()[j]).executer());
            }
            // Et on vérifie qu'il a fonctionné en regardant comment il a modifié la table des symboles
            interpreteur.traduitEnCPP(cout,0);   
        } else
            cout << interpreteur.getNbErreurs() << " erreur(s) de syntaxe" << endl;
    } catch (InterpreteurException & e) {
        cout<< e.what();
    }
}




