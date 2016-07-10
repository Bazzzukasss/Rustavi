#include "TIndicatorFrame.h"

TIndicatorFrame::TIndicatorFrame(QWidget *parent) :
    QFrame(parent)
{
    QFont font=this->font();
    QVBoxLayout* vLayout=new QVBoxLayout(this);
    vLayout->setSpacing(2);
    vLayout->setMargin(2);
    caption=new QLabel("noname",this);
    font.setBold(true);
    caption->setFont(font);
    caption->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Policy::Fixed);
    caption->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(caption);

    layout=new QGridLayout();
    layout->setSpacing(2);
    layout->setMargin(2);
    vLayout->addLayout(layout);
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    vLayout->addSpacerItem(spacer);
}

void TIndicatorFrame::setName(const QString &_name)
{
    caption->setText(_name);
}

void TIndicatorFrame::setType(IndicatorType _type)
{
    type=_type;
}

void TIndicatorFrame::setValues(const vector<short int> &_values)
{
    int valuesCount=_values.size();
    int count=min(ioValuesCount,valuesCount);
    for(int i=0;i<count;i++)
    {
        if(type==IndicatorType::IND_ANALOG)
            ioValues_a[i]->setText(QString().number(_values[i]));
        else
            ioValues_d[i]->setChecked(_values[i]);
    }
}
void TIndicatorFrame::setIndSize(int _size)
{
    size=_size;
    for(auto& b:ioValues_d)
    {
        b->setMaximumSize(size,size);
        b->setMinimumSize(size,size);
    }
}

void TIndicatorFrame::setIndPerLine(int _indPerLine)
{
    indPerLine=_indPerLine;
}
void TIndicatorFrame::addIndicator(const QString &_name)
{
    ioCaptions.push_back(new QLabel(_name,this));
    if(type==IndicatorType::IND_ANALOG)
        ioValues_a.push_back(new QLabel(0,this));
    else
        ioValues_d.push_back(new QPushButton(this));
    addWidget(ioValuesCount);
    ioValuesCount++;
}

TIndicatorFrame &TIndicatorFrame::operator=(const TIndicatorFrame &_rhv)
{
    if(this!=&_rhv)
    {
        clear();
        type=_rhv.type;
        size=_rhv.size;
        indPerLine=_rhv.indPerLine;
        for(int i=0;i<_rhv.ioValuesCount;i++)
            addIndicator(_rhv.ioCaptions[i]->text());
    }
    return *this;
}

void TIndicatorFrame::addWidget(int _ind)
{
    QPushButton* pButton;
    QLabel* pLabel;
    QFont font=this->font();
    int isCaption(1);

    pLabel= new QLabel(QString().number(_ind),this);
    font.setBold(true);
    pLabel->setFont(font);
    pLabel->setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed);
    pLabel->setAlignment(Qt::AlignLeft);
    layout->addWidget(pLabel,addedIndPerLine+isCaption,lineCount*3);

    if(type==IndicatorType::IND_ANALOG)
    {
        pLabel= ioValues_a[_ind];
        font.setBold(true);
        pLabel->setFont(font);
        layout->addWidget(pLabel,addedIndPerLine+isCaption,lineCount*3+2);

        pLabel= ioCaptions[_ind];
        pLabel->setFont(this->font());
        layout->addWidget(pLabel,addedIndPerLine+isCaption,lineCount*3+1,Qt::AlignLeft);
    }
    else
    {
        pButton=ioValues_d[_ind];
        pButton->setEnabled(false);
        pButton->setCheckable(true);
        pButton->setMaximumSize(size,size);
        pButton->setMinimumSize(size,size);
        pButton->setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Policy::Fixed);
        layout->addWidget(pButton,addedIndPerLine+isCaption,lineCount*3+1);
        pLabel= ioCaptions[_ind];
        pLabel->setFont(this->font());
        layout->addWidget(pLabel,addedIndPerLine+isCaption,lineCount*3+2,Qt::AlignLeft);

    }


    addedIndPerLine++;
    if(addedIndPerLine>=indPerLine)
    {
        lineCount++;
        addedIndPerLine=0;
    }
}

void TIndicatorFrame::clear()
{
    for(int i=0;i<ioValuesCount;i++)
    {
        delete ioCaptions[i];
        delete ioValues_a[i];
        delete ioValues_d[i];
    }
    ioValuesCount=0;
    addedIndPerLine=0;
    lineCount=0;
}
