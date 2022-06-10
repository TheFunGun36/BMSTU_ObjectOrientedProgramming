#pragma once
#include <qwidget.h>
#include <qlabel.h>
#include "../model/jsceneobject.h"

class ItemRow : public QWidget {
public:
    ItemRow(Jora::ObjectId id, const QString& label, QWidget* parent = nullptr);

    Jora::ObjectId id() const noexcept { return _id; }
    QString label() const noexcept { _label; }
    void setId(Jora::ObjectId id) noexcept { _id = id; }
    void setLabel(QString label) noexcept { _label->setText(label); }

private:
    Jora::ObjectId _id;
    QLabel* _label;
};

