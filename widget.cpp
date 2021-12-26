#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

Widget::~Widget()
{
}

void Widget::setupUi()
{
    QFont labelFont ("Times",12);
    //Label and dropdown for space
    QLabel * spaceLabel = new QLabel ("Space",this);
    spaceLabel->move(10,10);
    spaceLabel->setFont(labelFont);
    //Dropdown for space
    QComboBox * spaceComboBox = new QComboBox(this);
    spaceComboBox->move(100,10);
    spaceComboBox->setMinimumSize(150,10);
    spaceComboBox->addItems({"Select..","2D","3D"});
    //Save Choice in a variable
    /*connect(spaceComboBox, &QComboBox::currentTextChanged,[=](){
        QString space = spaceComboBox->currentText();
        qDebug()<<"Space is"<<space;
    });
    */


    //Label and dropdown for units
    QLabel * unitsLabel = new QLabel ("Units",this);
    unitsLabel->move(10,50);
    unitsLabel->setFont(labelFont);
    //Dropdown for units
    QComboBox * unitsComboBox = new QComboBox(this);
    unitsComboBox->move(100,50);
    unitsComboBox->setMinimumSize(150,10);
    unitsComboBox->addItems({"Select..","m","mm"});
    //Save choice in a variable
    /*connect(unitsComboBox, &QComboBox::currentTextChanged,[=](){
        QString units = unitsComboBox->currentText();
        qDebug()<<"Units are "<<units;
    });
    */

    //Label and dropdown for model
    QLabel * modelLabel = new QLabel ("Model",this);
    modelLabel->move(10,90);
    modelLabel->setFont(labelFont);
    //Dropdown for model
    QComboBox * modelComboBox = new QComboBox(this);
    modelComboBox->move(100,90);
    modelComboBox->setMinimumSize(150,10);
    modelComboBox->addItems({"Select","U","B","T"});

    //Label and line edit for parameter 1
    QLabel * parameter1Label = new QLabel ("Parameter 1",this);
    parameter1Label->move(10,160);
    parameter1Label->setFont(labelFont);
    //Line edit for parameter 1
    QLineEdit * parameter1LineEdit = new QLineEdit(this);
    parameter1LineEdit->move(100,160);
    parameter1LineEdit->setMinimumSize(150,10);
    parameter1LineEdit->setPlaceholderText("Radius");

    //Label and line edit for parameter 2
    QLabel * parameter2Label = new QLabel ("Parameter 2",this);
    parameter2Label->move(10,200);
    parameter2Label->setFont(labelFont);
    //line edit for paramter 2
    QLineEdit * parameter2LineEdit = new QLineEdit(this);
    parameter2LineEdit->move(100,200);
    parameter2LineEdit->setMinimumSize(150,10);
    parameter2LineEdit->setPlaceholderText("Width or Height");

    //Change parameter 2 based on the user input
    connect(modelComboBox,&QComboBox::currentTextChanged,[=](){
        int model = modelComboBox->currentIndex();
        switch (model){
        case 1:
            parameter1Label->setText("Radius");
            parameter2Label->setText("Height");
            break;
        case 2:
            parameter1Label->setText("Radius");
            parameter2Label->setText("Width");
            break;
        case 3:
            parameter1Label->setText("Radius");
            parameter2Label->setText("Width");
            break;
        }
    });

    //Save button
    QPushButton * saveButton = new QPushButton("Save",this);
    saveButton->move(100,400);
    connect(saveButton, &QPushButton::clicked,[=](){
        QString spaceSelection = spaceComboBox->currentText();

        QString unitsSelection = unitsComboBox->currentText();

        QString modelSelection = modelComboBox->currentText();

        QString parameter1Selection = parameter1LineEdit->text();

        QString parameter2Selection = parameter2LineEdit->text();

        //create a JSON Documents
        QJsonObject userSelection;
        userSelection.insert("model",modelSelection);
        userSelection.insert("space",spaceSelection);
        userSelection.insert("units",unitsSelection);
        userSelection.insert("parameter1",parameter1Selection);
        userSelection.insert("parameter2",parameter2Selection);

        QJsonDocument jsonDocument;
        jsonDocument.setObject(userSelection);
        QByteArray bytes = jsonDocument.toJson(QJsonDocument::Indented);
        QFile file("C:/Users/gooda/OneDrive/Desktop/simpleDialog/simpleDialogCodeOnly/specimenInfo.json");
        if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
            {
                QTextStream iStream( &file );
                iStream.setCodec( "utf-8" );
                iStream << bytes;
                file.close();
            }
        else
            {
                qDebug() << "file open failed";
            }
    QMessageBox::information(this,"Success","The input has been saved");

    });




}



