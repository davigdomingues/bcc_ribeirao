#include <stdio.h>

void elementos(int *vetor, int *vetorA, int *vetorB){
    for (int j = 0; j < 30; j++){
        if (vetor[j] % 2 == 0){
            printf("%d ", *(vetor + j));
            vetorA++;
        }
    }
    
    printf("\n");

    for (int j = 0; j < 30; j++){
        if (vetor[j] % 2 == 1){
            printf("%d ", *(vetor + j));
            vetorB++;
        }
    }

}

int main(){
    int vetor[30], vetorA[30], vetorB[30];
    
    for (int i = 0; i < 30; i++){
        printf("Valor %d: ", i + 1);
        scanf("%d", vetor + i);
    }

    elementos(vetor, vetorA, vetorB);
}

/*Solução do Chrstyan:

void elementos(int *vetor, int *vetorA, int *vetorB){
	int *x = vetor, *y = vetorA, *z = vetorB;

    for (int j = 0; j < 30; j++){
        if ((*x) % 2){
            *z = *x;
            z++;
        } else {
			*y = *x;
			y++;
    }
    x++;
}

int main(){
    int vetor[30], vetorA[30], vetorB[30];

    elementos(vetor, vetorA, vetorB);
	
	printf("Numeros pares:\n");
	
	for (int i = 0; i < 30; i++){
		printf("%p", vetorA[i]);
	}
	
	return 0;
}

//Forma completa definitiva:

#include <stdio.h>

void elementos(int *vetor, int *vetorA, int *vetorB){
	int *x = vetor, *y = vetorA, *z = vetorB;

    for (int j = 0; j < 30; j++){
        if ((*x) % 2){
            *z = *x;
            z++;
        } else {
	   *y = *x;
	   y++;
        }
    	x++;
    }
}

int main(){
    int vetor[30], vetorA[30], vetorB[30];
    
    for (int i = 0; i < 3; i++){
        printf("Valor %d: ", i + 1);
        scanf("%d", vetor + i);
    }

    elementos(vetor, vetorA, vetorB);
    
    printf("Numeros pares:\n");
	
	for (int i = 0; i < 30; i++){
		printf("%d ", vetorA[i]);
	}
	
	printf("\nNumeros impares:\n");
	
	for (int i = 0; i < 30; i++){
		printf("%d ", vetorB[i]);
	}
}
