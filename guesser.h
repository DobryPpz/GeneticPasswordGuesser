#ifndef GUESSER_H
#define GUESSER_H

struct specimen{
    char *chromosome;
    int chromosome_length;
};

void print_chromosome(struct specimen *s);
int find_symbol_index_in_gene_set(char symbol);
void mutate(struct specimen *s);
struct specimen *generate_parent(int length);
void destroy_parent(struct specimen *s);
int get_fitness(char *target, struct specimen *s);
void run(char *target);
struct specimen *clone_specimen(struct specimen *s);

#endif