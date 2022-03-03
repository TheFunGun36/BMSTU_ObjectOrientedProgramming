#include "Model3D.h"

namespace wireframe {
    QPointF rotate(QPointF point, QPointF center, qreal angle) {
        qreal sint = qSin(angle);
        qreal cost = qCos(angle);

        qreal dx = point.x() - center.x();
        qreal dy = point.y() - center.y();

        point.setX(center.x() + dx * cost + dy * sint);
        point.setY(center.y() - dx * sint + dy * cost);

        return point;
    }

    void modelRotate(Model3D &model, QVector3D point, QVector3D angles) {
        for (Vertex3D &v : model.vertex) {
            QPointF r;

            r = rotate({ v.y, v.z }, { point.y(), point.z() }, angles.x());
            v.y = r.x();
            v.z = r.y();

            r = rotate({ v.x, v.z }, { point.x(), point.z() }, angles.y());
            v.x = r.x();
            v.z = r.y();

            r = rotate({ v.x, v.y }, { point.x(), point.y() }, angles.z());
            v.x = r.x();
            v.y = r.y();
        }
    }

    void modelMove(Model3D &model, QVector3D vector) {
        for (Vertex3D &v : model.vertex) {
            v.x += vector.x();
            v.y += vector.y();
            v.y += vector.z();
        }
    }

    void modelScale(Model3D &model, QVector3D point, QVector3D k) {
        for (Vertex3D &v : model.vertex) {
            v.x = v.x * k.x() + (1 - k.x()) * point.x();
            v.y = v.y * k.y() + (1 - k.y()) * point.y();
            v.z = v.z * k.z() + (1 - k.z()) * point.z();
        }
    }

}
