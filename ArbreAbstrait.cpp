#include <stdlib.h>
#include "ArbreAbstrait.h"
#include "Symbole.h"
#include "SymboleValue.h"
#include "Exceptions.h"

////////////////////////////////////////////////////////////////////////////////
// NoeudSeqInst
////////////////////////////////////////////////////////////////////////////////

NoeudSeqInst::NoeudSeqInst() : m_instructions() {
}

int NoeudSeqInst::executer() {
  for (unsigned int i = 0; i < m_instructions.size(); i++)
    m_instructions[i]->executer();    
  return 0; // La valeur renvoyée ne représente rien !
}

void NoeudSeqInst::ajoute(Noeud* instruction) {
  if (instruction!=nullptr) m_instructions.push_back(instruction);
}

////////////////////////////////////////////////////////////////////////////////
// NoeudAffectation
////////////////////////////////////////////////////////////////////////////////

NoeudAffectation::NoeudAffectation(Noeud* variable, Noeud* expression)
: m_variable(variable), m_expression(expression) {
}

int NoeudAffectation::executer() {
  int valeur = m_expression->executer(); // On exécute (évalue) l'expression
  ((SymboleValue*) m_variable)->setValeur(valeur); // On affecte la variable
  return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudOperateurBinaire
////////////////////////////////////////////////////////////////////////////////

NoeudOperateurBinaire::NoeudOperateurBinaire(Symbole operateur, Noeud* operandeGauche, Noeud* operandeDroit)
:m_operateur(operateur), m_operandeGauche(operandeGauche), m_operandeDroit(operandeDroit) {
}

int NoeudOperateurBinaire::executer() {
  int og, od, valeur;
  if (m_operandeGauche != nullptr) og = m_operandeGauche->executer(); // On évalue l'opérande gauche
  if (m_operandeDroit != nullptr) od = m_operandeDroit->executer(); // On évalue l'opérande droit
  // Et on combine les deux opérandes en fonctions de l'opérateur
  if (this->m_operateur == "+") valeur = (og + od);
  else if (this->m_operateur == "-") valeur = (og - od);
  else if (this->m_operateur == "*") valeur = (og * od);
  else if (this->m_operateur == "==") valeur = (og == od);
  else if (this->m_operateur == "!=") valeur = (og != od);
  else if (this->m_operateur == "<") valeur = (og < od);
  else if (this->m_operateur == ">") valeur = (og > od);
  else if (this->m_operateur == "<=") valeur = (og <= od);
  else if (this->m_operateur == ">=") valeur = (og >= od);
  else if (this->m_operateur == "et") valeur = (og && od);
  else if (this->m_operateur == "ou") valeur = (og || od);
  else if (this->m_operateur == "non") valeur = (!og);
  else if (this->m_operateur == "/") {
    if (od == 0) throw DivParZeroException();
    valeur = og / od;
  }
  return valeur; // On retourne la valeur calculée
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

NoeudInstSi::NoeudInstSi(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstSi::executer() {
  if (m_condition->executer()) m_sequence->executer();
  return 0; // La valeur renvoyée ne représente rien !
}

////////////////////////////////////////////////////////////////////////////////
// NoeudInstTantQue
////////////////////////////////////////////////////////////////////////////////
NoeudInstTantQue::NoeudInstTantQue(Noeud* expression,Noeud* sequence)
:m_expression(expression), m_sequence(sequence){
}

int NoeudInstTantQue::executer() {
    while(m_expression->executer()){      
        m_sequence->executer();
    }   
    return 0;
}

///////////////////////////////////////////////////////////
////////////// //////////Repeter/////////////////////////
///////////////////////////////////////////////////////////

NoeudRepeter::NoeudRepeter(Noeud *expression, Noeud *sequence)
:m_expression(expression),m_sequence(sequence){
}

int NoeudRepeter::executer(){
        do{
            cout<<"exec  instruction \n";
            m_sequence->executer();
        }while(m_expression->executer()); //m_expression->executer() == m_sequence->executer();
        cout<<"fin";
        return 0;
}

///////////////////////////////////////////////////////////////
//////////////////////////////SiRiche/////////////////////////
//////////////////////////////////////////////////////////////
NoeudInstSiRiche::NoeudInstSiRiche(vector<Noeud *> v_conditions, vector<Noeud *> v_sequences)
:m_conditions(v_conditions),m_sequences(v_sequences){
    
}

int NoeudInstSiRiche::executer(){  
    for(int i =0; i < m_conditions.size(); i++){
        if(m_conditions[i]->executer()){
            m_sequences[i]->executer();
        }
    }       
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// NoeudInstPour
////////////////////////////////////////////////////////////////////////////////
NoeudInstPour::NoeudInstPour(Noeud* affectationGauche, Noeud* condition, Noeud* affectationDroite, Noeud* sequence)
:m_affectationGauche(affectationDroite), m_condition(condition), m_affectationDroite(affectationDroite), m_sequence(sequence){
}

int NoeudInstPour::executer(){
    //Si les nous n'avons pas les affectations(i =0 et i = i+1) alors
   //on "affecte" les affection puis celle-ci seront exécutée.
    if(m_affectationGauche != NULL && m_affectationDroite != NULL){
        m_affectationGauche->executer();
        m_affectationDroite->executer();
        if(m_condition->executer()){
            while(m_condition->executer()){
                m_sequence->executer();             
            }
        }  
         //Si les nous n'avons pas les affectations(i =0 et i = i+1) alors
        //on execute l'instruction tant que la condition est vraie
    }else if(m_affectationGauche == NULL && m_affectationDroite == NULL){
        if(m_condition->executer())
            while(m_condition->executer()){
                m_sequence->executer();
            }
    }
    return 0;
}

////////////////////////////////////////////////////////
///////////////////LIRE/////////////////////////////////
////////////////////////////////////////////////////////
NoeudInstLire::NoeudInstLire(vector <Noeud*> instructions): v_instructions(instructions){}

int NoeudInstLire::executer(){
    for(auto inst : v_instructions){
        cout<<"Entrez la valeur de : ";
        cout<<((SymboleValue*)inst)->getChaine();
        cout<<"\n";
        long nombreAEntrer;
        cin>>nombreAEntrer;
        ((SymboleValue*)inst)->setValeur(nombreAEntrer);
    }
    return 0;
}