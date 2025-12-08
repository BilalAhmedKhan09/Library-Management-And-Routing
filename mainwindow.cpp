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
#include <queue>
#include <utility>
#include <vector>
#include <functional>


using namespace std;

struct Record {
    string name;
    int ID;
    int height;
    Record *left;
    Record *right;
};

int getheight(Record *n){
    if(n == NULL){
        return 0;
    }
    else{
        return n->height;
    }
}

Record * newnode(int id, string name){
    Record *n = new Record;
    n->height = 1;
    n->ID = id;
    n->name = name;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int getbalancefactor(Record *n){
    if(n == NULL){
        return 0;
    }
    else{
        return getheight(n->left) - getheight(n->right);
    }
}

int max (int a , int b){
    return a>b?a:b;
}

Record *minimum(Record *n){
    if(n == NULL){
        return n;
    }
    else if(n->left == NULL){
        return n;
    }
    return minimum(n->left);
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
    if(n == NULL){
        return newnode(ID, name);
    }
    else if(ID < n->ID){
        n->left = Insert(n->left, ID, name);
    }
    else if(ID > n->ID){
        n->right = Insert(n->right, ID, name);
    }
    n->height = 1 + max(getheight(n->left), getheight(n->right));
    int bf = getbalancefactor(n);
    if(bf > 1 && ID < n->left->ID){
        return rightrotate(n);
    }
    else if(bf > 1 && ID > n->left->ID){
        n->left = leftrotate(n->left);
        return rightrotate(n);
    }
    else if(bf < -1 && ID > n->right->ID){
        return leftrotate(n);
    }
    else if(bf < -1 && ID < n->right->ID){
        n->right = rightrotate(n->right);
        return leftrotate(n);
    }
    return n;
}

Record *Delete(Record *n, int key){
    if(n == NULL){
        return n;
    }
    else if(key < n->ID){
        n->left = Delete(n->left, key);
    }
    else if(key > n->ID){
        n->right = Delete(n->right,key);
    }
    else{
        if(n->right == NULL){
            Record *temp = n->left;
            delete n;
            return temp;
        }
        if(n->left == NULL){
            Record *temp = n->right;
            delete n;
            return temp;
        }
        Record *temp = minimum(n->right);
        n->ID = temp->ID;
        n->name = temp->name;
        n->right = Delete(n->right, temp->ID);
    }
    n->height = 1 + max(getheight(n->left), getheight(n->right));
    int bf = getbalancefactor(n);
    if(bf > 1 && getbalancefactor(n->left) >= 0){ //left-left
        return rightrotate(n);
    }
    else if(bf > 1 && getbalancefactor(n->left) < 0){ //left-right
        n->left = leftrotate(n->left);
        return rightrotate(n);
    }
    else if(bf < -1 && getbalancefactor(n->right) <= 0){
        return leftrotate(n);
    }
    else if(bf < -1 && getbalancefactor(n->right) > 0){
        n->right = rightrotate(n->right);
        return leftrotate(n);
    }
    return n;
}

Record* search(Record *root, int val){
    if(root == NULL){
        return NULL;
    }
    else if(val < root->ID){
        return search(root->left, val);
    }
    else if(val > root->ID){
        return search(root->right, val);
    }
    else{
        return root;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this)) // Initialize scene in the constructor initializer list
    , view(new QGraphicsView(scene, this)) // Initialize view with scene
{
    ui->setupUi(this);
    // makes the right side widget the parent so the graph is built there
    view->setParent(ui->Graphwidget);
    // To make sure the graph fills the widget area
    QVBoxLayout *graphLayout = new QVBoxLayout(ui->Graphwidget);
    graphLayout->addWidget(view);
    // to make the graph and other widgets consistent set a screen size
     scene->setSceneRect(0, 0, 800, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Record *root = nullptr; // to start a tree initially

void MainWindow::on_Search_clicked() // if clicked
{
    int ID = ui->searchID->text().toInt(); // converted to int
    if(!ui->searchID->text().isEmpty() && ID >= 0){ // checks for invalid search IDs
        qDebug() << "Searching for ID:" << ID;
        Record *n = search(root, ID);
        // Display "Not Found" if search returns the empty string sentinel
        if (n == NULL) {
            ui->searchout->setText("Record Not Found");
        } else {
            ui->searchout->setText(QString::fromStdString(n->name)); // back to qstring and output
        }
    }
    else{
        ui->searchID->setText("Wrong Search ID");
    }
}

void MainWindow::on_AddRecord_clicked()
{
    int ID = ui->ID->text().toInt(); // converted to int
    string name = ui->Name->text().toStdString();
    if(!ui->ID->text().isEmpty() && name != "" && ID >= 0){ // checks for invalid inputs
        root = Insert(root, ID, name);
        qDebug() << "Inserted ID:" << ID << ". New root ID:" << (root ? root->ID : -1);
    }
    else{
        ui->Name->setText("Wrong input");
        ui->ID->setText("Wrong input");
    }
}

// -----------------------GRAPH FUNCTIONALITIES--------------------------------

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
    qreal labelY = y + 2*radius + 10; // a bit below the circle
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
    setPen(QPen(Qt::black, 2));
    updatePosition();

    // FIX: parent text to the edge so Qt manages it safely
    weightLabel = new QGraphicsTextItem(QString::number(w), this);
    weightLabel->setDefaultTextColor(Qt::red);

    // event filter for movement
    a->installSceneEventFilter(this);
    b->installSceneEventFilter(this);

    // register in nodes
    a->edges.append(this);
    b->edges.append(this);

    // adjacency
    graphAdjacency[a->getName()].append(qMakePair(b->getName(), w));
    graphAdjacency[b->getName()].append(qMakePair(a->getName(), w));
}

void Edge::updatePosition()
{
    if (!n1 || !n2) return;

    QPointF p1 = n1->sceneBoundingRect().center();
    QPointF p2 = n2->sceneBoundingRect().center();
    setLine(QLineF(p1, p2));

    if (scene() && weightLabel) {
        QPointF mid = (p1 + p2) / 2;
        weightLabel->setPos(mid);
    }
}

bool Edge::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    Q_UNUSED(watched);
    if (event->type() == QEvent::GraphicsSceneMove) {
        updatePosition();
    }
    return false;
}

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
}

// ========================= DIJKSTRA ==============================

void MainWindow::on_dijekstra_clicked()
{
    QString source = ui->source->text().trimmed();
    QString dest = ui->dest->text().trimmed();

    if (source.isEmpty() || dest.isEmpty()) {
        ui->pathOut->setPlainText("Enter Source and Destination");
        return;
    }

    if (!graphAdjacency.contains(source) || !graphAdjacency.contains(dest)) {
        ui->pathOut->setPlainText("Invalid source/destination!");
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
        ui->pathOut->setPlainText("No Path Found!");
        return;
    }

    QStringList path;
    QString cur = dest;
    while (cur != source && !cur.isEmpty()) {
        path.prepend(cur);
        cur = parent[cur];
    }
    path.prepend(source);

    ui->pathOut->setPlainText(QString("Cost: %1 | Path: %2")
                             .arg(dist[dest])
                             .arg(path.join(" -> ")));
}

