#include "showmainwindow.h"

ShowMainWindow::ShowMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowTitle("Automated Grain Sizing");
	showWidget = new ShowWidget(this);
	setCentralWidget(showWidget);
	createActions();
	createMenus();
}

void ShowMainWindow::createActions()
{
	// Open Image
	openImageAction = new QAction("&Open Image(O)...", this);
	openImageAction->setShortcut(tr("Ctrl+O"));
	openImageAction->setToolTip("Open Image");

	// Load Parameter
	loadParameterAction = new QAction("&Load Parameter(L)...", this);
	loadParameterAction->setShortcut(tr("Ctrl+L"));
	loadParameterAction->setToolTip("Load Parameter");

	// Close Image
	closeImageAction = new QAction("&Close Image(C)", this);
	closeImageAction->setShortcut(tr("Ctrl+C"));
	closeImageAction->setToolTip("Close Image");

	// Save Parameter
	saveParameterAction = new QAction("&Save Parameter(S)", this);
	saveParameterAction->setShortcut(tr("Ctrl+S"));
	saveParameterAction->setToolTip("Save Parameter");

	// Save Parameter As
	saveParameterAsAction = new QAction("&Save Parameter As(A)...", this);
	saveParameterAsAction->setShortcut(tr("Ctrl+A"));
	saveParameterAsAction->setToolTip("Save Parameter As");

	// Quit
	quitAction = new QAction("&Quit(Q)", this);
	quitAction->setShortcut(tr("Ctrl+Q"));
	quitAction->setToolTip("Quit");
}

void ShowMainWindow::createMenus()
{
	// File Menu
	fileMenu = menuBar()->addMenu("&File(F)");
	fileMenu->addAction(openImageAction);
	fileMenu->addAction(loadParameterAction);
	fileMenu->addSeparator();
	fileMenu->addAction(closeImageAction);
	fileMenu->addAction(saveParameterAction);
	fileMenu->addAction(saveParameterAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAction);

	// Options Menu
	optionsMenu = menuBar()->addMenu("&Options(O)");

	// Help Menu
	helpMenu = menuBar()->addMenu("&Help(H)");
}