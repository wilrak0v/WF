#include <stdio.h>
#include <stdlib.h>

// < > [ ] { } + - * ^

// Fonction pour convertir les symboles en nombres et les enregistrer en binaire
void convert_symbols_to_binary(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        printf("Erreur d'ouverture du fichier d'entrée.\n");
        return;
    }

    FILE *output_file = fopen(output_filename, "wb");  // Ouvrir en mode binaire
    if (!output_file) {
        printf("Erreur d'ouverture du fichier de sortie.\n");
        fclose(input_file);
        return;
    }

    
    int c;
    int save = 0;
    char result;
    while ((c = fgetc(input_file)) != EOF) {  // Lire chaque caractère jusqu'à la fin du fichier
		result = 0;
        save = 1;
        switch (c) {
        	case '.':
        		//printf("Print\n");
        		result = 1;
        		break;
        	case '+':
        		//printf("Incrémentation\n");
        		result = 2;
        		break;
        	case '[':
        		//printf("Début de boucle\n");
        		result = 3;
        		break;
        	case ']':
        		//printf("Fin de boucle\n");
        		result = 4;
        		break;
        	case '<':
        		//printf("Curseur déplacé vers la gauche\n");
        		result = 5;
        		break;
        	case '>':
        		//printf("Curseur déplacé vers la droite\n");
        		result = 6;
        		break;
        	case '{':
        		//printf("Début de fonction\n");
        		result = 7;
        		break;
        	case '}':
        		//printf("Fin de fonction\n");
        		result = 8;
        		break;
        	case '@':
        		//printf("Syscall\n");
        		result = 9;
        		break;
        	case '^':
        		//printf("Saute à la dernière fonction\n");
        		result = 10;
        		break;
        	case '-':
        		//printf("Décrémentation\n");
        		result = 11;
        		break;
        	case ',':
        		//printf("Lecture d'un input\n");
        		result = 12;
        		break;
        	default:
        		save = 0;
        		break;
        }
        if (save == 1) { fwrite(&result, sizeof(result), 1, output_file); fflush(output_file); }
    }

    fclose(input_file);
    fclose(output_file);
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    // Convertir un fichier texte contenant des symboles en binaire
    convert_symbols_to_binary(argv[1], argv[2]);
    return 0;
}
