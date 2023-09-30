#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

Neurona::Neurona(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue, Neurona *sig)
{
    this->id=id;
    this->voltaje=voltaje;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->red=red;
    this->blue=blue;
    this->green=green;
    this->sig=sig;
}

void Administrar::agregrarInicio(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue)
{
    Neurona *tmp=new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue, nullptr);
    if(!h)
    {
        h=tmp;
    }
    else
    {
        tmp->sig=h;
        h=tmp;
    }
}

void Administrar::agregarFinal(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue)
{
    Neurona *tmp=new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue, nullptr);
    if(!h)
    {
        h=tmp;
    }
    else
    {
        Neurona *aux=h;

        while(aux->sig!=nullptr)
        {
            aux=aux->sig;
        }
        aux->sig=tmp;
    }
}

void Administrar::mostrar()
{
}

Administrar *lis= new Administrar();
int id, posicion_x, posicion_y, red, green, blue;
float voltaje;
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    std::string idStd = arg1.toStdString();
    bool band =! idStd.empty() && std::all_of(idStd.begin(), idStd.end(), [](char cad){
        return std::isdigit(static_cast<unsigned char>(cad));
    });

    if (band)
    {
        id= std::stoi(idStd);
    }
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    voltaje = arg1;
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    posicion_x = arg1;
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    posicion_y = arg1;
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    red = value;
}


void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    green = value;
}


void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    blue = value;
}


void MainWindow::on_pushButton_clicked()
{
    lis->agregrarInicio(id, voltaje, posicion_x, posicion_y, red, green, blue);
    vaciar();
}


void MainWindow::on_pushButton_2_clicked()
{
    lis->agregarFinal(id, voltaje, posicion_x, posicion_y, red, green, blue);
    vaciar();
}


void MainWindow::on_plainTextEdit_textChanged()
{

}


void MainWindow::on_pushButton_3_clicked()
{
    QString lista;
    Neurona *aux=lis->h;

    if(aux)
    {
        while(aux)
        {
            QString nstr = "Neurona: " + QString::number(aux->id) + "\n";
            nstr += "Voltaje: " + QString::number(aux->voltaje) + "\n";
            nstr += "Posicion X: " + QString::number(aux->posicion_x) + "\n";
            nstr += "Posicion Y: " + QString::number(aux->posicion_y) + "\n";
            nstr += "Rojo: " + QString::number(aux->red) + "\n";
            nstr += "Verde: " + QString::number(aux->green) + "\n";
            nstr += "Azul: " + QString::number(aux->blue) + "\n\n";

            lista += nstr;
            aux=aux->sig;
        }
    }
    else
    {
        lista = "No hay elementos en la lista...";
    }

    ui->plainTextEdit->setPlainText(lista);
}

void MainWindow::vaciar()
{
    id=0;
    voltaje=0.0;
    posicion_x=0;
    posicion_y=0;
    red=0;
    green=0;
    blue=0;

    ui->lineEdit->clear();
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);
    ui->spinBox_3->setValue(0);
    ui->verticalSlider->setValue(0);
    ui->verticalSlider_2->setValue(0);
    ui->verticalSlider_3->setValue(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home", tr("Text files (*.txt)"));

    if(!fileName.isNull())
    {
    QFile file(fileName);

    if(file.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&file);
        Neurona *actual= lis->h;
        while(actual)
        {
            out<<actual->id<<'*'<<actual->voltaje<<'*'<<actual->posicion_x<<'*'<<actual->posicion_y<<'*'<<actual->red
                <<'*'<<actual->green<<'*'<<actual->blue<<'*'<< '\n';
            actual=actual->sig;
        }
        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("Save File"), tr("Error al abrir el archivo"));
    }
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Text files (*.txt)"));

    if(!fileName.isNull())
    {
    QFile file(fileName);

    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString QLine = in.readLine();
            QStringList div = QLine.split('*');
            if(div.size()==7)
            {
                bool convert = false;
                int id=div[0].toInt(&convert);
                    if (!convert)
                    {
                        continue;
                    }

                    float voltaje = div[1].toFloat(&convert);
                    if (!convert)
                    {
                        continue;
                    }

                    int posicion_x = div[2].toInt(&convert);
                    if (!convert)
                    {
                        continue;

                    int posicion_y = div[3].toInt(&convert);
                    if (!convert)
                    {
                        continue;
                    }

                    int red = div[4].toInt(&convert);
                    if (!convert)
                    {
                        continue;
                    }

                    int green = div[5].toInt(&convert);
                    if (!convert)
                    {
                        continue;
                    }

                    int blue = div[6].toInt(&convert);
                    if (!convert)
                    {
                        continue;
                    }
                    if (lis != nullptr)
                    {
                        lis->agregrarInicio(id, voltaje, posicion_x, posicion_y, red, green, blue);
                    }
                    else
                    {
                        //'lis' no está inicializado
                    }
                }
            }
        }
    } file.close();
    }
        else
        {
            QMessageBox::warning(this, tr("Open File"), tr("Error al abrir el archivo"));
        }
}
