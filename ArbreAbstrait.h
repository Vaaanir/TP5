#ifndef ARBREABSTRAIT_H
#define ARBREABSTRAIT_H

// Contient toutes les déclarations de classes nécessaires
//  pour représenter l'arbre abstrait

#include <vector>
#include <iostream>
#include <iomanip>
#include <typeinfo>
using namespace std;

#include "Symbole.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////
class Noeud {
// Classe abstraite dont dériveront toutes les classes servant à représenter l'arbre abstrait
// Remarque : la classe ne contient aucun constructeur
  public:
    virtual int  executer() =0 ; // Méthode pure (non implémentée) qui rend la classe abstraite
    virtual void ajoute(Noeud* instruction) { throw OperationInterditeException(); }
    virtual void traduitEnCPP(ostream &cout, unsigned int indentation) const { throw OperationInterditeException(); }
    virtual void traduitEnCPPPour(ostream &cout, unsigned int indentation) const { throw OperationInterditeException(); }
    virtual ~Noeud() {} // Présence d'un destructeur virtuel conseillée dans les classes abstraites
};

////////////////////////////////////////////////////////////////////////////////
class NoeudSeqInst : public Noeud {
// Classe pour représenter un noeud "sequence d'instruction"
//  qui a autant de fils que d'instructions dans la séquence
  public:
     NoeudSeqInst();         // Construit une séquence d'instruction vide
    ~NoeudSeqInst() {}       // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute chaque instruction de la séquence
    void ajoute(Noeud* instruction) override;  // Ajoute une instruction à la séquence
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
  private:
    vector<Noeud *> m_instructions; // pour stocker les instructions de la séquence
};

////////////////////////////////////////////////////////////////////////////////
class NoeudAffectation : public Noeud {
// Classe pour représenter un noeud "affectation"
//  composé de 2 fils : la variable et l'expression qu'on lui affecte
  public:
     NoeudAffectation(Noeud* variable, Noeud* expression); // construit une affectation
    ~NoeudAffectation() {}   // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute (évalue) l'expression et affecte sa valeur à la variable
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
    void traduitEnCPPPour(ostream &cout, unsigned int indentation) const override;
  private:
    Noeud* m_variable;
    Noeud* m_expression;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudOperateurBinaire : public Noeud {
// Classe pour représenter un noeud "opération binaire" composé d'un opérateur
//  et de 2 fils : l'opérande gauche et l'opérande droit
  public:
    NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit);
    // Construit une opération binaire : operandeGauche operateur OperandeDroit
   ~NoeudOperateurBinaire() {} // A cause du destructeur virtuel de la classe Noeud
    int executer() override;   // Exécute (évalue) l'opération binaire)
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
  private:
    Symbole m_operateur;
    Noeud*  m_operandeGauche;
    Noeud*  m_operandeDroit;
};

////////////////////////////////////////////////////////////////////////////////
class NoeudInstSi : public Noeud {
// Classe pour représenter un noeud "instruction si"
//  et ses 2 fils : la condition du si et la séquence d'instruction associée
  public:
    NoeudInstSi(Noeud* condition, Noeud* sequence);
     // Construit une "instruction si" avec sa condition et sa séquence d'instruction
   ~NoeudInstSi() {}         // A cause du destructeur virtuel de la classe Noeud
    int executer() override; // Exécute l'instruction si : si condition vraie on exécute la séquence
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
  private:
    Noeud*  m_condition;
    Noeud*  m_sequence;
};
/////////////////////////////////////////////
class NoeudInstTantQue : public Noeud{
    
public : 
    NoeudInstTantQue(Noeud* expression, Noeud* sequence);
    ~NoeudInstTantQue(){}
    int executer() override;
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
private :
    Noeud* m_expression;
    Noeud * m_sequence; 
};

///////////////////////////////////////////////////////////
////////////// //////////SiRiche/////////////////////////
///////////////////////////////////////////////////////////

class NoeudInstSiRiche : public Noeud{
    
public : 
    NoeudInstSiRiche(vector<Noeud *> v_conditions, vector<Noeud *> v_sequences, vector<Noeud *> v_sequencesinon);
    ~NoeudInstSiRiche(){}
    virtual void ajoute(Noeud* instruction)override { throw OperationInterditeException(); }
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
    int executer() override;
private :
    vector <Noeud *>m_conditions;
    vector <Noeud *>m_sequences;
    vector <Noeud *> m_sequencesinon;
    //Lire les trucs, ajouter si if ou sinon dans m_instructions et m_sequences
    //Puis lire m_instruction en même temps que m_sequences pour faire le tout en même temps
};
///////////////////////////////////////////////////////////
////////////// //////////Repeter/////////////////////////
///////////////////////////////////////////////////////////

class NoeudInstRepeter : public Noeud{
    
public : 
    NoeudInstRepeter(Noeud* expression, Noeud *sequence);//Noeud* expression, Noeud* sequence);
    ~NoeudInstRepeter(){}
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
    int executer() override;
private :
    Noeud* m_expression;
    Noeud * m_sequence; 
};

///////////////////////////////////////////////////////////
////////////// //////////Pour/////////////////////////
///////////////////////////////////////////////////////////
class NoeudInstPour : public Noeud{
public:
    NoeudInstPour(Noeud* affectationGauche, Noeud* condition, Noeud* affectationDroite, Noeud* sequence);
    ~NoeudInstPour(){}
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
    int executer() override;
private:
    Noeud* m_condition;
    Noeud* m_sequence;
    Noeud* m_affectationGauche;
    Noeud* m_affectationDroite;
};


///////////////////////////////////////////////////////////
////////////// //////////Ecrire/////////////////////////
///////////////////////////////////////////////////////////
class NoeudInstEcrire : public Noeud{
public:
    NoeudInstEcrire(vector<Noeud*> exp);
    ~NoeudInstEcrire(){}
    int executer() override;
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
private:
    vector<Noeud*> m_exp;
};

///////////////////////////////////////////////////////////
////////////// //////////Lire/////////////////////////
///////////////////////////////////////////////////////////
class NoeudInstLire : public Noeud{
public :
    NoeudInstLire(vector <Noeud *> instructions);
    ~NoeudInstLire(){};
    int executer() override;
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
private :
    vector <Noeud*> v_instructions;
};




///////////////////////////////////////////////////////////
////////////// //////////Selon/////////////////////////
///////////////////////////////////////////////////////////

class NoeudInstSelon : public Noeud{
public : 
    NoeudInstSelon(vector <Noeud *> instructions,vector <Noeud *> sequences,vector <Noeud*>v_instructionDefault, Noeud* condition);
    ~NoeudInstSelon(){}
    int executer()override;
    void traduitEnCPP(ostream &cout, unsigned int indentation) const override;
private : 
    vector <Noeud*> v_instruction;
    vector <Noeud*> v_sequences;
    vector <Noeud *> v_instructionDefault;
    Noeud* m_condition;
};
#endif /* ARBREABSTRAIT_H */
