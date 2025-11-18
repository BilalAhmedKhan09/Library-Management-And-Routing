#include<QGraphicsEllipseItem>
#include <QString>
#include <QPainter>

using namespace std;

class node:QGraphicsEllipseItem{
public:
    node(qreal x, qreal y, qreal radius, QGraphicsItem *parent = nullptr)
        : QGraphicsEllipseItem(x, y, 2 * radius, 2 * radius, parent) {
        setBrush(QBrush(Qt::blue)); // sets node colour
        setPen(QPen(Qt::black, 1)); // sets border colour
        // for interactivity (drag and such)
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    }
};

