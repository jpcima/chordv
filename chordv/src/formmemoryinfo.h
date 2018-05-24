#ifndef FORMMEMORYINFO_H
#define FORMMEMORYINFO_H

#include <QWidget>

namespace Ui {
class FormMemoryInfo;
}

///
/// \brief The FormMemoryInfo class manage the ùmemory information configuration and execution parameter like FormConfig
///
///
class FormMemoryInfo : public QWidget
{
    Q_OBJECT

public:
    ///
    /// \brief FormMemoryInfo constructor complient with Designer call of widget children
    /// \param parent
    ///
    explicit FormMemoryInfo(QWidget *parent = 0);
    ~FormMemoryInfo();

private:
    Ui::FormMemoryInfo *ui;
    ///
    /// \brief Init init all the records from setting file
    ///
    void Init();

public:
    ///
    /// \brief Save save all the records in setting file
    ///
    void Save();
private slots:
    void ShowSelectedFont(QFont, QColor, QColor);
};

#endif // FORMMEMORYINFO_H
