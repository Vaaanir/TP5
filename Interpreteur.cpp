#include "Interpreteur.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Interpreteur::Interpreteur(ifstream & fichier) :
m_lecteur(fichier), m_table(), m_arbre(nullptr) {
}

void Interpreteur::analyse() {
  m_arbre = programme(); // on lance l'analyse de la première règle
}

bool Interpreteur::tester(const string & symboleAttendu) const {
  // Teste si le symbole courant est égal au symboleAttendu... Si non, lève une exception
  static char messageWhat[256];
  if (m_lecteur.getSymbole() != symboleAttendu) {
    sprintf(messageWhat,
            "Ligne %d, Colonne %d - Erreur de syntaxe - Symbole attendu : %s - Symbole trouvé : %s",
            m_lecteur.getLigne(), m_lecteur.getColonne(),
            symboleAttendu.c_str(), m_lecteur.getSymbole().getChaine().c_str());
    cout << messageWhat << endl;
    return false;
  }else{
      return true;
  }
}

void Interpreteur::testerEtAvancer(const string & symboleAttendu) {
  // Teste si le symbole courant est égal au symboleAttendu... Si oui, avance, Sinon, lève une exception
  if(tester(symboleAttendu)){
    m_lecteur.avancer();
  }
}

void Interpreteur::erreur(const string & message) const {
  // Lève une exception contenant le message et le symbole courant trouvé
  // Utilisé lorsqu'il y a plusieurs symboles attendus possibles...
  static char messageWhat[256];
  sprintf(messageWhat,
          "Ligne %d, Colonne %d - Erreur de syntaxe - %s - Symbole trouvé : %s",
          m_lecteur.getLigne(), m_lecteur.getColonne(), message.c_str(), m_lecteur.getSymbole().getChaine().c_str());
  cout << messageWhat << endl;
}

Noeud* Interpreteur::programme() {
  // <programme> ::= procedure principale() <seqInst> finproc FIN_FICHIER
        testerEtAvancer("procedure");
        testerEtAvancer("principale");
        testerEtAvancer("(");
        testerEtAvancer(")");
        Noeud* sequence = seqInst();
        testerEtAvancer("finproc");
        tester("<FINDEFICHIER>");
        return sequence;
    }

Noeud* Interpreteur::seqInst() {
  // <seqInst> ::= <inst> { <inst> }
  NoeudSeqInst* sequence = new NoeudSeqInst();
  do {
    sequence->ajoute(inst());

  } while (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "si" || m_lecteur.getSymbole() == "tantque" 
          || m_lecteur.getSymbole() == "repeter" ||m_lecteur.getSymbole() == "pour" || m_lecteur.getSymbole() == "ecrire" || m_lecteur.getSymbole() == "lire");
  // Tant que le symbole courant est un début possible d'instruction...
  // Il faut compléter cette condition chaque fois qu'on rajoute une nouvelle instruction
  return sequence;
}

Noeud* Interpreteur::inst() {
  // <inst> ::= <affectation>  ; | <instSi> | <instTantQue>
  if (m_lecteur.getSymbole() == "<VARIABLE>") {
    Noeud *affect = affectation();
    testerEtAvancer(";");
    return affect;
  }
  else if (m_lecteur.getSymbole() == "si"){
    return instSiRiche();
  }
  else if(m_lecteur.getSymbole() == "tantque"){
   return instTantQue();
  }
  else if(m_lecteur.getSymbole() == "repeter"){
      return instRepeter();
  }  
  else if(m_lecteur.getSymbole() == "pour"){
      return instPour();
  }
  else if(m_lecteur.getSymbole() == "ecrire"){
      return instEcrire();
  }
  else if(m_lecteur.getSymbole() == "lire"){
      return instLire();
  }
  // Compléter les alternatives chaque fois qu'on rajoute une nouvelle instruction
  else {
      erreur("Instruction incorrecte");
      return nullptr;
    }
}

Noeud* Interpreteur::affectation() {
  // <affectation> ::= <variable> = <expression> 
  tester("<VARIABLE>");
  Noeud* var = m_table.chercheAjoute(m_lecteur.getSymbole()); // La variable est ajoutée à la table et on la mémorise
  m_lecteur.avancer();
  testerEtAvancer("=");
  Noeud* exp = expression();             // On mémorise l'expression trouvée
  return new NoeudAffectation(var, exp); // On renvoie un noeud affectation
}

Noeud* Interpreteur::expression() {
  // <expression> ::= <expEt> { ou <expEt> }
  Noeud* exp = expEt();
  while (m_lecteur.getSymbole() == "ou") {
    Symbole operateur = m_lecteur.getSymbole(); // On mémorise le symbole de l'opérateur
    m_lecteur.avancer();
    Noeud* expDroit = expEt(); // On mémorise l'opérande droit
    exp = new NoeudOperateurBinaire(operateur,exp,expDroit); // Et on construit un noeud opérateur binaire
  }
  return exp; // On renvoie exp qui pointe sur la racine de l'expression
}

Noeud* Interpreteur::expEt(){
  // <expEt> ::= <expComp> { et <expComp> }
    Noeud* exp = expComp();
    while(m_lecteur.getSymbole() == "et"){
        Symbole operateur = m_lecteur.getSymbole();
        m_lecteur.avancer();
        Noeud* expDroit = expComp();
        exp = new NoeudOperateurBinaire(operateur,exp,expDroit);
    }
    return exp;
}

Noeud* Interpreteur::expComp(){
  // <expComp> ::= expAdd> { == | != | < | <= | > | >= <expAdd> }
    Noeud* exp = expAdd();
    while(m_lecteur.getSymbole() == "<"  || m_lecteur.getSymbole() == "<=" ||
          m_lecteur.getSymbole() == ">"  || m_lecteur.getSymbole() == ">=" ||
          m_lecteur.getSymbole() == "==" || m_lecteur.getSymbole() == "!="){
        Symbole operateur = m_lecteur.getSymbole();
        m_lecteur.avancer();
        Noeud* expDroit = expAdd();
        exp = new NoeudOperateurBinaire(operateur,exp,expDroit);
    }
    return exp;
}

Noeud* Interpreteur::expAdd(){
  // <expAdd> ::= <expMult> { + | - <expMult> }
    Noeud* exp = expMult();
    while(m_lecteur.getSymbole() == "+"  || m_lecteur.getSymbole() == "-"){
        Symbole operateur = m_lecteur.getSymbole();
        m_lecteur.avancer();
        Noeud* expDroit = expMult();
        exp = new NoeudOperateurBinaire(operateur,exp,expDroit);
    }
    return exp;
}

Noeud* Interpreteur::expMult(){
  // <expMult> ::= <facteur> { * | / <facteur> }
    Noeud* fact = facteur();
    while(m_lecteur.getSymbole() == "*"  || m_lecteur.getSymbole() == "/" ){
        Symbole operateur = m_lecteur.getSymbole();
        m_lecteur.avancer();
        Noeud* facDroit = facteur();
        fact = new NoeudOperateurBinaire(operateur,fact,facDroit);
    }
    return fact;
}

Noeud* Interpreteur::facteur() {
  // <facteur> ::= <entier> | <variable> | - <facteur> | non <facteur> | ( <expression> )
  Noeud* fact = nullptr;
  if (m_lecteur.getSymbole() == "<VARIABLE>" || m_lecteur.getSymbole() == "<ENTIER>" || m_lecteur.getSymbole() == "<CHAINE>") {
    fact = m_table.chercheAjoute(m_lecteur.getSymbole()); // on ajoute la variable ou l'entier à la table
    m_lecteur.avancer();
  } else if (m_lecteur.getSymbole() == "-") { // - <facteur>
    m_lecteur.avancer();
    // on représente le moins unaire (- facteur) par une soustraction binaire (0 - facteur)
    fact = new NoeudOperateurBinaire(Symbole("-"), m_table.chercheAjoute(Symbole("0")), facteur());
  } else if (m_lecteur.getSymbole() == "non") { // non <facteur>
    m_lecteur.avancer();
    // on représente le moins unaire (- facteur) par une soustractin binaire (0 - facteur)
    fact = new NoeudOperateurBinaire(Symbole("non"), facteur(), nullptr);
  } else if (m_lecteur.getSymbole() == "(") { // expression parenthésée
    m_lecteur.avancer();
    fact = expression();
    testerEtAvancer(")");
  } else
    erreur("Facteur incorrect");
  return fact;
}

Noeud* Interpreteur::instSi() {
  // <instSi> ::= si ( <expression> ) <seqInst> finsi
  testerEtAvancer("si");
  testerEtAvancer("(");
  Noeud* condition = expression(); // On mémorise la condition
  testerEtAvancer(")");
  Noeud* sequence = seqInst();     // On mémorise la séquence d'instruction
  testerEtAvancer("finsi");
  return new NoeudInstSi(condition, sequence); // Et on renvoie un noeud Instruction Si
}

void Interpreteur::traduitEnCPP(ostream &cout, unsigned int indentation) const{
    cout<<"#include <iostream> \n";
    cout<<"using namespace std \n";
    cout<<"\n";
    cout<< setw(4*indentation) << "" << "int main(){" << endl;
    /////////////////////////////////////////////////////////

    getArbre()->traduitEnCPP(cout,indentation+1);
    cout << setw(4*(indentation+1)) << "" << "return 0;" << endl;
    cout << setw(4*indentation) << "}" <<endl;
}
///////////////////////////////////////////////////////////
////////////// //////////TANT QUE /////////////////////////
///////////////////////////////////////////////////////////

Noeud* Interpreteur::instTantQue(){
    // <instTantQue> ::= tantque (<expression>)  <seqInst> finTantQue
        testerEtAvancer("tantque");
        testerEtAvancer("(");
        Noeud* condition = expression();
        testerEtAvancer(")");
        Noeud *sequence = seqInst();
        testerEtAvancer("fintantque");
        return new NoeudInstTantQue(condition,sequence);
}


///////////////////////////////////////////////////////////
////////////// //////////SiRiche/////////////////////////
///////////////////////////////////////////////////////////
Noeud* Interpreteur::instSiRiche(){
    vector <Noeud *> v_sequences;
    vector <Noeud *> v_conditions;
    vector <Noeud *> v_sequencesinon;
    //<instSiRiche> ::=si(<expression>) <seqInst> {sinonsi(<expression>) <seqInst> }[sinon <seqInst>]finsi
    testerEtAvancer("si");
    testerEtAvancer("(");
    Noeud* condition = expression();
    if(condition != nullptr){
        v_conditions.push_back(condition);
    }
    testerEtAvancer(")");
    Noeud* sequence = seqInst();
    if(sequence != nullptr){
        v_sequences.push_back(sequence);
    }
    
    while(m_lecteur.getSymbole() == "sinonsi"){
        testerEtAvancer("sinonsi");
        testerEtAvancer("(");
        Noeud* condition1 = expression();
        if(condition1 != nullptr){
            v_conditions.push_back(condition1);
        }
        testerEtAvancer(")");
        Noeud* sequence1 = seqInst();
        if(sequence1 != nullptr){
            v_sequences.push_back(sequence1);
        }  
    }
    if(m_lecteur.getSymbole() == "sinon"){
        testerEtAvancer("sinon");
        testerEtAvancer("(");
        Noeud * sinon = seqInst();
        if(sinon != nullptr){
            v_sequencesinon.push_back(sinon);
        }
        testerEtAvancer(")");
    }


    testerEtAvancer("finsi");
    return new NoeudInstSiRiche(v_conditions,v_sequences,v_sequencesinon);
}


    

///////////////////////////////////////////////////////////
////////////// //////////Repeter/////////////////////////
///////////////////////////////////////////////////////////

Noeud* Interpreteur::instRepeter(){
    //<instRepeter> ::=repeter <seqInst> jusqua( <expression> )
    Noeud * sequence = NULL;
    Noeud *condition = NULL;
    testerEtAvancer("repeter");
    sequence = seqInst();
    testerEtAvancer("jusqua");
    testerEtAvancer("(");
    condition = expression();
    testerEtAvancer(")");
    
    return new NoeudInstRepeter(condition,sequence);
}

///////////////////////////////////////////////////////////
////////////// //////////Pour/////////////////////////
///////////////////////////////////////////////////////////
//<instPour> ::= pour( [ <affectation> ] ; <expression> ;[ <affectation> ]) <seqInst> finpour
 Noeud* Interpreteur::instPour(){
     testerEtAvancer("pour");
     testerEtAvancer("(");
     Noeud* affectationgauche = NULL;
     Noeud* affectationdroite = NULL;
     Noeud* condition = NULL;
     Noeud* instruction = NULL;
     
     if(m_lecteur.getSymbole() == "<VARIABLE>"){ //alors dans le cas de l'affectation     
         affectationgauche = affectation();     
     }
    testerEtAvancer(";");  
    condition = expression();
    testerEtAvancer(";");
    if(m_lecteur.getSymbole() == "<VARIABLE>"){
        affectationdroite = affectation(); 
    }
    testerEtAvancer(")");
    instruction = seqInst();
    testerEtAvancer("finpour");
     return new NoeudInstPour(affectationgauche,condition,affectationdroite,instruction);
 }

     
 
///////////////////////////////////////////////////////////
////////////// //////////Ecrire/////////////////////////
///////////////////////////////////////////////////////////
// <instEcrire>  ::=ecrire( <expression> | <chaine> {, <expression> | <chaine> })
 Noeud* Interpreteur::instEcrire(){
     vector<Noeud*> v_exp;
     testerEtAvancer("ecrire");
     testerEtAvancer("(");
     Noeud* condition = expression();
     v_exp.push_back(condition);
     while(m_lecteur.getSymbole() == ","){
        testerEtAvancer(",");
        Noeud* condition1 = expression();
        v_exp.push_back(condition1);
     }
     testerEtAvancer(")");
     return new NoeudInstEcrire(v_exp);
 }

///////////////////////////////////////////////////////////
////////////// //////////Lire/////////////////////////
///////////////////////////////////////////////////////////
 Noeud *Interpreteur::instLire(){
     //cin bolosse
    vector <Noeud *> v_variables;
    testerEtAvancer("lire");
    testerEtAvancer("(");
    try{
        if(m_lecteur.getSymbole()==""){
            throw string ("Erreur : veuillez mettre une variable dans le lire");
        }
        v_variables.push_back(m_table.chercheAjoute(m_lecteur.getSymbole())); 
        m_lecteur.avancer();
        while(m_lecteur.getSymbole()!=")"){
            //On ajoute la variable lié au symbole où pointe le lecteur
            testerEtAvancer(",");
            v_variables.push_back(m_table.chercheAjoute(m_lecteur.getSymbole())); 
            m_lecteur.avancer();
        } 
    }catch(string const& chaine){
        cerr<<chaine<<endl;
    }
     testerEtAvancer(")");
     return new NoeudInstLire(v_variables);
 }
