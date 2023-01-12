#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <guesser.h>

char gene_set[] = {
    'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H',
    'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P',
    'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X',
    'y', 'Y', 'z', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '?',
    '!', ',', ';', ':', '[', ']', '@', '#', '$', '%', '^', '*', '{', '}', '-', '+'
};

void print_chromosome(struct specimen *s){
    for(int i=0;i<(s->chromosome_length);i++){
        printf("%c",s->chromosome[i]);
    }
    printf("\n");
}
int find_symbol_index_in_gene_set(char symbol){
    for(int i=0;i<80;i++){
        if(gene_set[i]==symbol) return i;
    }
    return -1;
}
void mutate(struct specimen *s){
    int index_to_mutate = random()%(s->chromosome_length);
    s->chromosome[index_to_mutate] = gene_set[random()%80];
}
struct specimen *generate_parent(int length){
    struct specimen *s = (struct specimen*)malloc(sizeof(struct specimen));
    s->chromosome_length = length;
    s->chromosome = (char*)malloc(length*sizeof(char));
    for(int i=0;i<length;i++){
        s->chromosome[i] = gene_set[random()%80];
    }
    return s;
}
void destroy_parent(struct specimen *s){
    free(s->chromosome);
    free(s);
}
int get_fitness(char *target, struct specimen *s){
    int fitness = 0;
    for(int i=0;i<(s->chromosome_length);i++){
        if(target[i]==s->chromosome[i]){
            fitness++;
        }
    }
    return fitness;
}
struct specimen *clone_specimen(struct specimen *s){
    struct specimen *clone = (struct specimen*)malloc(sizeof(struct specimen));
    clone->chromosome_length = s->chromosome_length;
    clone->chromosome = (char*)malloc(s->chromosome_length*sizeof(char));
    memcpy(clone->chromosome,s->chromosome,s->chromosome_length);
    return clone;
}
void run(char *target){
    srandom(997);
    struct specimen *s = NULL;
    struct specimen *best_parent = generate_parent(strlen(target));
    int highest_possible_fitness = strlen(target);
    int best_fitness = get_fitness(target,best_parent);
    int current_fitness;
    while(best_fitness<highest_possible_fitness){
        s = clone_specimen(best_parent);
        mutate(s);
        current_fitness = get_fitness(target,s);
        if(current_fitness>best_fitness){
            destroy_parent(best_parent);
            best_parent = clone_specimen(s);
            best_fitness = current_fitness;
            print_chromosome(best_parent);
        }
        destroy_parent(s);
    }
    printf("i guessed:\n");
    print_chromosome(best_parent);
    destroy_parent(best_parent);
}