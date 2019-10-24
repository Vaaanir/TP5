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

void NoeudSeqInst::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    for (unsigned int i = 0; i < m_instructions.size(); i++){
        m_instructions[i]->traduitEnCPP(cout,indentation);
    }
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

void NoeudAffectation::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    cout << setw(4*indentation)<<""<<((SymboleValue*)m_variable)->getChaine();
    cout<<"=";
    if((typeid(*m_expression) == typeid(SymboleValue))){
        cout<<((SymboleValue*)m_expression)->getChaine();
    }else{
        m_expression->traduitEnCPP(cout,0);
    }
    
    cout<<";"<<endl; 
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

void NoeudOperateurBinaire::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    cout<< setw(4*indentation)<<""<<((SymboleValue*)m_operandeGauche)->getChaine();
    cout<<m_operateur.getChaine();
    cout<<((SymboleValue*)m_operandeDroit)->getChaine();
}
//////////////////////////////////////////////////////////////////////////
// NoeudInstSi
////////////////////////////////////////////////////////////////////////////////

NoeudInstSi::NoeudInstSi(Noeud* condition, Noeud* sequence)
: m_condition(condition), m_sequence(sequence) {
}

int NoeudInstSi::executer() {
  if (m_condition->executer()) m_sequence->executer();
  return 0; // La valeur renvoyée ne représente rien !
}

void NoeudInstSi::traduitEnCPP(ostream & cout,unsigned int indentation)const{  
    cout << setw(4*indentation)<<""<<"if (";// Ecrit "if (" avec un décalage de 4*indentation espaces   
    m_condition->traduitEnCPP(cout,0);// Traduit la condition en C++ sans décalage   
    cout <<") {"<< endl;// Ecrit ") {" et passe à la ligne   
    m_sequence->traduitEnCPP(cout, indentation+1);// Traduit en C++ la séquence avec indentation augmentée   
    cout << setw(4*indentation)<<""<<"}"<< endl;// Ecrit "}" avec l'indentation initiale et passe à la ligne 
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

void NoeudInstTantQue::traduitEnCPP(ostream &cout, unsigned int indentation) const {
    cout<<setw(4*indentation) << ""<<"while (";
    m_expression->traduitEnCPP(cout,indentation);
    cout<<"){"<<endl;
        m_sequence->traduitEnCPP(cout,indentation+1);
        cout<<setw(indentation*4)<<""<< "}" << endl;

}

///////////////////////////////////////////////////////////
////////////// //////////Repeter/////////////////////////
///////////////////////////////////////////////////////////

NoeudInstRepeter::NoeudInstRepeter(Noeud *expression, Noeud *sequence)
:m_expression(expression),m_sequence(sequence){
}

int NoeudInstRepeter::executer(){
        do{
            cout<<"exec  instruction \n";
            m_sequence->executer();
        }while(m_expression->executer()); //m_expression->executer() == m_sequence->executer();
        cout<<"fin";
        return 0;
}
void NoeudInstRepeter::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    cout<<setw(4*indentation) <<""<<"do {" << endl;
    m_sequence->traduitEnCPP(cout,indentation);
    cout<<"} while (";
    m_expression->traduitEnCPP(cout,indentation);
    cout<<setw(indentation*4)<<""<<")" <<endl;
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
void NoeudInstSiRiche::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    cout<<setw(4*indentation)<<""<<"if (";
    for(int i =0; m_conditions.size();i++){
        if(i !=0){
            if(i = m_conditions.size()){
                cout<<setw(4*indentation)<<""<<"else(";
            }else {
                 cout<<setw(4*indentation)<<""<<"else if(";
            }
        }
        m_conditions[i]->traduitEnCPP(cout,indentation);
        cout<<") {" <<endl;
            m_sequences[i]->traduitEnCPP(cout,indentation);
        cout<<"}" <<endl;
    cout<<"}" <<endl;
    }
    
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
void NoeudInstPour::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    
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
void NoeudInstLire::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    
}