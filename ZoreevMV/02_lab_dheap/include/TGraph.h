﻿#pragma once

#include <iostream>
#include <stack>
#include <time.h>
#include <random>

#include "TException.h"

struct TEdge
{
    size_t from;   //Исходящая вершина
    size_t to;     //Входящая вершина
    double weight; //Вес ребра

    //Проверяет ребро на инцидентность вершине
    bool incident(size_t vertex);

    TEdge& operator=(const TEdge& temp);

    bool operator<(const TEdge& temp) const;
    bool operator==(const TEdge& temp) const;
    bool operator>(const TEdge& temp) const;
    bool operator<=(const TEdge& temp) const;
    bool operator>=(const TEdge& temp) const;

    //Возвращает вершину смежную переданной, по данному ребру.
    size_t operator[](size_t id) const;

    friend std::ostream& operator<<(std::ostream& out, const TEdge& edge);
    friend std::istream& operator>>(std::istream& in, TEdge& edge);
};


class TGraph
{
private:
    size_t vertices_count; //Количство вершин(нельзя поменять)
    size_t edges_count;    //Количество рёбер
    TEdge* edges;          //Массив рёбер

    

public:
    //Конструктор генерирующий граф
    TGraph(size_t vertices_count_, size_t edges_count_);
    TGraph(size_t vertices_count_, TEdge* edges_, size_t edges_count_);
    TGraph(const TGraph& temp);
    ~TGraph();

    size_t getVerticiesCount() const;
    size_t getEdgesCount() const;

    //Проверка графа на связность, методом случайного обхода
    bool connected() const;

    TGraph& operator=(const TGraph& temp);

    friend std::ostream& operator<<(std::ostream& out, const TGraph& graph);
    friend std::istream& operator>>(std::istream& in, TGraph& graph);

private:
    //Проверка вершины на корректность
    bool isCorrect(const TEdge& edge);

    friend class TKruskalsAlgorithm;
    friend class TDijkstrasAlgorithm;

};