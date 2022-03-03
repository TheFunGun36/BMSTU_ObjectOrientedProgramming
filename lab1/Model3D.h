#pragma once
#include <qvector.h>

// Формализуем формат трёхмерных файлов .obj
// формат допускает использование полигонов с произвольным числом вершин
// поверхности задаются в виде набора индексов вершин
// индексы начинаются с единицы, и могут быть отрицательными.
// в таком случае отсчёт ведётся с конца

struct Vertex3D {
    qreal x;
    qreal y;
    qreal z;
};

struct Surface3Dindex {
    QVector<int> vertexIdx;
};

struct Model3D {
    QVector<Vertex3D> vertex;
    QList<Surface3Dindex> face;
};
