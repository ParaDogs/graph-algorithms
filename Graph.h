#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <iostream>
#include "QList.h"

class Graph
{
private:
    struct Node
    {
        int key;
        Node* down;
        Node* right;

        explicit Node(int key = INT32_MIN)
        {
            this->key = key;
            this->down = nullptr;
            this->right = nullptr;
        }
    };

    Node* root = nullptr;
    std::string arrow = "-->";
    std::string arrowDown = "|";

    Node* getVertex(int key)
    {
        Node* temp = root;
        while (temp != nullptr && temp->key != key)
            temp = temp->down;
        return temp; // null - нет искомой вершины, иначе указатель на вершину
    }

    bool isEmpty()
    {
        return root->down == nullptr && root->right == nullptr && root->key == INT32_MIN;
    }

    bool addVertexToRigth(Node* from, Node* to)
    {
        Node* temp = from;
        Node* endRight;
        while (temp != nullptr)
        {
            if (temp->key == to->key)
            {
                std::cout << "Связь " << from->key << arrow << to->key << " уже есть" << std::endl;
                return false;
            }
            if (temp->right == nullptr)
                endRight = temp;
            temp = temp->right;
        }
        Node* newToVertex = new Node(to->key);
        newToVertex->down = to->down;
        endRight->right = newToVertex;
        return true;
    }

    bool removeVertexFromRight(Node* from, int toKey)
    {
        Node* tempRight;
        Node* remVertex;
        tempRight = from;
        while (tempRight->right != nullptr && tempRight->right->key != toKey)
            tempRight = tempRight->right;
        if (tempRight->right != nullptr)
        {
            remVertex = tempRight->right;
            tempRight->right = remVertex->right;
            delete remVertex;
        }
        else return false;
        return true;
    }

    int vertexN()
    {
        int n = 0;
        Node* temp = root;
        while (temp != nullptr)
        {
            n++;
            temp = temp->down;
        }
        return n;
    }

    int vertexNum(int key)
    {
        int num = 0;
        Node* temp = root;
        while (temp != nullptr && temp->key != key)
        {
            num++;
            temp = temp->down;
        }
        if (temp == nullptr) return -1;
        return num;
    }

    int minColor(Node* p, int colors[])
    {
        minColor(p, colors, 1);
    }

    int minColor(Node* p, int colors[], int startColor)
    {
        if (p->right == nullptr) return 1; // Изолированная вершина

        int minColor = startColor;
        Node* temp = p->right;
        while (temp != nullptr)
        {
            if (colors[vertexNum(temp->key)] == minColor)
            {
                minColor++;
                temp = p->right;
            }
            else temp = temp->right;
        }
        return minColor;
    }

    // Последняя вершина, смежная в x_star в {x_1, ..., x_(i_star - 1)} (упорядочено, согласно главному списку)
    Node* getLastVertex(Node* x_star, int i_star)
    {
        if (i_star == 1) return root;
        Node* x_k = getVertex(x_star->key)->right;
        Node* prev = x_k;
        while (x_k != nullptr)
        {
            if (vertexNum(x_k->key) < i_star && vertexNum(x_k->key) > vertexNum(prev->key)) prev = x_k;
            x_k = x_k->right;
        }
        if (prev == getVertex(x_star->key)->right) return getLastVertex(x_star, i_star-1);
        x_k = getVertex(prev->key);
        return x_k;
    }

    void comeback(Node* x_star, int colors[], int chromaticNumber)
    {
        if (x_star == root) return;

        /*Node* x_k = x_star->right;
        int i_star = vertexNum(x_star->key);
        Node* prev = x_k;
        while (x_k != nullptr && vertexNum(x_k->key) < i_star)
        {
            prev = x_k;
            x_k = x_k->right;
        }
        x_k = getVertex(prev->key); // Последняя вершина, смежная в x_star в {x_1, ..., x_(i_star - 1)}*/
        Node* x_k = getLastVertex(x_star, vertexNum(x_star->key)); //

        int i_k = vertexNum(x_k->key);

        int j_k = colors[i_k]; // x_k окрашена в цвет j_k

        int j_k_new = minColor(x_k, colors, j_k + 1); // x_k перекрашивается в другой допестимый цвет с наименьшим возможным номером больше прежнего

        if (j_k_new >= chromaticNumber)
            comeback(x_k, colors, chromaticNumber);
        else
        {
            colors[i_k] = j_k_new;
            Node* p = x_k->down;
            int num;
            int newMinColor;
            for(int i = 0; i < 2; ++i)
            {
                while (p != nullptr)
                {
                    num = vertexNum(p->key);
                    newMinColor = minColor(p, colors, colors[num] == chromaticNumber ? 1 : colors[num] + 1); //newMinColor = minColor(p, colors);
                    if (newMinColor < chromaticNumber) colors[num] = newMinColor;
                    else comeback(p,colors,chromaticNumber);
                    p = p->down;
                }
                p = x_k->down;
            }
        }
    }


public:
    Graph()
    {
        root = new Node();
    }

    ~Graph() = default;

    Node* addVertex(int key)
    {
        if (getVertex(key) == nullptr)
        {
            Node* newVertex = new Node(key);
            if (isEmpty())
            {
                delete root;
                root = newVertex;
            }
            else
            {
                Node* temp = root;
                while (temp->down != nullptr)
                    temp = temp->down;
                temp->down = newVertex;
            }
            return newVertex; // Добавлена новая вершина
        }
        std::cout << "Вершина " << key << " уже есть" << std::endl;
        return nullptr;
    }

    bool removeVertex(int key)
    {
        Node* vertex = getVertex(key);
        if (vertex != nullptr)
        {
            // Удаление из главного списка
            if (vertex == root)
            {
                //Если это единственная вершина то очищаем корень, иначе меняем корень на следующий в главном списке
                if (root->down == nullptr)
                {
                    root->right = nullptr;
                    root->key = INT32_MIN;
                    return true;
                }
                else
                {
                    root = root->down;
                    delete vertex;
                }
            }
            else
            {
                Node* vertexPrev = root;
                while (vertexPrev->down != vertex)
                    vertexPrev = vertexPrev->down;
                vertexPrev->down = vertex->down;
                delete vertex;
            }

            // Удаление из правых списков
            Node* tempMain = root;
            while (tempMain != nullptr)
            {
                removeVertexFromRight(tempMain, key);
                tempMain = tempMain->down;
            }
            return true;
        }
        std::cout << "Вершины " << key << " нет" << std::endl;
        return false;
    }

    bool addEdge(int from, int to)
    {
        Node* fromVertex = getVertex(from);
        if (fromVertex == nullptr)
            fromVertex = addVertex(from);

        Node* toVertex = getVertex(to);
        if (toVertex == nullptr)
            toVertex = addVertex(to);

        return addVertexToRigth(fromVertex, toVertex) && addVertexToRigth(toVertex, fromVertex);
    }

    bool removeEdge(int from, int to)
    {
        Node* fromVertex = getVertex(from);
        Node* toVertex = getVertex(to);

        if (fromVertex == nullptr || toVertex == nullptr)
        {
            std::cout << "Связи " << from << arrow << to << " нет" << std::endl;
            return false;
        }

        return removeVertexFromRight(fromVertex, toVertex->key) && removeVertexFromRight(toVertex, fromVertex->key);
    }

    void print()
    {
        if (isEmpty())
            std::cout << "Граф пуст" << std::endl;
        else
        {
            Node* temp = root;
            while (temp != nullptr)
            {
                std::cout << temp->key;
                if (temp->right != nullptr)
                {
                    Node* tempRight = temp->right;
                    while (tempRight != nullptr)
                    {
                        std::cout << arrow;
                        std::cout << tempRight->key;
                        tempRight = tempRight->right;
                    }
                }
                std::cout << std::endl;
                std::cout << ((temp->down != nullptr) ? arrowDown : "") << std::endl;
                temp = temp->down;
            }
        }
    }

    bool visit(int p)
    {
        if (isEmpty() || getVertex(p) == nullptr)
        {
            std::cout << "Невозможно начать обход с вершины " << p << std::endl;
            return false;
        }

        struct Edge
        {
            int from;
            int to;

            Edge(int from, int to)
            {
                this->from = from;
                this->to = to;
            }

            Edge()
            {
                this->from = INT32_MIN;
                this->to = INT32_MIN;
            }
        };

        bool mark[vertexN()];
        QList<Edge> S;
        int q = p;
        Node* temp;

        L:
        while (!mark[vertexNum(q)])
        {
            mark[vertexNum(q)] = true;
            temp = getVertex(q)->right;
            while (temp != nullptr)
            {
                S.push_back(Edge(q, temp->key));
                temp = temp->right;
            }
            while (S.size() != 0)
            {
                Edge edge = S.front();
                S.pop_front();
                std::cout << "(" << edge.from << "," << edge.to << ") ";
                q = edge.to;
                if (!mark[vertexNum(q)]) goto L;
            }
        }
        return true;
    }

    int paint()
    {
        paint(root->key);
    }

    int paint(int key)
    {
        if (isEmpty()) return 0;
        Node* p = getVertex(key);

        if (p == nullptr)
        {
            std::cout << "Нет стартовой вершины для окраски" << std::endl;
            return -1;
        }

        int chromaticNumber = 0;
        int n = vertexN();
        int colors[n];
        for (int i = 0; i < n; ++i) colors[i] = 0;

        int vertexPassed = 0;
        int num;
        while (p != nullptr && vertexPassed < n)
        {
            num = vertexNum(p->key);
            colors[num] = minColor(p, colors);
            if (colors[num] > chromaticNumber) chromaticNumber = colors[num];
            std::cout << p->key << "~>" << colors[num] << std::endl;
            vertexPassed++;
            if (p->down == nullptr && vertexPassed < n) p = root;
            else p = p->down;
        }
        std::cout << std::endl;
        // Неявная схема закончилась
        if (chromaticNumber < 3) return chromaticNumber; // Случай несвязного графа и графа, у которого нельзя уменьшить хроматическое число

        // Перекраска
        int oldCromaticNumber = 0;
        while (oldCromaticNumber != chromaticNumber)
        {
            oldCromaticNumber = chromaticNumber; // = q

            Node* x_star = root; // Первая вершина при заданном упорядочивании, которая была окрашена в цвет q
            int i_star = vertexNum(x_star->key);
            while (colors[i_star] != chromaticNumber)
            {
                x_star = x_star->down;
                i_star = vertexNum(x_star->key);
            }
            comeback(x_star, colors, chromaticNumber);

            chromaticNumber = -1;
            for (int i = 0; i < n; ++i)
                if (colors[i] > chromaticNumber) chromaticNumber = colors[i];
        }

        Node* temp = root;
        for (int i = 0; i < n; ++i)
        {
            std::cout << temp->key << "~>" << colors[i] << std::endl;
            temp = temp->down;
        }
        return chromaticNumber;
    }
};
#endif
