/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * See LICENSE for more informations.
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <tools/Settings.h>

namespace Ui {
class MainWindow;
}
class PlainTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class MainWindowTest;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionAbout_triggered();

private:
    void createConnections();
    void openFile(const QString &filePath);
    void showFile(const QString &filePath);
    PlainTextEdit *m_textEdit;
    Ui::MainWindow *ui;
    Settings m_settings;
};

#endif // MAINWINDOW_H
