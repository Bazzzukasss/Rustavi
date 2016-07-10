#ifndef TINDICATOR_H
#define TINDICATOR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <QGridLayout>
using namespace std;

enum class IndicatorType{IND_ANALOG,IND_DIGIT};
class TIndicatorFrame : public QFrame
{
    Q_OBJECT
public:
    explicit TIndicatorFrame(QWidget *parent = 0);
    void setName(const QString& _name);
    void setType(IndicatorType _type);
    void setValues(const vector<short int>& _values);
    void setIndSize(int _size);
    void setIndPerLine(int _indPerLine);
    void addIndicator(const QString& _name);
    TIndicatorFrame& operator= (const TIndicatorFrame& _rhv);
signals:

public slots:

protected:
    void addWidget(int _ind);
private:
    IndicatorType type{IndicatorType::IND_DIGIT};
    int size{24};
    int indPerLine{-1};
    int addedIndPerLine{0};
    int lineCount{0};
    int ioValuesCount{0};
    QLabel* caption;
    QGridLayout* layout;
    vector<QLabel*> ioCaptions;
    vector<QLabel*> ioValues_a;
    vector<QPushButton*> ioValues_d;
    void clear();
};

#endif // TINDICATOR_H
