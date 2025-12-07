#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QMap>
#include <QQueue>
#include <QDebug>
#include <QMessageBox>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include <functional>

// ===================== AVL TREE =========================

using namespace std;

struct Record {
    string name;
    int ID;
    int height;
    Record *left;
    Record *right;
};

int getheight(Record *n){
    return n ? n->height : 0;
}

Record *newnode(int id, string name){
    Record *n = new Record;
    n->height = 1;
    n->ID = id;
    n->name = name;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

int getbalancefactor(Record *n){
    return n ? getheight(n->left) - getheight(n->right) : 0;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

Record *minimum(Record *n){
    return (n && n->left) ? minimum(n->left) : n;
}

Record *leftrotate(Record *b){
    Record *d = b->right;
    Record *c = d->left;
    d->left = b;
    b->right = c;
    b->height = 1 + max(getheight(b->left), getheight(b->right));
    d->height = 1 + max(getheight(d->left), getheight(d->right));
    return d;
}

Record *rightrotate(Record *d){
    Record *b = d->left;
    Record *c = b->right;
    b->right = d;
    d->left = c;
    b->height = 1 + max(getheight(b->left), getheight(b->right));
    d->height = 1 + max(getheight(d->left), getheight(d->right));
    return b;
}

Record *Insert(Record *n, int ID, string name){
    if (!n) return newnode(ID, name);

    if (ID < n->ID)
        n->left = Insert(n->left, ID, name);
    else if (ID > n->ID)
        n->right = Insert(n->right, ID, name);

    n->height = 1 + max(getheight(n->left), getheight(n->right));
    int bf = getbalancefactor(n);

    if (bf > 1 && ID < n->left->ID) return rightrotate(n);
    if (bf > 1 && ID > n->left->ID) {
        n->left = leftrotate(n->left);
        return rightrotate(n);
    }
    if (bf < -1 && ID > n->right->ID) return leftrotate(n);
    if (bf < -1 && ID < n->right->ID) {
        n->right = rightrotate(n->right);
        return leftrotate(n);
    }

    return n;
}

Record* searchRecord(Record *root, int val){
    if (!root) return nullptr;
    if (val < root->ID) return searchRecord(root->left, val);
    if (val > root->ID) return searchRecord(root->right, val);
    return root;
}


// ========================= GRAPH CLASSES =============================

class Node;
class Edge;

// Global adjacency list
QMap<QString, QList<QPair<QString, int>>> graphAdjacency;

// FIX: global node map
QMap<QString, Node*> nodeMap;

class Edge : public QGraphicsLineItem {
public:
    Node *n1;
    Node *n2;
    int weight;
    QGraphicsTextItem* weightLabel;

    Edge(Node *a, Node *b, int w);
    void updatePosition();
    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) override;
};

class Node : public QGraphicsEllipseItem {
public:
    QGraphicsTextItem *label;
    QList<Edge*> edges;

    Node(qreal x, qreal y, qreal radius, QString name, QGraphicsItem *parent = nullptr);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    QString getName() const;
};

Node::Node(qreal x, qreal y, qreal radius, QString name, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, 2*radius, 2*radius, parent)
{
    setBrush(QBrush(QColor(50, 150, 250)));
    setPen(QPen(Qt::black, 1));

    label = new QGraphicsTextItem(name, this);
    label->setDefaultTextColor(Qt::black);

    // position label under the node circle (centered roughly)
    QRectF lb = label->boundingRect();
    qreal labelX = x + radius - lb.width()/2;
    qreal labelY = y + 2*radius + 5; // a bit below the circle
    label->setPos(labelX, labelY);

    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        // avoid Qt container-detach warning by indexing instead of range-for
        for (int i = 0; i < edges.size(); ++i) {
            Edge* e = edges.at(i);
            if (e) e->updatePosition();
        }
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

QString Node::getName() const {
    return label->toPlainText();
}

Edge::Edge(Node *a, Node *b, int w)
    : n1(a), n2(b), weight(w)
{
    // assume callers have validated a and b non-null
    setPen(QPen(Qt::black, 2));
    updatePosition();

    weightLabel = new QGraphicsTextItem(QString::number(w));
    weightLabel->setDefaultTextColor(Qt::red);

    // Install event filters so when nodes move, edge can update
    a->installSceneEventFilter(this);
    b->installSceneEventFilter(this);

    // Add to nodes
    a->edges.append(this);
    b->edges.append(this);

    // Update adjacency for Dijkstra
    graphAdjacency[a->getName()].append(qMakePair(b->getName(), w));
    graphAdjacency[b->getName()].append(qMakePair(a->getName(), w));
}

void Edge::updatePosition()
{
    if (!n1 || !n2) return;

    QPointF p1 = n1->sceneBoundingRect().center();
    QPointF p2 = n2->sceneBoundingRect().center();

    setLine(QLineF(p1, p2));
    QPointF mid = (p1 + p2) / 2;
    if (weightLabel) weightLabel->setPos(mid);
}

bool Edge::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    Q_UNUSED(watched);
    if (event->type() == QEvent::GraphicsSceneMove) {
        updatePosition();
    }
    return false;
}


// ========================= MAINWINDOW ===============================

Record *root = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    // create and add view to Graphwidget layout
    view = new QGraphicsView(scene, this);
    QVBoxLayout *layout = new QVBoxLayout(ui->Graphwidget);
    layout->addWidget(view);
    ui->Graphwidget->setLayout(layout);

    scene->setSceneRect(0,0,800,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ========================= AVL UI ==============================

void MainWindow::on_Search_clicked()
{
    if (ui->searchID->text().isEmpty()) {
        ui->searchout->setText("Invalid input");
        return;
    }

    int ID = ui->searchID->text().toInt();
    Record *n = searchRecord(root, ID);
    if (!n) ui->searchout->setText("Record Not Found");
    else ui->searchout->setText(QString::fromStdString(n->name));
}

void MainWindow::on_AddRecord_clicked()
{
    if (ui->ID->text().isEmpty() || ui->Name->text().isEmpty()) {
        ui->Name->setText("Wrong input");
        ui->ID->setText("Wrong input");
        return;
    }

    int ID = ui->ID->text().toInt();
    string name = ui->Name->text().toStdString();
    root = Insert(root, ID, name);
}


// ========================= GRAPH UI ==============================

void MainWindow::on_AddNode_clicked()
{
    QString name = ui->Nname->text();
    if (name.isEmpty()) {
        QMessageBox::information(this, "Info", "Enter node name");
        return;
    }

    // create node at default position - you can modify to place where you want
    qreal x = 100;
    qreal y = 100;
    qreal radius = 15;

    // if node with same name exists, warn and return
    if (nodeMap.contains(name)) {
        QMessageBox::warning(this, "Warning", "Node with this name already exists");
        return;
    }

    Node *n = new Node(x, y, radius, name);
    scene->addItem(n);
    scene->addItem(n->label); // ensure label is part of scene
    nodeMap[name] = n;
}

void MainWindow::on_AddEdge_clicked()
{
    QString name1 = ui->N1->text().trimmed();
    QString name2 = ui->N2->text().trimmed();
    int weight = ui->weight->text().toInt();

    if (name1.isEmpty() || name2.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter both node names");
        return;
    }
    if (weight <= 0) {
        QMessageBox::warning(this, "Error", "Enter a valid positive weight");
        return;
    }

    // check existence
    if (!nodeMap.contains(name1)) {
        QMessageBox::warning(this, "Error", QString("Start node '%1' does not exist").arg(name1));
        return;
    }
    if (!nodeMap.contains(name2)) {
        QMessageBox::warning(this, "Error", QString("End node '%1' does not exist").arg(name2));
        return;
    }

    Node *node1 = nodeMap.value(name1);
    Node *node2 = nodeMap.value(name2);

    // extra null-checks (defensive)
    if (!node1 || !node2) {
        QMessageBox::warning(this, "Error", "Node pointer invalid");
        return;
    }

    Edge *edge = new Edge(node1, node2, weight);
    scene->addItem(edge);
    if (edge->weightLabel) scene->addItem(edge->weightLabel);
}


// ========================= DIJKSTRA ==============================

void MainWindow::on_runDijkstraButton_clicked()
{
    QString source = ui->Source->text().trimmed();
    QString dest = ui->Dest->text().trimmed();

    if (source.isEmpty() || dest.isEmpty()) {
        ui->PathOut->setText("Enter source and destination");
        return;
    }

    if (!graphAdjacency.contains(source) || !graphAdjacency.contains(dest)) {
        ui->PathOut->setText("Invalid source/destination!");
        return;
    }

    QMap<QString,int> dist;
    QMap<QString,QString> parent;

    // initialize
    const QList<QString> keys = graphAdjacency.keys();
    for (const QString &node : keys) {
        dist[node] = INT_MAX;
        parent[node] = "";
    }

    dist[source] = 0;

    using Pair = pair<int, QString>;
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto top = pq.top();
        int d = top.first;
        QString u = top.second;
        pq.pop();

        if (d > dist[u]) continue;

        // iterate neighbours (QList<QPair<QString,int>>)
        const QList<QPair<QString,int>> &nbrs = graphAdjacency[u];
        for (int i = 0; i < nbrs.size(); ++i) {
            const QPair<QString,int> &nbr = nbrs.at(i);
            QString v = nbr.first;
            int w = nbr.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (!dist.contains(dest) || dist[dest] == INT_MAX) {
        ui->PathOut->setText("No Path Found!");
        return;
    }

    QStringList path;
    QString cur = dest;
    while (cur != source && !cur.isEmpty()) {
        path.prepend(cur);
        cur = parent[cur];
    }
    path.prepend(source);

    ui->PathOut->setText(QString("Cost: %1 | Path: %2")
                             .arg(dist[dest])
                             .arg(path.join(" -> ")));
}

