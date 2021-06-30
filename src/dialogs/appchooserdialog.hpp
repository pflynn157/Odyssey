//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QDialog>
#include <QString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>

class AppChooserDialog : public QDialog {
    Q_OBJECT
public:
    explicit AppChooserDialog(QString currentFile);
    ~AppChooserDialog();
private:
    QString currentFilePath;
    QVBoxLayout *layout;
    QTreeWidget *treeView;
    QDialogButtonBox *dialogButtons;
    QTreeWidgetItem *suggestedApps;
    QTreeWidgetItem *allApps;
    void loadAll(bool suggested);
    QStringList fileContent(QString file);
    QString secondHalf(QString line);
    void launchApp(QString exe);
private slots:
    void onItemDoubleClicked(QTreeWidgetItem *item);
    void onCancelClicked();
    void onOkClicked();
};

