#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <vector>
#include <QPalette>
#include <string>
#include <map>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
// class NumButton {
//     public:
//         NumButton();
//         NumButton(QString name, QString clicked, QString pressed, QString def);
//         ~NumButton();
//         QString getName();
//         void setStyle(QString style);
//         void on_pushButton_planeTextEdit__clicked() {
//             planeTextEdit_->setStyleSheet(clickedStyle);
//         }
//         void on_pushButton_planeTextEdit__pressed() {
//             planeTextEdit_->setStyleSheet(pressedStyle);
//         }

//     private:
//         QString name_;
//         QPlainTextEdit *planeTextEdit_;
//         QString clickedStyle;
//         QString pressedStyle;
//         QString defStyle;
// };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPlainTextEdit *currentPlainText;
    int currentVecIndex = 0;
    QString currentSign;
    std::string num1 = "", num2 = "";
    int system1 = 0, system2 = 0;
    std::vector<QPlainTextEdit*> vec;
    

private slots:
    void Answer(int a, int b, std::string sign);

    void setSignStyle();
    void setNumStyle();
    void setDefaultSettings();
    void setOutputStyle();
    void setArrowsStatus();
    void blockLeft();
    void blockRight();
    void unblockLeft();
    void unblockRight();

    void on_plainTextEdit_Num1_1_selectionChanged();
    void on_plainTextEdit_Num1_2_selectionChanged();
    void on_plainTextEdit_Num1_3_selectionChanged();
    void on_plainTextEdit_Num1_4_selectionChanged();
    void on_plainTextEdit_Num1_5_selectionChanged();
    void on_plainTextEdit_Num1_6_selectionChanged();
    void on_plainTextEdit_Num2_1_selectionChanged();
    void on_plainTextEdit_Num2_2_selectionChanged();
    void on_plainTextEdit_Num2_3_selectionChanged();
    void on_plainTextEdit_Num2_4_selectionChanged();
    void on_plainTextEdit_Num2_5_selectionChanged();
    void on_plainTextEdit_Num2_6_selectionChanged();


    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    
    void on_pushButton_0_pressed();
    void on_pushButton_1_pressed();
    void on_pushButton_2_pressed();
    void on_pushButton_3_pressed();
    void on_pushButton_4_pressed();
    void on_pushButton_5_pressed();
    void on_pushButton_6_pressed();
    void on_pushButton_7_pressed();
    void on_pushButton_8_pressed();
    void on_pushButton_9_pressed();
    

    void on_pushButton_Right_clicked();
    void on_pushButton_Left_clicked();
    void on_pushButton_ClearAll_clicked();
    void on_pushButton_Delete_clicked();

    void on_pushButton_Right_pressed();
    void on_pushButton_Left_pressed();
    void on_pushButton_ClearAll_pressed();
    void on_pushButton_Delete_pressed();

    void on_pushButton_Sum_clicked();
    void on_pushButton_Sub_clicked();
    void on_pushButton_Equal_clicked();

    void on_pushButton_Sum_pressed();
    void on_pushButton_Sub_pressed();
    void on_pushButton_Equal_pressed();    
};
#endif // MAINWINDOW_H
