#pragma once
#include <qvector.h>
#include <qvector3d.h>

// Формализуем формат трёхмерных файлов .obj
// формат допускает использование полигонов с произвольным числом вершин
// поверхности задаются в виде набора индексов вершин
// индексы начинаются с единицы, и могут быть отрицательными.
// в таком случае отсчёт ведётся с конца

namespace wireframe {
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

    void modelRotate(Model3D &model, QVector3D point, QVector3D angles);
    void modelMove(Model3D &model, QVector3D vector);
    void modelScale(Model3D &model, QVector3D point, QVector3D coeficients);
}
