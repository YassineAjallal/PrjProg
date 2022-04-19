
/*-----------------------------------Location----------------------------------- */
int Location()
{
    system("cls");

    int choix ;
    do
    {
        printf("              Location des voitures        \n\n\n");
        printf("     Visualisation contrat.................1\n");
        printf("     Louer Voiture.........................2\n");
        printf("     Retourner voiture.....................3\n");
        printf("     Modifier contrat......................4\n");
        printf("     Supprimer contrat.....................5\n");
        printf("     Retour................................6\n");
        printf("\n\n                Votre choix : ");
        scanf("%d",&choix);
        printf("\n\n");
    }
    while(choix<1 || choix>6);
    printf("      ========================================\n\n");
    if(choix==6){
    	system("cls");
    	main();
	}
	else return choix;

}


/*-------------------------------Gestion Voitures----------------------------------*/

int gestionVoitures()
{
    system("cls");

    int choix;
    do
    {
        printf("                Gestion des voitures        \n\n\n");
        printf("     Liste des voitures....................1\n");
        printf("     Ajouter voiture.......................2\n");
        printf("     Modifier voiture......................3\n");
        printf("     Supprimer voiture.....................4\n");
        printf("     Retour................................5\n");
        printf("\n\n               Votre choix : ");
        scanf("%d",&choix);
        printf("\n\n");
    }
    while(choix<1 || choix>5);
    printf("      ========================================\n\n");
    if(choix==5){
    	system("cls");
    	main();
	}
    else return choix;
}

/*-------------------------------Gestion Client----------------------------------*/
int gestionClients()
{
    system("cls");
    int choix;
    do
    {
        printf("                Gestion des clients        \n\n\n");
        printf("     Liste des clients....................1\n");
        printf("     Ajouter client.......................2\n");
        printf("     Modifier client......................3\n");
        printf("     Supprimer client.....................4\n");
        printf("     Retour...............................5\n");
        printf("\n\n               Votre choix : ");
        scanf("%d",&choix);
        printf("\n\n");
    }
    while(choix<1 || choix>5);
    printf("      ========================================\n\n");
    if(choix==5){
    	system("cls");
    	main();
	}
    else return choix;
}
