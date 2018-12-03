#include <stdlib.h>
#include <stdio.h>
#define nb_sommet 4

// Un sommet contient uniquement une valeur
typedef struct Sommet {
	int value ;
}Sommet;

// Le graphe est représenté par un tableau de sommet et une matrice d'arretes ou chaque case vaut 1 (si il y'a une arrete) ou 0 sinon
typedef struct Graphe {
	Sommet sommets[nb_sommet];	
	int arretes[nb_sommet][nb_sommet];
}Graphe;

//Pour le tableau résultat, chaque case (indice) represente un sommet, et nous aurons besoin pour chaque sommet de : 
// ind_parcours : L'indice de son parcours 
// ind_pere : L'indice de son pere (dans le tableau des sommets du graphe) 
// articulation : Un booleen qui dit si c'est un point d'articulation ou non 
// low : le plus petit indice de parcours vers lequel ce sommet peut remonter

typedef struct Result {
	int ind_parcours;
	int ind_pere;
	int articulation;
	int low;
}Result;

// Voila le tableau résultat 
Result resultat[nb_sommet];

//Le graphe comme variable globale
Graphe graphe;

//L'indice de parcours comme variable globale 
int cpt=1;

//Retourne le min de deux entiers
int min (int a, int b)
{
	if(a>b) return b;
	return a;
}

//Parcours un sommet et ces fils avec recherche des points d'articulations 
void parcoursSommet (int sommet) 
{
	//Calculer le nombre de déscendants directs dans l'arbre DFS
	int children = 0;
	//Marquer le sommet a visité, et lui affecter son indice de parcours 
	resultat[sommet].ind_parcours = cpt;
	//Initialisation du prefixe
	resultat[sommet].low = cpt;
	cpt++;
	for(int j=0; j<nb_sommet; j++)  
	{
		if (graphe.arretes[sommet][j] == 1) //Parcourir tous les sommets adjacents 
		{
			if(resultat[j].ind_parcours == -1) //Si il y'a un qui est non visité 
			{
				children ++;                 
				resultat[j].ind_pere = sommet; //Modifier le pere
				parcoursSommet(j);     //Parcourir le fils 
				//Verifier si le fils j a une arrete avec un ascendant de sommet
				resultat[sommet].low = min(resultat[sommet].low, resultat[j].low); 
				if(resultat[sommet].ind_pere == -1 && children > 1)
				{   //Si le sommet est la racine et possede plus d'un fils c'est un point d'articulation
					resultat[sommet].articulation = 1;
				}
				if(resultat[sommet].ind_pere != -1 && resultat[j].low >= resultat[sommet].ind_parcours)
				{ //Si le sommet n'est pas la racine, mais un de ces fils n'a pas d'arrete qui remonte 
					resultat[sommet].articulation = 1;
				}				
			}
			else if(j != resultat[sommet].ind_pere)
			{ //Si le noeud adjacent est deja visité, on met a jour low
				resultat[sommet].low = min(resultat[sommet].low, resultat[j].ind_parcours);
			}
		}
	}
}


//Effectue un parcours profondeur du graphe
void parcoursProfondeur()
{
	for (int i=0; i<nb_sommet ; i++)  //Parcourir tous les sommets et si il y'a un non visité, on le visite
	{
		if(resultat[i].ind_parcours == -1)  parcoursSommet(i);		
	}	

}


//Construction aléatoire des graphes, utile pour les tests sur des grands graphes
Graphe construireGraphe()
{
	for(int i=0; i<nb_sommet;i++)
	{
		graphe.sommets[i].value = i;
		resultat[i].ind_parcours = -1;
		resultat[i].articulation = 0;		
		resultat[i].ind_pere = -1;
		resultat[i].low = -1;
	}
 
	for(int i=0; i<nb_sommet ; i++)
	{
		graphe.arretes[i][i] = 0;
		for(int j=i+1; j<nb_sommet; j++)
		{
			int x = (rand()+j)%2;
			graphe.arretes[i][j] = x;
			graphe.arretes[j][i] = x;
		}
	}
}


//Construction manuelle des points d'articulations : utile pour tester le bon fonctionnement de l'algorithme sur des exemples connus
Graphe construireGraphePerso()
{
	graphe.sommets[0].value= 0;
	graphe.sommets[1].value= 1;
	graphe.sommets[2].value= 2;
	graphe.sommets[3].value= 3;

	resultat[0].ind_parcours = -1;
	resultat[0].articulation = 0;
	resultat[0].ind_pere = -1;
	resultat[0].low = -1;
	resultat[1].ind_parcours = -1;
	resultat[1].articulation = 0;
	resultat[1].ind_pere = -1;
	resultat[1].low = -1;
	resultat[2].ind_parcours = -1;
	resultat[2].articulation = 0;
	resultat[2].ind_pere = -1;
	resultat[2].low = -1;
	resultat[3].ind_parcours = -1;
	resultat[3].articulation = 0;
	resultat[3].ind_pere = -1;
	resultat[3].low = -1;
	graphe.arretes[0][0] = 0;
	graphe.arretes[0][1] = 1;
	graphe.arretes[0][2] = 0;
	graphe.arretes[0][3] = 0;
	graphe.arretes[1][0] = 1;
	graphe.arretes[1][1] = 0;
	graphe.arretes[1][2] = 1;
	graphe.arretes[1][3] = 1;
	graphe.arretes[2][0] = 0;
	graphe.arretes[2][1] = 1;
	graphe.arretes[2][2] = 0;
	graphe.arretes[2][3] = 1;
	graphe.arretes[3][0] = 0;
	graphe.arretes[3][1] = 1;
	graphe.arretes[3][2] = 1;
	graphe.arretes[3][3] = 0;
}


// Le main : crée un graphe, puis recherche les points d'articulations et les affiche 
int main()
{
	//construireGraphe();
	construireGraphePerso();
	parcoursProfondeur();
	for(int i=0; i<nb_sommet; i++) 
	{
		if (resultat[i].articulation ==1 ) printf("%d\n",i);
	}
	return 0;
}



