#ifndef MARKOV_CHAIN_CHAIN_H
#define MARKOV_CHAIN_CHAIN_H

#include "mindless_machine.h"
//TODO обнулить из '.' в '.'
//TODO функция для перевода в вероятности
/**
 * Функция создания нового конечного автомата из файла filename
 * @param filename - имя файла
 * @return указатель на новый граф
 */
graph* create_new_machine(char* filename);

/**
 * Функция создания автомата из сохраненного графа
 * @param filename - имя файла
 * @return указатель на граф
 */
graph* create_new_machine_graph_file(char* filename);

/**
 * Функция генерации предложения
 * @param graph - указатель на граф состояний (автомат)
 * @return - указатель на строку
 */
char* generate(graph* graph);

#endif //MARKOV_CHAIN_CHAIN_H
