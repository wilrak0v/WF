#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpretor.h"

void inter(char* code, unsigned char cels[32768], int* pointer, int* endroit)
{
	int* loop_stack = (int*)malloc(32768 * sizeof(int)); // Stack pour suivre les boucles
	int stack_pointer = -1; // Pointeur pour la pile des boucles
			
	long func_stack[100];
	int func_pointer = -1; // Pointeur pour la pile des fonctions
	long lieu;
		
	char ins;
		
	for(size_t i=0; i<strlen(code); i++) {
		ins = code[i];
		switch (ins) {
			case '.':		// Print
				putchar(cels[*pointer]);
				fflush(stdout); 
				break;
			case '+':		// Incrementer
				cels[*pointer]++;
				break;
				
			case '[':		// Début de boucle
				// Si la cellule est zéro, sauter à la fin de la boucle
				if (cels[*pointer] == 0) {
					// On doit sauter au bytecode après le ']' correspondant
					int loop_count = 1;
					while (loop_count > 0) {
						ins = code[loop_count];
						if (ins == 3) loop_count++; // Si c'est un '['
						if (ins == 4) loop_count--; // Si c'est un ']'
					}
				} else {
					// Sinon, on empile la position de la boucle
					loop_stack[++stack_pointer] = i-1;
				}
				break;
									
			case ']':		// Fin de boucle
				// Si la cellule n'est pas zéro, revenir au début de la boucle
				if (cels[*pointer] != 0) {
					i = loop_stack[stack_pointer]; // Revenir au début de la boucle
				} else {
					stack_pointer--; // Terminer la boucle
				}
				break;
					
			case '<':		// Curseur déplacé vers la gauche
				if (*pointer>0)*pointer = *pointer-1;
				else *pointer = 32768;
				if (*pointer%4==0) *endroit-=5;
				break;
					
			case '>':		// Curseur déplacé vers la droite
				if (*pointer<32768) *pointer=*pointer+1;
				else *pointer = 0;
				if (*pointer%5==0) *endroit+=5;
				break;
			
			case '{':		// Début de fonction
				func_pointer++;
				if (stack_pointer < 100) {
					func_stack[func_pointer] = i;
					//printf("Sauvegarde de la position à %ld\n", func_stack[func_pointer]);
				} else {
					printf("\nErreur : pile de fonctions pleine !\n");
				}
				while((ins = code[i]) != 8) {
					// Là on attend
				}
				break;
	
			case '}':		// Fin de fonction
				i = lieu;
				break;
					
			case '@':		// Syscall
				switch (cels[*pointer])
				{
					case 1:
						break;
					case 2:		// Multiplier la cellule précédente par la cellule suivante
						cels[*pointer-1] *= cels[*pointer-2];
						break;
					case 3:		// Afficher le nombre contenu dans la cellule précédente
						printf("%d", cels[*pointer-1]);
						break;
					default:
						break;
					// Rajouter des syscall ici
				}
				break;
		
			case '^':	// Execute la dernière fonction
				if (func_pointer>=0) {
					lieu = i;
					i = func_stack[func_pointer];
					//printf("Retour à la position %ld\n", func_stack[func_pointer]);
					func_pointer--;
				} else {
					//printf("Erreur : pile de fonctions vide !\n");
				}
				break;
								
			case '-':	// Decrementer
				cels[*pointer]--;
				break;
								
			case ',':	// Lire un input
				cels[*pointer] = getchar();
				break;
									
			default:
				break;
		}
	}
	free(loop_stack); // Libérer la mémoire de la pile des boucles

}
