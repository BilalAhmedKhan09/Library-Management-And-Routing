#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include<QGraphicsEllipseItem>
#include <QPainter>
#include <QGraphicsSimpleTextItem>
#include <QMap>
#include <QString>

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


class Node : public QGraphicsEllipseItem {
public:
    QGraphicsTextItem *label;
    QList<QGraphicsLineItem*> edges; // connected edges

    Node(qreal x, qreal y, qreal radius, QString name ,QGraphicsItem *parent = nullptr)
        : QGraphicsEllipseItem(x, y, 2*radius, 2*radius, parent)
    {
        QColor colour(50, 150, 250);
        setBrush(QBrush(colour)); // fils colour blue in the node
        setPen(QPen(Qt::black, 1));
        label = new QGraphicsTextItem(name, this);
        label->setDefaultTextColor(Qt::black);
        QRectF textRect = label->boundingRect();
        QRectF r = rect(); // ellipse rect
        qreal a = textRect.height() + 30; // label just above the node
        label->setPos(x, a);
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    }

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override {
        QPointF newPos = value.toPointF();
        for (QGraphicsLineItem* line : edges) {
            Node* otherNode = reinterpret_cast<Node*>(line->data(1).value<void*>());
            if (otherNode == this) {
                QLineF l(line->line());
                l.setP1(mapToScene(rect().center()));
                line->setLine(l);
            } else {
                QLineF l(line->line());
                l.setP2(mapToScene(rect().center()));
                line->setLine(l);
            }
        }
        return QGraphicsEllipseItem::itemChange(change, value);
    }
};

class Edge :public QGraphicsLineItem {
public:
    Node *n1;
    Node *n2;

    Edge(Node *a, Node *b) {
        n1 = a;
        n2 = b;
        setPen(QPen(Qt::black, 1));
        updatePosition();

        // move with nodes:
        a->installSceneEventFilter(this);
        b->installSceneEventFilter(this);
    }

    void updatePosition() {
        QPointF p1 = n1->sceneBoundingRect().center();
        QPointF p2 = n2->sceneBoundingRect().center();
        setLine(QLineF(p1, p2));
    }

    bool sceneEventFilter(QObject *watched, QEvent *event) {
        if (event->type() == QEvent::GraphicsSceneMove) {
            updatePosition();
        }
        return false;
    }
};

QMap<QString, Node*> nodeMap;  // store all nodes by name

void MainWindow::on_AddNode_clicked()
{
    QString name = ui->Nname->text();
    Node *n = new Node(100,100,15,name);
    scene->addItem(n);
    nodeMap[name] = n;
}

void MainWindow::on_AddEdge_clicked()
{
    QString name1 = ui->N1->text();
    QString name2 = ui->N2->text();

    if (name1.isEmpty() || name2.isEmpty()) {
        return; // invalid input
    }

    Node *node1 = nullptr;
    Node *node2 = nullptr;

    // find the nodes in the scene by label
    for (QGraphicsItem *item : scene->items()) {
        Node *n = dynamic_cast<Node*>(item);
        if (n) {
            if (n->label->toPlainText() == name1) node1 = n;
            if (n->label->toPlainText() == name2) node2 = n;
        }
    }

    if (!node1 || !node2) {
        return; // nodes not found
    }

    // create the edge
    QPointF p1 = node1->mapToScene(node1->rect().center());
    QPointF p2 = node2->mapToScene(node2->rect().center());
    QGraphicsLineItem *line = new QGraphicsLineItem(QLineF(p1, p2));
    scene->addItem(line);

    // store edge in both nodes for movement
    node1->edges.append(line);
    node2->edges.append(line);

    // mark which end is which
    line->setData(0, 0); // temporary, not used for now
    // store p1/p2 info for automatic movement
    line->setData(1, QVariant::fromValue<void*>(node1));
    line->setData(2, QVariant::fromValue<void*>(node2));
}

