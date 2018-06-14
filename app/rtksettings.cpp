#include "rtksettings.h"

RTKSettings::RTKSettings(QWidget *parent, rtkMain* rtk) : QWidget(parent)
{
    Serial = new serial();
    rtkmain = rtk;

    laRTKSettingName = new QLabel("RTK-Einstellungen");
    QFont headlineFont("Arial",15,QFont::Bold);
    laRTKSettingName->setFont(headlineFont);

    QFont defaultLabelFont("Arial",11);
    laSerialName = new QLabel("Input Serial:");
    laSerialName->setFont(defaultLabelFont);
    laTCPName = new QLabel("TCP Adresse:");
    laTCPName->setFont(defaultLabelFont);
    laPortName = new QLabel("TCP Port:");
    laPortName->setFont(defaultLabelFont);
    laStartSuccess = new QLabel();

    cbSerial = new QComboBox();
    laSerialDesc = new QLabel();

    leTCP = new QLineEdit();
    leTCP->setText(cDefaultTCP);
    leTCP->setFixedWidth(200);
    lePort = new QLineEdit();
    lePort->setText(cDefaultPort);
    lePort->setFixedWidth(50);

    horizontalLineWidget = new QWidget;
    horizontalLineWidget->setFixedHeight(2);
    horizontalLineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    horizontalLineWidget->setStyleSheet(QString("background-color: #0C0C0C;"));

    btReset = new QPushButton("Reset");
    btStart = new QPushButton(cStart);


    settingLabelLayout = new QHBoxLayout();
    settingLabelLayout->addWidget(laRTKSettingName,0,Qt::AlignLeft);

    serialLabelLayout = new QHBoxLayout();
    serialLabelLayout->addWidget(laSerialName,0,Qt::AlignLeft);

    serialLayout = new QHBoxLayout();
    serialLayout->addWidget(cbSerial,0,Qt::AlignLeft);
    serialLayout->addSpacing(10);
    serialLayout->addWidget(laSerialDesc);
    serialLayout->addStretch();

    TCPLabelLayout = new QHBoxLayout();
    TCPLabelLayout->addWidget(laTCPName,0,Qt::AlignLeft);
    TCPLabelLayout->addSpacing(140);
    TCPLabelLayout->addWidget(laPortName);
    TCPLabelLayout->addStretch();

    TCPLayout = new QHBoxLayout();
    TCPLayout->addWidget(leTCP,0,Qt::AlignLeft);
    TCPLayout->addSpacing(30);
    TCPLayout->addWidget(lePort);
    TCPLayout->addStretch(5);

    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(btReset,0,Qt::AlignLeft);
    buttonLayout->addWidget(laStartSuccess);
    buttonLayout->addWidget(btStart,0,Qt::AlignRight);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(settingLabelLayout);
    mainLayout->addLayout(serialLabelLayout);
    mainLayout->addLayout(serialLayout);
    mainLayout->addLayout(TCPLabelLayout);
    mainLayout->addLayout(TCPLayout);
    mainLayout->addWidget(horizontalLineWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    this->setLayout(mainLayout);

    connect(cbSerial,SIGNAL(currentIndexChanged(QString)),this,SLOT(updateSerialDesc(QString)));
    cbSerial->addItems(Serial->portsNames());

    connect(btReset,SIGNAL(clicked(bool)),this,SLOT(resetPressed()));
    connect(btStart,SIGNAL(clicked(bool)),this,SLOT(startPressed()));

    this->setLayout(mainLayout);
}

void RTKSettings::enableLayout(bool enable)
{
    cbSerial->setEnabled(enable);
    leTCP->setEnabled(enable);
    lePort->setEnabled(enable);
    btReset->setEnabled(enable);
}

void RTKSettings::updateComboBox(QStringList portNames)
{
    QString currentSerialName = cbSerial->currentText();
    while (cbSerial->count()) {
        cbSerial->removeItem(0);
    }
    cbSerial->addItems(portNames);
    int newIndex = cbSerial->findText(currentSerialName);
    if(newIndex != -1)
        cbSerial->setCurrentIndex(newIndex);
}

void RTKSettings::updateSerialDesc(const QString & portDesc)
{
    laSerialDesc->setText(Serial->getPortDescription(portDesc));
}

void RTKSettings::resetPressed()
{
    leTCP->setText(cDefaultTCP);
    lePort->setText(cDefaultPort);
}

void RTKSettings::startPressed()
{
    if(btStart->text() == cStart)
    {
        enableLayout(false);
        rtkmain->setParameters(cbSerial->currentText(), leTCP->text(), lePort->text());
        if(!rtkmain->startRtk())
        {
            enableLayout(true);
            laStartSuccess->setText(cStartError);
        }
        else {
            laStartSuccess->setText("");
            btStart->setText(cStop);
        }
    }
    else {
        rtkmain->stopRtk();
        btStart->setText(cStart);
        enableLayout(true);
    }
}
