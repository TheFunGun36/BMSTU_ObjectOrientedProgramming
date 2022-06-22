#include "itemrow.h"
#include <qboxlayout.h>

ItemRow::ItemRow(Jora::ObjectId id, const QString& label, QWidget* parent)
    : QWidget(parent)
    , _id(id) {
    QHBoxLayout* layout = new QHBoxLayout(this);
    _label = new QLabel(label, this);
    layout->addWidget(_label);
    setLayout(layout);
}
