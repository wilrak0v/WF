#include <stdio.h>
#include <stdlib.h>

// < > [ ] { } + - * ^

unsigned char cels[32768];
int pointer = 0;

// Fonction pour interpréter le bytecode
void interprete(const char* filename)
{
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Erreur d'ouverture de fichier");
		return;
	}

	int* loop_stack = (int*)malloc(32768 * sizeof(int)); // Stack pour suivre les boucles
	int stack_pointer = -1; // Pointeur pour la pile des boucles
	
	long func_stack[100];
	int func_pointer = -1; // Pointeur pour la pile des fonctions
	long lieu;
	
	int ins;
	
	while ((ins = fgetc(file)) != EOF) {
		switch (ins) {
			case 1:		// Print
				putchar(cels[pointer]);
				fflush(stdout); 
				break;

			case 2:		// Incrementer
				cels[pointer]++;
				break;
		
			case 3:		// Début de boucle
				// Si la cellule est zéro, sauter à la fin de la boucle
				if (cels[pointer] == 0) {
					// On doit sauter au bytecode après le ']' correspondant
					int loop_count = 1;
					while (loop_count > 0) {
						ins = fgetc(file);
						if (ins == 3) loop_count++; // Si c'est un '['
						if (ins == 4) loop_count--; // Si c'est un ']'
					}
				} else {
					// Sinon, on empile la position de la boucle
					loop_stack[++stack_pointer] = ftell(file)-1; // Enregistre la position du début de boucle
				}
				break;
							
			case 4:		// Fin de boucle
				// Si la cellule n'est pas zéro, revenir au début de la boucle
				if (cels[pointer] != 0) {
					fseek(file, loop_stack[stack_pointer], SEEK_SET); // Revenir au début de la boucle
				} else {
					stack_pointer--; // Terminer la boucle
				}
				break;
				
			case 5:		// Curseur déplacé vers la gauche
				if (pointer>0) pointer--;
				else pointer = 32768;
				break;
				
			case 6:		// Curseur déplacé vers la droite
				if (pointer<32768) pointer++;
				else pointer = 0;
				break;
		
			case 7:		// Début de fonction
				func_pointer++;
				if (stack_pointer < 100) {
					func_stack[func_pointer] = ftell(file);
					//printf("Sauvegarde de la position à %ld\n", func_stack[func_pointer]);
				} else {
					printf("\nErreur : pile de fonctions pleine !\n");
				}
				while((ins = fgetc(file)) != 8) {
					// Là on attend
				}
				break;

			case 8:		// Fin de fonction
				fseek(file, lieu, SEEK_SET);
				break;
			
			case 9:		// Syscall
				switch (cels[pointer])
				{
					case 1:
						printf("Afficher pixel : X=%d ; Y=%d\n", cels[pointer-1], cels[pointer-2]);
						break;
					case 2:		// Multiplier la cellule précédente par la cellule suivante
						cels[pointer-1] *= cels[pointer-2];
						break;
					case 3:		// Afficher le nombre contenu dans la cellule précédente
						printf("%d", cels[pointer-1]);
						break;
					default:
						break;
					// Rajouter des syscall ici
				}
				break;
	
			case 10:	// Execute la dernière fonction
				if (func_pointer>=0) {
					lieu = ftell(file);
					fseek(file, func_stack[func_pointer], SEEK_SET);
					//printf("Retour à la position %ld\n", func_stack[func_pointer]);
					func_pointer--;
				} else {
					//printf("Erreur : pile de fonctions vide !\n");
				}
				break;
						
			case 11:	// Decrementer
				cels[pointer]--;
				break;
						
			case 12:	// Lire un input
				cels[pointer] = getchar();
				break;
							
			default:
				break;
		}
	}
	free(loop_stack); // Libérer la mémoire de la pile des boucles
	fclose(file);
}

int main(int argc, char* argv[])
{
	if (argc<2) return 1;
	interprete(argv[1]);
	printf("\n");
	return 0;
}
