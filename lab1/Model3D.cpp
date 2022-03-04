#include "Model3D.h"

namespace wireframe {
    struct AngleInfo {
        qreal sint;
        qreal cost;
    };

    QPointF rotate(QPointF point, QPointF center, const AngleInfo &a) {
        qreal dx = point.x() - center.x();
        qreal dy = point.y() - center.y();

        point.setX(center.x() + dx * a.cost + dy * a.sint);
        point.setY(center.y() - dx * a.sint + dy * a.cost);

        return point;
    }

    void modelRotate(Model3D &model, QVector3D point, QVector3D angles) {
        if (!qFuzzyIsNull(angles.x())) {
            AngleInfo ax;
            ax.sint = qSin(angles.x());
            ax.cost = qCos(angles.x());

            for (Vertex3D &v : model.vertex) {
                QPointF r = rotate({ v.y, v.z }, { point.y(), point.z() }, ax);
                v.y = r.x();
                v.z = r.y();
            }
        }

        if (!qFuzzyIsNull(angles.y())) {
            AngleInfo ay;
            ay.sint = qSin(angles.y());
            ay.cost = qCos(angles.y());

            for (Vertex3D &v : model.vertex) {
                QPointF r = rotate({ v.x, v.z }, { point.x(), point.z() }, ay);
                v.x = r.x();
                v.z = r.y();
            }
        }

        for (Vertex3D &v : model.vertex) {
            AngleInfo az;
            az.sint = qSin(angles.z());
            az.cost = qCos(angles.z());

            QPointF r = rotate({ v.x, v.y }, { point.x(), point.y() }, az);
            v.x = r.x();
            v.y = r.y();
        }
    }

    void modelMove(Model3D &model, QVector3D vector) {
        for (Vertex3D &v : model.vertex) {
            v.x += vector.x();
            v.y += vector.y();
            v.z += vector.z();
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
