#include "settingsform.h"
#include "widget/widget.h"
#include "settings.h"
#include <QFont>
#include <QClipboard>
#include <QApplication>

SettingsForm::SettingsForm()
    : QObject()
{
    main = new QWidget(), head = new QWidget();
    QFont bold, small;
    bold.setBold(true);
    small.setPixelSize(13);
    headLabel.setText(tr("User Settings","\"Headline\" of the window"));
    headLabel.setFont(bold);

    nameLabel.setText(tr("Name","Username/nick"));
    statusTextLabel.setText(tr("Status","Status message"));
    idLabel.setText("Tox ID (click here to copy)");
    id.setFont(small);
    id.setTextInteractionFlags(Qt::TextSelectableByMouse);
    id.setReadOnly(true);
    id.setFrameStyle(QFrame::NoFrame);
    id.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    id.setFixedHeight(id.document()->size().height());

    videoTest.setText(tr("Test video","Text on a button to test the video/webcam"));
    enableIPv6.setText(tr("Enable IPv6 (recommended)","Text on a checkbox to enable IPv6"));
    enableIPv6.setChecked(Settings::getInstance().getEnableIPv6());
    useTranslations.setText(tr("Use translations","Text on a checkbox to enable translations"));
    useTranslations.setChecked(Settings::getInstance().getUseTranslations());

    main->setLayout(&layout);
    layout.addWidget(&nameLabel);
    layout.addWidget(&name);
    layout.addWidget(&statusTextLabel);
    layout.addWidget(&statusText);
    layout.addWidget(&idLabel);
    layout.addWidget(&id);
    layout.addWidget(&videoTest);
    layout.addWidget(&enableIPv6);
    layout.addWidget(&useTranslations);
    layout.addStretch();

    head->setLayout(&headLayout);
    headLayout.addWidget(&headLabel);

    connect(&videoTest, SIGNAL(clicked()), this, SLOT(onTestVideoClicked()));
    connect(&enableIPv6, SIGNAL(stateChanged(int)), this, SLOT(onEnableIPv6Updated()));
    connect(&idLabel, SIGNAL(clicked()), this, SLOT(copyIdClicked()));
}

SettingsForm::~SettingsForm()
{
}

void SettingsForm::setFriendAddress(const QString& friendAddress)
{
    id.setText(friendAddress);
}

void SettingsForm::show(Ui::Widget &ui)
{
    name.setText(ui.nameLabel->text());
    statusText.setText(ui.statusLabel->text());
    ui.mainContent->layout()->addWidget(main);
    ui.mainHead->layout()->addWidget(head);
    main->show();
    head->show();
}

void SettingsForm::onTestVideoClicked()
{
     Widget::getInstance()->showTestCamview();
}

void SettingsForm::onEnableIPv6Updated()
{
    Settings::getInstance().setEnableIPv6(enableIPv6.isChecked());
}

void SettingsForm::copyIdClicked()
{
    id.selectAll();;
    QApplication::clipboard()->setText(id.toPlainText());
}

void SettingsForm::onUseTranslationUpdated()
{
    Settings::getInstance().setUseTranslations(useTranslations.isChecked());
}
