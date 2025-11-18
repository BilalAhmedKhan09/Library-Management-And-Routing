#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include<QGraphicsEllipseItem>
#include <QPainter>
#include <QGraphicsSimpleTextItem>

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

class Node: public QGraphicsEllipseItem{
    QGraphicsTextItem *label;
public:
    Node(qreal x, qreal y, qreal radius, QString name ,QGraphicsItem *parent = nullptr)
        : QGraphicsEllipseItem(x, y, 2 * radius, 2 * radius, parent) {
        QColor colour(50, 150, 250); // Lightblue
        setBrush(QBrush(colour)); // sets node colour
        setPen(QPen(Qt::black, 1)); // sets border colour
        label = new QGraphicsTextItem(name, this); // This binds the name to the actual node to move along with it
        label->setDefaultTextColor(Qt::black);
        //Get the length of the text and align it with the centre of the node
        QRectF textRect = label->boundingRect();
        qreal w = textRect.width()/2;
        label->setPos(115.0-w, 77.0);
        //For interactivity (drag and such)
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    }
};

void MainWindow::on_AddNode_clicked()
{
    QString name = ui->Nname->text();
    Node *n = new Node(100,100,15,name);
    scene->addItem(n);
}

