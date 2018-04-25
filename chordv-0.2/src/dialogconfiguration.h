#ifndef DIALOGCONFIGURATION_H
#define DIALOGCONFIGURATION_H

#include <QDialog>

#include <QComboBox>
#include <QTranslator>

namespace Ui {
class DialogConfiguration;
}

class DialogConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfiguration(QWidget *parent = 0);
    void setTranslator( QTranslator *translator);
    ~DialogConfiguration();
    void InitSettings();
    static void setLanguageComboBox(QComboBox *ptr);
    static QString getTranslationQmFileName(QString lang);
private slots:
    void Save();
    void SetPDFReader();
    void SelectLanguage(QString lang);
private:
    Ui::DialogConfiguration *ui;
    QWidget *m_parent;
    QTranslator *m_translator;
    void Connect();
    void Retranslate(QString lang);
signals:
    void LanguageChanged(QString lang);
    void PdfReaderChanged();
};

#endif // DIALOGCONFIGURATION_H
