/*
 * Le CrocoMeca est grincheux, il a mal dormi. Il est bien décidé à croquer tous ceux qui passeront à sa portée. Mieux vaut ne pas trop s'approcher...
 * 
 * Créé par Tatiana Grange, pour zBis, sous licence CC-BY-SA 4.0
 */

// Ces lignes servent à ajouter les bibliothèques (libraries) dont nous avons besoin
#include <Ultrasonic.h>
#include <Servo.h>



/********** Constantes **********/
// Les constantes sont comme des bouts de papier sur lesquels on écrit un mot ou un chiffre au feutre pour le retenir
// Le feutre ne peut-être effacé, la constante ne peut être modifiée.

const int distance = 30;        // La constante "distance" sera utilisée dans le code pour définir quand le crocodile doit mordre
const int boucheFermee = 140;   // La constante "boucheFermée" sera utilisée dans le code pour dire au moteur comment se positionner pour fermer la bouche
const int boucheOuverte = 100;  // La constante "boucheOuverte" sera utilisée dans le code pour dire au moteur comment se positionner pour ouvrir la bouche



/********** Variables **********/
// Les variables sont comme des bouts de papier sur lesquels on écrit au crayon à papier. 
// On peut remplacer le contenu de la variable en gommant et en écrivant la nouvelle valeur au crayon à papier
int attaquer = 0;                // La variable "attaquer" sera utilisée dans le code pour définir si le crocodile a bien vu quelque chose dans son champ de vision



/********** Capteurs et actionneurs **********/
Servo moteur;                 // La variable "moteur" permettra de désigner le petit servomoteur qui permet de faire bouger la bouche du crocodile
Ultrasonic yeux(9,8);         // Les yeux du crocodile sont branchés sur la carte Arduino. La branche Trig est sur l'entrée 9 et la branche Echo est sur l'entrée 8



/********** Fonctions **********/

// La fonction setup est la toute première exécutée par la carte Arduino.
void setup() {
  moteur.attach(2);                 // Le moteur est branché sur l'entrée 2
  moteur.write(boucheFermee);       // Par défaut, on ferme la bouche du crocodile

  Serial.begin(9600);               // Utile pour trouver les bugs, Serial permet d'écrire dans le moniteur Série. 
                                    // Ici, on écrira sur le canal 9600.
}

// La fonction loop est appelée en boucle par la carte Arduino
void loop()
{
  // "cm" est une variable qui représente la distance (en centimètres) entre le crocodile et ce qui lui passe sous les yeux
  int cm = yeux.Ranging(CM);

  //Début du retour sur le moniteur série
  Serial.print("--> ");
  Serial.println(cm);
  //Fin du retour sur le moniteur série

  // Le crocodile est vigilant, il vérifie toujours deux fois avant de mordre.
  // Cette partie du code permet de définir si le crocodile peut se reposer, doit se préparer à attaque ou doit attaquer.
  
  if(cm <= distance){                 // Est-ce qu'il y a quelque chose dans le champ de vision du crocodile
    // OUI il y a quelque chose dans son champ de vision !
    
    attaquer = attaquer+1;            // On augmente de 1 l'attaque du crocodile. 
                                      // Si elle était à 0, l'attaque passe à 1 et le crocodile prépare à attaquer
                                      // Si elle était à 1, l'attaque passe à 2 et le crocodile est prêt à attaquer

    if(attaquer >= 2){                // Est-ce que le crocodile est prêt à attaquer ?
      // OUI il est prêt à attaquer
      Serial.println("Le crocodile attaque !");
      attaquer = 2;
      
      // Ces quatre lignes permettent de mordre.
      moteur.write(boucheOuverte);    
      delay(200);                     // 200 est le nombre de milisecondes où la bouche reste ouverte. Cela signifie que la bouche reste ouverte 0,2 seconde !
      moteur.write(boucheFermee);
      delay(1000);                    // 1000 est le nombre de milisecondes où la bouche reste fermée. Cela signifie que la bouche reste fermée 1 seconde !
      
    }else{
      // NON il se prépare à attaquer.
      Serial.println("Le crocodile a cru voir quelque chose");
    }
  }
  else{
    // NON il n'y a rien dans son champ de vision !
    attaquer = 0;

    Serial.println("Le crocodile se repose");
  }
    
  delay(100);
}
