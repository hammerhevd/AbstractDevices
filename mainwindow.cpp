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

void MainWindow::on_pushButton_clicked()
{
    QString serial, model, freq, freq_d, interfaces, gpio;

    // Проверка на выбор параметров устройства и параметров портов GPIO

    if(ui->comboBox->currentText().isNull() || ui->comboBox_2->currentText().isNull()
            || ui->comboBox_3->currentText().isNull() || ui->comboBox_4->currentText().isNull())
    {              
        ui->textBrowser->setText("> Выберите параметры устройства");
        QMessageBox::warning(this,"Внимание!", "Выберите параметры устройства");
    }

    else if (ui->checkBox_8->isChecked() && (ui->comboBox_5->currentText().isNull() || ui->comboBox_6->currentText().isNull()))
    {
        ui->textBrowser->setText("> Выберите параметры GPIO A");
        QMessageBox::warning(this,"Внимание!", "Выберите параметры GPIO A");
    }

    else if (ui->checkBox_9->isChecked() && ui->comboBox_7->currentText().isNull() && ui->comboBox_8->currentText().isNull())
    {
        ui->textBrowser->setText("> Выберите параметры GPIO B");
        QMessageBox::warning(this,"Внимание!", "Выберите параметры GPIO B");
    }

    else if (ui->checkBox_10->isChecked() && ui->comboBox_9->currentText().isNull() && ui->comboBox_10->currentText().isNull())
    {
        ui->textBrowser->setText("> Выберите параметры GPIO C");
        QMessageBox::warning(this,"Внимание!", "Выберите параметры GPIO C");
    }

    else if (ui->checkBox_11->isChecked() && ui->comboBox_11->currentText().isNull() && ui->comboBox_12->currentText().isNull())
    {
        ui->textBrowser->setText("> Выберите параметры GPIO D");
        QMessageBox::warning(this,"Внимание!", "Выберите параметры GPIO D");
    }

    // Все что касается парметров устройства (Серия, модель, частоты)

    else
    {
        serial = "Серия устройства: " + ui->comboBox->currentText() + ", ";
        freq   = "Частота тактирования: " + ui->comboBox_2->currentText() + " МГц, ";
        model  = "Модель устройства: " + ui->comboBox_3->currentText() + ", ";
        freq_d = "Частота тактирования ПУ: " + ui->comboBox_4->currentText() + " МГц, ";

        // Всё что касается выбора интерфейсов

        if (ui->checkBox->isChecked() || ui->checkBox_2->isChecked() || ui->checkBox_3->isChecked() ||
                ui->checkBox_4->isChecked() || ui->checkBox_5->isChecked() || ui->checkBox_6->isChecked() ||
                ui->checkBox_7->isChecked())
        {
            interfaces = "Задействованные интерфейсы: ";

            if (ui->checkBox->isChecked())
            {
                interfaces += "USB, ";
            }

            if (ui->checkBox_2->isChecked())
            {
                interfaces += "UART, ";
            }

            if (ui->checkBox_3->isChecked())
            {
                interfaces += "SPI, ";
            }

            if (ui->checkBox_4->isChecked())
            {
                interfaces += "I2C, ";
            }

            if (ui->checkBox_5->isChecked())
            {
                interfaces += "Ethernet, ";
            }

            if (ui->checkBox_6->isChecked())
            {
                interfaces += "1-Wire, ";
            }

            if (ui->checkBox_7->isChecked())
            {
                interfaces += "Многоразрядная шина, ";
            }
        }

        else interfaces = "Интерфейсы передачи данных не задействованы. ";

        // Всё что касается выбора портов GPIO

        if (ui->checkBox_8->isChecked() || ui->checkBox_9->isChecked()
                || ui->checkBox_10->isChecked() || ui->checkBox_11->isChecked())
        {
            gpio = "Задействованные порты GPIO: ";

            if (ui->checkBox_8->isChecked())
            {
                gpio += "PORT A: ";
                gpio += ui->comboBox_5->currentText() +", ";
                gpio += ui->comboBox_6->currentText() +". ";
            }

            if (ui->checkBox_9->isChecked())
            {
                gpio += "PORT B: ";
                gpio += ui->comboBox_7->currentText() +", ";
                gpio += ui->comboBox_8->currentText() +". ";
            }

            if (ui->checkBox_10->isChecked())
            {                   
                gpio += "PORT C: ";
                gpio += ui->comboBox_9->currentText() +", ";
                gpio += ui->comboBox_10->currentText() +". ";
            }

            if (ui->checkBox_11->isChecked())
            {

                gpio += "PORT D: ";
                gpio += ui->comboBox_11->currentText() +", ";
                gpio += ui->comboBox_12->currentText() +". ";
            }
        }

        else gpio = "Порты GPIO не задействованы. ";

        // Всё что касается предварительного вывода информации в диалоговое окно

        QString inf = serial + "\n" + model + "\n" + freq + "\n" + freq_d + "\n" + interfaces + "\n" + gpio;

        QMessageBox::information(this,"Задействованные интерфейсы",inf);

        // Запись в файл

        QFile file ("C:/Users/User/Documents/AbstractDevice/config.txt");
        if(!file.open(QFile::Append | QFile::Text))
        {
    //        QMessageBox::warning(this,"Внимание", "Файл не закрыт");
        }
        QTextStream out(&file);
        out << inf << Qt::endl << "\n";
        file.flush();
        file.close();       
        ui->textBrowser->setText("> Файл конфигурации записан");

    }
}

// Открытие файла конфигурации и вывод его в text browser

void MainWindow::on_pushButton_2_clicked()
{

    QFile file = QFileDialog::getOpenFileName(this, "Выберите файл", "C:/Users/User/Documents/AbstractDevice/" );
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str = stream.readAll();
        ui->textBrowser->setText("> " + str);
        file.close();
    }

}

// Cохранение файла конфигурации в формате JSON

void MainWindow::on_pushButton_3_clicked()
{
        QJsonObject textObject;
        QJsonObject m_currentJsonObject;
        textObject["Serial "] = ui->comboBox->currentText();
        textObject["Model "] = ui->comboBox_3->currentText();
        textObject["Frequency "] = ui->comboBox_2->currentText();
        textObject["Device frequency "] = ui->comboBox_4->currentText();

        // Не успел доработать исключения и добавить параметры конфигурации портов GPIO и

        QJsonArray textArray = m_currentJsonObject["Abstract Devices"].toArray();
        textArray.append(textObject);
        m_currentJsonObject["Abstract Devices"]=textArray;

//          ui->textBrowser->setText(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));

        QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Json file"),QString(), tr("JSON(*.json)"));;
        QFileInfo fileInfo(saveFileName);
        QDir::setCurrent(fileInfo.path());
        QFile jsonFile(saveFileName);
        if (!jsonFile.open(QIODevice::WriteOnly))
        {
            return;
        }

        jsonFile.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
        jsonFile.close();
}

