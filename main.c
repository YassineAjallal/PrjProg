#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"
#include "menu.h"
#include "Voitures.h"
#include "Location.h"
#include "Clients.h"

int (*listeFonctions[3])() = {Location,gestionVoitures,gestionClients};


int main()
{
    FILE *contracts , *vtr , *clt,*cont, *tempV, *tempC, *tempCT,*tempR, *tempL;
    vtr = fopen("Voiture.txt", "rb+");
    clt = fopen("Client.txt","rb+");
    cont = fopen("Contrat.txt","rb+");

    int choix,(*functionAdress)() , choice;
    do
    {
        printf("                  Menu Principal        \n\n\n");
        printf("     Location..............................1\n");
        printf("     Gestion voitures......................2\n");
        printf("     Gestion clients.......................3\n");
        printf("     Quitter...............................4\n");
        printf("\n\n                Votre choix : ");
        scanf("%d",&choix);
        printf("\n\n");
    }
    while(choix<1 || choix>4);
    printf("      ========================================\n");
    if(choix==4)
    {
        printf("      Merci d'avoir utiliser notre service :)\n");
        printf("      ========================================\n\n");
        exit(1);
    }
    else functionAdress=listeFonctions[choix-1];
    choice = functionAdress();
    switch(choix){
        case 1 : switch (choice){

              case 1 : visualiserContrat(cont);
                      break ;
              case 2 : 
              		   tempL = fopen("renommerL.txt","wb+");
			  		   louerVoiture(vtr,clt,cont,tempL) ;
                       break ;
              case 3 : 
		 		       tempR = fopen("renommerR.txt","wb+");
					  retournerV(cont,vtr ,tempR);
                       break ;
              case 4 : modifierContrat(cont);
                       break ;
              case 5 : 
              		   tempCT = fopen("renommerCT.txt","wb+");
			  		   supprimerContrat(vtr , cont , tempCT);
                       break ;
		   		}
		   		break;
			
        case 2 :
              switch(choice){

               case 1 :
                        ListeVoitures(vtr);
                        break ;
               case 2 :
                        Ajouter(vtr);
                        break ;
               case 3 :
                        Modifier(vtr);
                        break ;
               case 4 : 
               			tempV = fopen("renommerV.txt","wb+");
			   			Supprimer(vtr,tempV);
                        break ;



          }
          break ;
          case 3 : switch(choice){
               case 1 : listerClient(clt);
                        break ;
               case 2 : ajouterClient(clt);
                        break ;
               case 3 : modifierClient(clt);
                        break ;
               case 4 : 
               			tempC = fopen("renommerC.txt","wb+");
			   			supprimerClient(clt,tempC);
                        break ;

          }
    }



    return 0;
}
