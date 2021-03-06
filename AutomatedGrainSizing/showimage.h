#pragma once

#include <QtWidgets/QWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QIcon>
#include <QCursor>
#include <QImage>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPointF>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtMath>
#include <QStyleOption>
#include <QStyle>
#include <QTransform>
#include <cmath>
#include <opencv2/opencv.hpp>
#include "automatedgrainsizing.h"

#define imgW (showImage.size().width())	// image width
#define imgH (showImage.size().height())	// image height
#define winW (width())				// window width
#define winH (height())				// window height

class ShowImage: public QWidget
{
	Q_OBJECT

public:
	ShowImage(QWidget *parent = Q_NULLPTR);
	AutomatedGrainSizing *progressBar;

	QVector<QPointF> rawImage4Points;					// record 4  raw image points' pixel
	QVector<QPointF> rawImage2Points;					// record 2  raw image points' pixel
	QVector<QPointF> warpImage4Points;					// record 4 warp image points' pixel
	QVector<QPointF> warpImage2Points;					// record 2 warp image points' pixel
	QImage showImage;									// image to show
	QImage rawImage;									// store raw image
	QImage warpImage;									// store transform image
	cv::Mat perspectiveMatrix;							// perspective projection transform matrix
	vector<float> ellipseM;								// AGS M
	vector<float> ellipseL;								// AGS L

	void closeImage();									// close image
	bool loadImage(QString path);						// load image
	void loadParameter(QString filePathName);			// load parameter
	void saveFile(QString filePathName);				// save GSD
	void saveParameter(QString filePathName);			// save parameter
	
protected:
	float maxScale = 0.0f;								// maximum scale
	float minScale = 0.0f;								// minimun scale
	float scale = 0.0f;									// scale to draw
	QPointF newDelta;									// new displacement
	QPointF oldDelta;									// old displacement
	QPointF pos1;										// mouse press position 1
	QPointF pos2;										// mouse press position 2
	bool outBorder = 0;									// record point is out of border or not

	void resizeEvent(QResizeEvent *event);				// window resize
	void wheelEvent(QWheelEvent *event);				// wheel zoom in and out
	void mousePressEvent(QMouseEvent *event);			// mouse press		(overload from QWidget)
	void mouseMoveEvent(QMouseEvent *event);			// mouse move		(overload from QWidget)
	void mouseReleaseEvent(QMouseEvent *event);			// mouse release	(overload from QWidget)
	void keyPressEvent(QKeyEvent *event);				// keyboard press	(overload from QWidget)
	void paintEvent(QPaintEvent *event);				// drawing the result

private:
	QPoint realSize = QPoint(1000, 1000);				// record lineEdit size
	int mumax;											// record grain's max grain size
	QString filePathName;								// record file full path 

	bool image4PointsFulled = 0;						// image 4 points full
	bool image2PointsFulled = 0;						// image 2 points full
	bool image4PointModified = 1;						// record 4 points modified(0 - not mod, 1 - mod)
	bool image2PointModified = 1;						// record 2 points modified(0 - not mod, 1 - mod)
	bool realSizeModified = 1;							// record realSize modified
	bool loading = false;								// loading file
	bool finished = 0;									// record AGS had been finished or not
	int modifiedPointState = 0;							// record modify of points (0 to 6, 0 is not modified)
	int checkBoxState = 0;								// record checkBox state

	void initial();										// initial and rest widget
	void resetImage();									// reset image
	void addPoints(QMouseEvent *event);					// add points
	void addDragPoints(QMouseEvent *event);				// add drag points
	void modifyPoints(QMouseEvent *event);				// modify points
	void modifyDragPoints(QMouseEvent *event);			// modify drag points
	void clearPoints();									// clear points
	void deletePoints();								// delete points
	void raw2WarpImagePoints();							// raw image points to warp image points
	void warp2RawImagePoints();							// warp image points to raw image points
	QImage ShowImage::Mat2QImage(const cv::Mat& mat);	// Mat to QImage
	cv::Mat ShowImage::QImage2Mat(QImage image);		// QImage to Mat
	void perspectiveTransform();						// perspective projection transform
	bool checkPointLocation(QPointF imagePos);			// check point is in the image or not
	int getMuMax();										// get mu max
	
signals:
	void image4PointsModified(int num);					// 4 points modified
	void image2PointsModified(int num);					// 2 points modified
	void emitRealSize(QPoint);							// emit realSize
	void processingFinish(bool finished);				// process finished or not

private slots:
	void getRealSize(QPoint size);						// get lineEdit size
	void getCheckBoxState(int checkBoxState);			// get checkbox state
	void startProcessing();								// automated grained sizing
};
