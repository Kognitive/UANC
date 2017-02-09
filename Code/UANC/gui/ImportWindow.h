/*
 * ImportWindow.h
 *
 *  Created on: 06.02.2017
 *      Author: Vladimir Roskin
 */

#ifndef CODE_UANC_GUI_IMPORTWINDOW_H_
#define CODE_UANC_GUI_IMPORTWINDOW_H_

#include <memory>
#include <iostream>
#include <unordered_map>

//QT-stuff
#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QWidget>

//The util for loading and saving files
#include "Code/UANC/util/DialogUtil.h"

namespace uanc {
namespace gui {

class ImportWindow :public QMainWindow {

 Q_OBJECT

 public:


  /** \brief Obtain a reference to the Importer window.
   *
   * Uses a classical singleton pattern to give back exactly the same copy of the main window.
   *
   * @return The shared pointer containing the Importer Window
   */
  static std::shared_ptr<ImportWindow> get();


 private:

  /**
   * Adds a new signal from the file system to the list of selected signals
   */
  void addSignal();

  /**
   * Initializes the list of recently used signals
   */
  void loadRecentlyUsedSignals();

  /** \brief Sets up the import window.
   *
   */
  void setupGUI();


  /** \bief The default constructor
   */
  ImportWindow();

  //Layout elements
  QWidget *centralWidget;
  QVBoxLayout *mainWidgetVerticalLayout;
  QGroupBox *filesGroupBox;
  QVBoxLayout *mainWidgetGroupLayout;
  QVBoxLayout *filesMainVerticalLayout;
  QPushButton *addSelectedFilesButton;
  QVBoxLayout *filesInnerVertivalLayout;
  QScrollArea *selectedFilesScrollArea;
  QWidget *scrollAreaWidgetContents;
  QVBoxLayout *verticalLayout_13;
  QGroupBox *RecentlyUsedGroupBox;
  QVBoxLayout *verticalLayout_10;
  QComboBox *recentlyUsedCombo;
  QGroupBox *importGroupBox;
  QVBoxLayout *verticalLayout_7;
  QCheckBox *normalizeCheckBox;
  QGroupBox *actionsGroupBox;
  QHBoxLayout *actonLayout;
  QPushButton *importButton;
  QPushButton *cancelButton;
  QStatusBar *statusBar;

  //Gui-Elements for a loaded file
  struct selectedPathLoadedElements {
    QHBoxLayout selectedEntryHorizontalLayout;
    QLineEdit selectedEntryPath;
    QPushButton *selectEntryRemove;
  };

  //Hash function for the keys of the selected files
  std::hash<std::string> pathHash;

  //Key values for the selected files.
  std::vector<size_t> selectedFilePathKeys;

  //Maps for selected files
  std::unordered_map <size_t, selectedPathLoadedElements> selectedPathHashMap;

  QHBoxLayout *selectedEntryHorizontalLayout_0;
  QLineEdit *selectedEntryPath_0;
  QPushButton *selectEntryRemove_0;

  /** \brief Shared pointer to the one and only instance of ImportWindow.
   */
  static std::shared_ptr<ImportWindow> _instance;

  private slots:
  /**
   * Closes the window if "cancel" is clicked.
   */
  void applyCancel();

  /**
   * Imports the selected files
   */
  void importFiles();

  /**
   * Adds new files to list of selected files.
   */
  void addFilesToSelectes();

  /**
   * Removes the selected file from the import list
   */
  void removeSelectedSignal(int signalIndex);



};

}}

#endif /* CODE_UANC_GUI_IMPORTWINDOW_H_ */
