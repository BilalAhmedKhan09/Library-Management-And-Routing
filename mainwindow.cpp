#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>

using namespace std;

struct Node {
    string name;
    int ID;
    int height;
    Node *left;
    Node *right;
};

int getheight(Node *n){
    if(n == NULL){
        return 0;
    }
    else{
        return n->height;
    }
}

Node * newnode(int id, string name){
    Node *n = new Node;
    n->height = 1;
    n->ID = id;
    n->name = name;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int getbalancefactor(Node *n){
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

Node *minimum(Node *n){
    if(n == NULL){
        return n;
    }
    else if(n->left == NULL){
        return n;
    }
    return minimum(n->left);
}

Node *leftrotate(Node *b){
    Node *d = b->right;
    Node *c = d->left;

    d->left = b;
    b->right = c;
    b->height = 1 + max(getheight(b->left), getheight(b->right));
    d->height = 1 + max(getheight(d->left), getheight(d->right));
    return d;
}

Node *rightrotate(Node *d){
    Node *b = d->left;
    Node *c = b->right;

    b->right = d;
    d->left = c;
    b->height = 1 + max(getheight(b->left), getheight(b->right));
    d->height = 1 + max(getheight(d->left), getheight(d->right));
    return b;
}

Node *Insert(Node*n, int ID, string name){
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

Node *Delete(Node *n, int key){
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
            Node *temp = n->left;
            delete n;
            return temp;
        }
        if(n->left == NULL){
            Node *temp = n->right;
            delete n;
            return temp;
        }
        Node *temp = minimum(n->right);
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

Node* search(Node *root, int val){
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
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Node *root = nullptr;

void MainWindow::on_Search_clicked() // if clicked
{
    int ID = ui->searchID->text().toInt(); // converted to int
    if(!ui->searchID->text().isEmpty() && ID >= 0){ // checks for invalid search IDs
        qDebug() << "Searching for ID:" << ID;
        Node *n = search(root, ID);
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
