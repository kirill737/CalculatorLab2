#include "mainwindow.h"
#include "./ui_mainwindow.h"

bool lettersBlocked = false;
bool rightMoveBlocked = false;
bool leftMoveBlocked = true;
QString mainWindowColor = "background-color: #000000";
QString signColorOff = "border-radius: 20px;"
    "background-color: #F29C07 ;"
    "color: #FEFEFE;"
    "text-align: centre;";
    // "border: none;"; 
QString signColorOn = "border-radius: 20px;"
    "background-color:#FEFEFE ;"
    "color: #F29C07;"
    "border: none;"; 
QString signColorPressed = "border-radius: 20px;"
    "background-color:#FBC98E ;"
    "color: #FEFFFE;";
    // "border: none;"; 
QString numColorPressed = "border-radius: 20px;"
    "background-color: #737373;"
    "color: #FEFEFE;";
    // "border: none;"; 
QString numColorOff = "border-radius: 20px;"
    "background-color: #333333;"
    // "background-color: #6E6C6F;"
    "color: #FEFEFE;";
    // "border: none;"; 
QString numColorBlocked = "border-radius: 20px;"
    "background-color: #000000;"
    "color: #6E6C6F;"
    "border: 2px solid #6E6C6F;"; 
QString operationColorOff = "border-radius: 20px;"
    "background-color: #A5A5A5;"
    "color: #000000;";
    // "border: none;"; 
QString operationColorBlocked = "border-radius: 20px;"
    "border: 2px solid #A5A5A5;"
    "background-color: #000000;"
    "color: #A5A5A5;";
QString operationColorPressed = "border-radius: 20px;"
    "background-color: #D9D9D9;"
    "color: #000000;";
    // "border: none;"; 
QString outputColor = "border-radius: 5px;"
    "background-color: #333333;"
    "color: #FFFFFF;";
    // "border-style: outset;";
QString outputColorActive = "border-radius: 5px;"
    "background-color: #333333;"
    "color: #FFFFFF;"
    "border: 2px solid white;";
    // "border-style: outset;";
QString outputColorError = "border-radius: 5px;"
    "background-color: #333333;"
    "color: #FFFFFF;"
    "border: 2px solid #FF0000;";
QString signColor = "background-color: #000000;"
"color: #FFFFFF;";

std::map<char, int> Alfabet(){
    std::map<char, int> m;
    m['0'] = 0;
    m['1'] = 1;
    m['2'] = 2;
    m['3'] = 3;
    m['4'] = 4;
    m['5'] = 5;
    m['6'] = 6;
    m['7'] = 7;
    m['8'] = 8;
    m['9'] = 9;
    m['A'] = 10;
    m['B'] = 11;
    m['C'] = 12;
    m['D'] = 13;
    m['E'] = 14;
    m['F'] = 15;
    return m;
};

std::map<std::string, int> Signs(){
    std::map<std::string, int> m;
    m["+"] = 1;
    m["−"] = 2;
    m["×"] = 3;
    m["÷"] = 4;
    return m;
};

static std::map<char, int> alfabet_ = std::move(Alfabet());
static std::map<std::string, int> signs_ = std::move(Signs());

QString answer_;

long long Pow(int a, int n) { //возведение в степень
	if (n == 0) return 1;
	if (n % 2 == 0)	
        return Pow((a * a), n / 2);
	else
		return (a * Pow(a, n - 1));
}

long long To_dec(std::string num, int sys) { //перевод в десятичную СС
	long long res = 0;
	for (int i = 0; i < num.length(); i++) {
        if(num[num.length() - i - 1] != '0')
		    res += alfabet_[num[num.length() - i - 1]] * Pow(sys, i);
	}
	return res;
}

bool Sys_check(std::string num, int sys) { //проверка принадлежности числа своей СС
	for (int i = 0; i < num.length(); i++) {
		if (alfabet_[num[i]] >= sys) return false;
	}
	return true;
}

bool Date_check(std::pair<std::string, std::vector<int>> tmp) { //проверка введенной даты на корректность
	return !(tmp.second[5] > 59 || tmp.second[4] > 59 || tmp.second[3] > 23 || tmp.second[2] > 6 || tmp.second[1] > 52 || tmp.second[5] < 0 || tmp.second[4] < 0 || tmp.second[3]<0 || tmp.second[2]<0 || tmp.second[1]<0 || tmp.second[0]<0);
}
std::pair<std::string, std::vector<int>> plus(std::pair<std::string, std::vector<int>> f, std::pair<std::string, std::vector<int>> s); //Объявление функций заранее, тк они взаимозависимые
std::pair<std::string, std::vector<int>> minus(std::pair<std::string, std::vector<int>> f, std::pair<std::string, std::vector<int>> s);

std::pair<std::string, std::vector<int>> plus(std::pair<std::string, std::vector<int>> f, std::pair<std::string, std::vector<int>> s) { //Определение функций
	if (f.first == "-" && s.first != "-") {
		f.first = " ";
		return minus(s,f);
	}
	if (s.first == "-" && f.first != "-") {
		s.first = " ";
		return minus(f, s);
	}
	for (int i = 0; i < 6; i++) {
		f.second[i] += s.second[i];
	}
	f.second[4] += f.second[5] / 60;
	f.second[5] %= 60;
	
	f.second[3] += f.second[4] / 60;
	f.second[4] %= 60;

	f.second[2] += f.second[3] / 24;
	f.second[3] %= 24;

	f.second[1] += f.second[2] / 7;
	f.second[2] %= 7;

	f.second[0] += f.second[1] / 365;
	f.second[1] %= 365;
	
	if (f.first == "-") return std::make_pair("-", f.second);
	return std::make_pair(" ", f.second);
}

std::pair<std::string, std::vector<int>> minus(std::pair<std::string, std::vector<int>> f, std::pair<std::string, std::vector<int>> s) {
	if (f.first == "-" && s.first != "-") {
		s.first = "-";
		return plus(s, f);
	}
	if (s.first == "-" && f.first != "-") {
		s.first = " ";
		return plus(f, s);
	}
	if (f.first == "-" && s.first == "-") {
		std::swap(f, s);
	}
	if (f.second[5] < s.second[5]) {
		f.second[4]--;
		f.second[5] += 60;
	}
	if (f.second[4] < s.second[4]) {
		f.second[3]--;
		f.second[4] += 60;
	}
	if (f.second[3] < s.second[3]) {
		f.second[2]--;
		f.second[5] += 24;
	}
	if (f.second[2] < s.second[2]) {
		f.second[1]--;
		f.second[2] += 7;
	}
	if (f.second[1] < s.second[1]) {
		f.second[0]--;
		f.second[1] += 365;
	}
	for (int i = 0; i < 6; i++){
		f.second[i] -= s.second[i];
	}
	if (f.second[0] < 0) {
		f.second[0] = std::abs(f.second[0]);
		return std::make_pair("-", f.second);
	}
	return std::make_pair(" ", f.second);
}

// MainWindow::NumButton::NumButton() {
//     QString name_ = "";
//     clickedStyle = "";
//     pressedStyle = "";
//     defStyle = "";
//     setStyle(defStyle);
// }
// MainWindow::NumButton::NumButton(QString name, QString clicked, QString pressed, QString def) {
//     QString name_ = name;
//     clickedStyle = clicked;
//     pressedStyle = pressed;
//     defStyle = def;
//     setStyle(defStyle);
// }
// MainWindow::NumButton::~NumButton() {
//     name_ = nullptr;
//     clickedStyle = nullptr;
//     pressedStyle = nullptr;
//     defStyle = nullptr;
// }

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setDefaultSettings();
    ui->textEdit->setStyleSheet(outputColorError);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Answer(int a, int b, std::string sign) { //подсчет ответа
    switch (signs_[sign])
    {
    case 1:
        answer_ = QString::number(a + b);
        break;
    case 2:
        answer_ = QString::number(a - b);
        break;
    case 3:
        answer_ = QString::number(a * b);
        break;
    case 4:
        answer_ = QString::number((double)a / (double)b); //здесь нужно округление до 3х знаков после запятой
        break;
    default:
        break;
    }
}

void MainWindow::setDefaultSettings() {
    vec.clear();
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->label_4->setAlignment(Qt::AlignCenter);
    ui->label_5->setAlignment(Qt::AlignCenter);
    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_7->setAlignment(Qt::AlignCenter);
    ui->label_2->setStyleSheet("color: #FFFFFF;");
    ui->label_3->setStyleSheet("color: #FFFFFF;");
    ui->label_4->setStyleSheet("color: #FFFFFF;");
    ui->label_5->setStyleSheet("color: #FFFFFF;");
    ui->label_6->setStyleSheet("color: #FFFFFF;");
    ui->label_7->setStyleSheet("color: #FFFFFF;");
    
    vec.push_back(ui->plainTextEdit_Num1_1);
    vec.push_back(ui->plainTextEdit_Num1_2);
    vec.push_back(ui->plainTextEdit_Num1_3);
    vec.push_back(ui->plainTextEdit_Num1_4);
    vec.push_back(ui->plainTextEdit_Num1_5);
    vec.push_back(ui->plainTextEdit_Num1_6);
    vec.push_back(ui->plainTextEdit_Num2_1);
    vec.push_back(ui->plainTextEdit_Num2_2);
    vec.push_back(ui->plainTextEdit_Num2_3);
    vec.push_back(ui->plainTextEdit_Num2_4);
    vec.push_back(ui->plainTextEdit_Num2_5);
    vec.push_back(ui->plainTextEdit_Num2_6);
    currentVecIndex = 0;
    currentPlainText = vec[currentVecIndex];
    currentPlainText->setStyleSheet(outputColorActive);

    setSignStyle();
    setNumStyle();
    setOutputStyle();

    ui->label_Sign->setStyleSheet(signColor);
    ui->label_answerSign->setStyleSheet(signColor);
    ui->plainTextEdit_Answer_1->setStyleSheet(outputColor);
    ui->label->setStyleSheet("color: #FFFFFF;");
    currentPlainText->setStyleSheet(outputColorActive);

    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_Sign->setAlignment(Qt::AlignCenter);
    ui->label_answerSign->setAlignment(Qt::AlignCenter);

    setArrowsStatus();
}
void MainWindow::setOutputStyle() {
    ui->plainTextEdit_Num1_1->setStyleSheet(outputColor);
    ui->plainTextEdit_Num1_2->setStyleSheet(outputColor);
    ui->plainTextEdit_Num1_3->setStyleSheet(outputColor);
    ui->plainTextEdit_Num1_4->setStyleSheet(outputColor);
    ui->plainTextEdit_Num1_5->setStyleSheet(outputColor);
    ui->plainTextEdit_Num1_6->setStyleSheet(outputColor);
    ui->plainTextEdit_Num2_1->setStyleSheet(outputColor);
    ui->plainTextEdit_Num2_2->setStyleSheet(outputColor);
    ui->plainTextEdit_Num2_3->setStyleSheet(outputColor);
    ui->plainTextEdit_Num2_4->setStyleSheet(outputColor);
    ui->plainTextEdit_Num2_5->setStyleSheet(outputColor);
    ui->plainTextEdit_Num2_6->setStyleSheet(outputColor);
    ui->plainTextEdit_Answer_1->setStyleSheet(outputColor);
    ui->plainTextEdit_Answer_2->setStyleSheet(outputColor);
    ui->plainTextEdit_Answer_3->setStyleSheet(outputColor);
    ui->plainTextEdit_Answer_4->setStyleSheet(outputColor);
    ui->plainTextEdit_Answer_5->setStyleSheet(outputColor);
    ui->plainTextEdit_Answer_6->setStyleSheet(outputColor);
}
void MainWindow::setNumStyle() {
    ui->pushButton_0->setStyleSheet(numColorOff);
    ui->pushButton_1->setStyleSheet(numColorOff);
    ui->pushButton_2->setStyleSheet(numColorOff);
    ui->pushButton_3->setStyleSheet(numColorOff);
    ui->pushButton_4->setStyleSheet(numColorOff);
    ui->pushButton_5->setStyleSheet(numColorOff);
    ui->pushButton_6->setStyleSheet(numColorOff);
    ui->pushButton_7->setStyleSheet(numColorOff);
    ui->pushButton_8->setStyleSheet(numColorOff);
    ui->pushButton_9->setStyleSheet(numColorOff);

    ui->pushButton_ClearAll->setStyleSheet(operationColorOff);
    if (!rightMoveBlocked) {
        ui->pushButton_Right->setStyleSheet(operationColorOff);
    }
    if (!leftMoveBlocked) {
        ui->pushButton_Left->setStyleSheet(operationColorOff);
    }
    ui->pushButton_Delete->setStyleSheet(operationColorOff);
}
void MainWindow::setSignStyle() {
    this->setStyleSheet(mainWindowColor);
    ui->pushButton_Sub->setStyleSheet(signColorOff);
    ui->pushButton_Sum->setStyleSheet(signColorOff);
    ui->pushButton_Equal->setStyleSheet(signColorOff);
}

void MainWindow::blockLeft() {
    ui->pushButton_Left->setEnabled(false);
    ui->pushButton_Left->setStyleSheet(operationColorBlocked);
}
void MainWindow::blockRight() {
    ui->pushButton_Right->setEnabled(false);
    ui->pushButton_Right->setStyleSheet(operationColorBlocked);
}
void MainWindow::unblockLeft() {
    ui->pushButton_Left->setEnabled(true);
    ui->pushButton_Left->setStyleSheet(operationColorOff);
}
void MainWindow::unblockRight() {
    ui->pushButton_Right->setEnabled(true);
    ui->pushButton_Right->setStyleSheet(operationColorOff);
}

void MainWindow::setArrowsStatus() {
    ui->plainTextEdit_Num1_1->setPlainText("0");
    ui->plainTextEdit_Num1_2->setPlainText("0");
    ui->plainTextEdit_Num1_3->setPlainText("0");
    ui->plainTextEdit_Num1_4->setPlainText("0");
    ui->plainTextEdit_Num1_5->setPlainText("0");
    ui->plainTextEdit_Num1_6->setPlainText("0");
    ui->plainTextEdit_Num2_1->setPlainText("0");
    ui->plainTextEdit_Num2_2->setPlainText("0");
    ui->plainTextEdit_Num2_3->setPlainText("0");
    ui->plainTextEdit_Num2_4->setPlainText("0");
    ui->plainTextEdit_Num2_5->setPlainText("0");
    ui->plainTextEdit_Num2_6->setPlainText("0");
    currentPlainText = vec[currentVecIndex];
    currentPlainText->setStyleSheet(outputColorActive);
    switch (currentVecIndex)
    {
    case 0:
        blockLeft();
        unblockRight();
        leftMoveBlocked = true;
        rightMoveBlocked = false;
        break;
    case 11:
        unblockLeft();
        blockRight();
        leftMoveBlocked = false;
        rightMoveBlocked = true;
        break;
    default:
        unblockLeft();
        unblockRight();
        leftMoveBlocked = false;
        rightMoveBlocked = false;
        break;
    }
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
}

void MainWindow::on_plainTextEdit_Num1_1_selectionChanged() {
    currentVecIndex = 0;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num1_2_selectionChanged() {
    currentVecIndex = 1;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num1_3_selectionChanged() {
    currentVecIndex = 2;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num1_4_selectionChanged() {
    currentVecIndex = 3;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num1_5_selectionChanged() {
    currentVecIndex = 4;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num1_6_selectionChanged() {
    currentVecIndex = 5;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}

void MainWindow::on_plainTextEdit_Num2_1_selectionChanged() {
    currentVecIndex = 6;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num2_2_selectionChanged() {
    currentVecIndex = 7;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num2_3_selectionChanged() {
    currentVecIndex = 8;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num2_4_selectionChanged() {
    currentVecIndex = 9;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num2_5_selectionChanged() {
    currentVecIndex = 10;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}
void MainWindow::on_plainTextEdit_Num2_6_selectionChanged() {
    currentVecIndex = 11;
    currentPlainText = vec[currentVecIndex];
    setOutputStyle();
    currentPlainText->setStyleSheet(outputColorActive);
    setArrowsStatus();
    currentPlainText->setPlainText("");
}

void MainWindow::on_pushButton_Sum_pressed() {
    ui->pushButton_Sum->setStyleSheet(signColorPressed);
};
void MainWindow::on_pushButton_Sub_pressed() {
    ui->pushButton_Sub->setStyleSheet(signColorPressed);
};
void MainWindow::on_pushButton_Equal_pressed() {
    ui->pushButton_Equal->setStyleSheet(signColorPressed);
};

void MainWindow::on_pushButton_ClearAll_clicked() {
    ui->plainTextEdit_Num1_1->setPlainText("0");
    ui->plainTextEdit_Num1_2->setPlainText("0");
    ui->plainTextEdit_Num1_3->setPlainText("0");
    ui->plainTextEdit_Num1_4->setPlainText("0");
    ui->plainTextEdit_Num1_5->setPlainText("0");
    ui->plainTextEdit_Num1_6->setPlainText("0");
    ui->plainTextEdit_Num2_1->setPlainText("0");
    ui->plainTextEdit_Num2_2->setPlainText("0");
    ui->plainTextEdit_Num2_3->setPlainText("0");
    ui->plainTextEdit_Num2_4->setPlainText("0");
    ui->plainTextEdit_Num2_5->setPlainText("0");
    ui->plainTextEdit_Num2_6->setPlainText("0");
    ui->label_Sign->setText("");
    ui->plainTextEdit_Answer_1->setPlainText("");
    ui->plainTextEdit_Answer_2->setPlainText("");
    ui->plainTextEdit_Answer_3->setPlainText("");
    ui->plainTextEdit_Answer_4->setPlainText("");
    ui->plainTextEdit_Answer_5->setPlainText("");
    ui->plainTextEdit_Answer_6->setPlainText("");
    setDefaultSettings();
};
void MainWindow::on_pushButton_Right_clicked() {
    currentVecIndex++;
    setArrowsStatus();
}
void MainWindow::on_pushButton_Left_clicked() {
    currentVecIndex--;
    setArrowsStatus();
}
void MainWindow::on_pushButton_Delete_clicked() {
    QString text = currentPlainText->toPlainText();
    text.resize(text.size() - 1);
    currentPlainText->setPlainText(text);   
    setNumStyle();
}

void MainWindow::on_pushButton_ClearAll_pressed() {
    ui->pushButton_ClearAll->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Right_pressed() {
    ui->pushButton_Right->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Left_pressed() {
    ui->pushButton_Left->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Delete_pressed() {
    ui->pushButton_Delete->setStyleSheet(operationColorPressed);
}
void MainWindow::on_pushButton_Sum_clicked() {
    currentSign = "+";
    ui->label_Sign->setText(currentSign);
    setSignStyle();
    ui->pushButton_Sum->setStyleSheet(signColorOn);
};
void MainWindow::on_pushButton_Sub_clicked() {
    currentSign = "−";
    ui->label_Sign->setText(currentSign);
    setSignStyle();
    ui->pushButton_Sub->setStyleSheet(signColorOn);
};
void MainWindow::on_pushButton_Equal_clicked() {
    setSignStyle();
    ui->label_answerSign->setText("−"); //вот сюда знак ответа пихай
    std::string sign = currentSign.toStdString();
};

void MainWindow::on_pushButton_0_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "0");
    setNumStyle();
}
void MainWindow::on_pushButton_1_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "1");
    setNumStyle();
}
void MainWindow::on_pushButton_2_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "2");
    setNumStyle();
}
void MainWindow::on_pushButton_3_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "3");
    setNumStyle();
}
void MainWindow::on_pushButton_4_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "4");
    setNumStyle();
}
void MainWindow::on_pushButton_5_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "5");
    setNumStyle();
}
void MainWindow::on_pushButton_6_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "6");
    setNumStyle();
}
void MainWindow::on_pushButton_7_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "7");
    setNumStyle();
}
void MainWindow::on_pushButton_8_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "8");
    setNumStyle();
}
void MainWindow::on_pushButton_9_clicked() {
    QString text = currentPlainText->toPlainText();
    currentPlainText->setPlainText(text + "9");
    setNumStyle();
}

void MainWindow::on_pushButton_0_pressed() {
    ui->pushButton_0->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_1_pressed() {
    ui->pushButton_1->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_2_pressed() {
    ui->pushButton_2->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_3_pressed() {
    ui->pushButton_3->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_4_pressed() {
    ui->pushButton_4->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_5_pressed() {
    ui->pushButton_5->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_6_pressed() {
    ui->pushButton_6->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_7_pressed() {
    ui->pushButton_7->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_8_pressed() {
    ui->pushButton_8->setStyleSheet(numColorPressed);
}
void MainWindow::on_pushButton_9_pressed() {
    ui->pushButton_9->setStyleSheet(numColorPressed);
}
