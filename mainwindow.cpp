#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Expands textEdit to the full size of our window
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Clears the window
void MainWindow::on_actionNew_triggered() {
    file_path = "";
    ui->textEdit->clear();
}

// Opens a text file and displays it in textEdit
void MainWindow::on_actionOpen_triggered() {
    // Creates an open file dialog
    QString file_name = QFileDialog::getOpenFileName(this, "Open file");
    file_path = file_name; // Sets the global file path
    QFile file(file_name);

    // The file did not open correctly
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "The file is not open for reading");
        return;
    }

    // Creates a stream in reference to the file
    QTextStream instream(&file);
    QString text = instream.readAll().toUtf8();
    file.close();

    ui->textEdit->setText(text);
}

// Saves the text in textEdit to the file
void MainWindow::on_actionSave_triggered() {
    if (file_path == "") {
        QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
        file_path = file_name; // Sets the global file path
    }

    QFile file(file_path);

    // The file is not open correctly
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "The file is not open for writing");
    }

    // Writes the stream to the file
    QTextStream outstream(&file);
    QString text = ui->textEdit->toPlainText();

    outstream << text;
    file.flush();
    file.close();

}


void MainWindow::on_actionSave_as_triggered() {
    QString file_name = QFileDialog::getSaveFileName(this, "Save the file");
    QFile file(file_name);
    file_path = file_name; // Sets the global file path

    // The file is not open correctly
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Error", "The file is not open for writing");
    }

    // Writes the stream to the file
    QTextStream outstream(&file);
    QString text = ui->textEdit->toPlainText();

    outstream << text;
    file.flush();
    file.close();
}


// Cuts from the clipboard to the textEdit
void MainWindow::on_actionCut_triggered() {
    ui->textEdit->cut();
}

// Copies from the textEdit to the clipboard
void MainWindow::on_actionCopy_triggered() {
    ui->textEdit->copy();
}

// Pastes from the clipboard to the textEdit
void MainWindow::on_actionPaste_triggered() {
    ui->textEdit->paste();
}

// Redoes the previous action
void MainWindow::on_actionRedo_triggered() {
    ui->textEdit->redo();
}

// Undoes the previous action
void MainWindow::on_actionUndo_triggered() {
    ui->textEdit->undo();
}


void MainWindow::on_actionAbout_notepad_triggered() {

}

