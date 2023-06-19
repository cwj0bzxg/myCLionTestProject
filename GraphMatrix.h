//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#pragma once
#include "myVector.h"
#include "Graph.h"

template<typename Tv>
struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;
    int dTime, fTime;
    int parent;
    int priority;
    Vertex(Tv const& d = (Tv) 0) :
            data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template<typename Te>
struct Edge {
    Te data;
    int weight;
    EType type;
    Edge(Te const& d, int w) :
            data(d), weight(w), type(UNDETERMINED) {}
};

template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    myVector<Vertex<Tv>> V;
    myVector<myVector<Edge<Te>*>> E;
public:
    GraphMatrix() {
        this->n = this->e = 0;
    }
    ~GraphMatrix() {
        for (int j = 0; j < this->n; ++j) {
            for (int k = 0; k < this->n; ++k) {
                delete E[j][k];
            }
        }
    }
    virtual Tv& vertex(int i) {
        return V[i].data;
    }
    virtual int inDegree(int i) {
        return V[i].inDegree;
    }
    virtual int outDegree(int i) {
        return V[i].outDegree;
    }
    virtual int firstNbr(int i) {
        return nextNbr(i, this->n);
    }
    virtual int nextNbr(int i, int j) {
        while ((-1 < j) && (!exists(i, --j)));
        return j;
    }
    virtual VStatus& status(int i) {
        return V[i].status;
    }
    virtual int& dTime(int i) {
        return V[i].dTime;
    }
    virtual int& fTime(int i) {
        return V[i].fTime;
    }
    virtual int& parent(int i) {
        return V[i].parent;
    }
    virtual int& priority(int i) {
        return V[i].priority;
    }
    virtual int insert(Tv const& vertex) {
        for (int j = 0; j < this->n; ++j) {
            E[j].insert(nullptr);
            ++this->n;
        }
        E.insert(myVector<Edge<Te>*>(this->n, this->n, (Edge<Te>*) nullptr));
        return V.insert(Vertex<Tv>(vertex));
    }
    virtual Tv remove(int i) {
        for (int j = 0; j < this->n; ++j) {
            if (exists(i, j)) {
                delete E[i][j];
                --V[j].inDegree;
            }
        }
        E.remove(i);
        --this->n;
        Tv vBak = vertex(i);
        V.remove(i);
        for (int j = 0; j < this->n; ++j) {
            if (Edge<Te>* e = E[j].remove(i)) {  // e is not nullptr
                delete e;
                --V[j].outDegree;
            }
        }
        return vBak;
    }
    virtual bool exists(int i, int j) {
        return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != nullptr;
    }
    virtual EType& type(int i, int j) {
        return E[i][j]->type;
    }
    virtual Te& edge(int i, int j) {
        return E[i][j]->data;
    }
    virtual int& weight(int i, int j) {
        return E[i][j]->weight;
    }
    virtual void insert(Te const& edge, int w, int i, int j) {
        if (exists(i, j)) {
            return;
        }
        E[i][j] = new Edge<Te>(edge, w);
        ++this->e;
        ++V[i].outDegree;
        ++V[j].inDegree;
    }
};