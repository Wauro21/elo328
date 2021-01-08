#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	/* Load default track icon */
	QPixmap imagen;
	imagen.load("../F1RacingLine/GUI_IMG/icon_track0.jpg");
	ui->trackViewer->setPixmap(imagen);

	lwin = new LoadWin();
	connect(this, SIGNAL(updateBar(int)), lwin->pBar, SLOT(setValue(int)));
}

/* Boton para seleccionar archivo de IMAGEN/VIDEO */
void MainWindow::on_videoButton_clicked()
{
	filename = QFileDialog::getOpenFileName(
				this, tr("Open File"), "../F1RacingLine/NewTelemtry",
				tr("Images/Video (*.png *.jpeg *.jpg *.bmp *.mp4 *.mov)"));
	ui->videoPath->setText(filename);
}

/* Boton para seleccionar archivo CSV/TXT */
void MainWindow::on_csvButton_clicked()
{
	filenameUDP = QFileDialog::getOpenFileName(
				this, tr("Open File"), "../F1RacingLine/NewTelemetry",
				tr("Comma Separted Values (*.csv *.txt)"));
	ui->csvPath->setText(filenameUDP);
}

/* Boton de Modo Imagen */
void MainWindow::on_runButton_clicked()
{
	std::string inputIMG = filename.toStdString();
	cv::Mat out;

	mainProcessing(inputIMG, out, filenameUDP.toStdString(), MODO_IMG);
	cv::resize(out, out, cv::Size(1280, 720));
	cv::imshow("Result", out);
	cv::waitKey(0);
}

/* Boton de Modo Video */
void MainWindow::on_runvideoButton_clicked()
{
	lwin->show();
	std::string inputIMG = filename.toStdString();
	cv::Mat out;
	mainProcessing(inputIMG, out, filenameUDP.toStdString(), MODO_VID);
	lwin->close();
}

/* Seleccion de la pista de Carreras (SOLO IMPLEMENTADO PARA SIVLERSTONE) */
void MainWindow::on_trackSelection_currentIndexChanged(int index)
{
	QString file = "../F1RacingLine/GUI_IMG/icon_track";
	file += QString::number(index) + ".jpg";

	QPixmap trackIcon;
	trackIcon.load(file);
	ui->trackViewer->setPixmap(trackIcon);
}

void MainWindow::on_actionAbout_this_project_triggered()
{
	QMessageBox about;
	about.setWindowTitle("About This Project");
	about.setText("Proyecto ELO328 - 2020.S2\n"
					"Sistema de Reconocimiento de Pista de F1\n\n"
					"Autores: \tMauricio Aravena\n"
					"\tDiego Badillo\n"
					"\tSteev Gonzalez\n"
					"\tSebastian Neira\n"
					"\tFelipe Villenas");
	about.exec();
}

MainWindow::~MainWindow(){ delete ui; }
void MainWindow::on_exitButton_clicked(){ this->close(); }
void MainWindow::on_videoPath_textChanged(const QString &arg1){ filename = arg1; }
void MainWindow::on_csvPath_textChanged(const QString &arg1){ filenameUDP = arg1; }

/* --------------- Metodos ---------------------- */
void MainWindow::mainProcessing(std::string inputFile, cv::Mat& dst, std::string csvFile, bool mode)
{
	//Lectura puntos telemetria
	bool selCSV[] = {true, false, true, true, false, true};
	readVector readUDP = readFile(csvFile, csvSkip, nColsCSV, selCSV); // lee posición y orientación del auto

	// Modo Imagen
	if(!mode){
		cv::Mat src = cv::imread(inputFile.c_str());
		dst = frameProcessing(src, readUDP[0]);
	}
	// Modo Video
	else{
		cv::VideoCapture videoFile(inputFile.c_str());
		double N_frames = (double)videoFile.get(cv::CAP_PROP_FRAME_COUNT);	// numero de frames del video
		double n_frame = 0.0;
		cv::Size S = cv::Size((int)videoFile.get(cv::CAP_PROP_FRAME_WIDTH),(int)videoFile.get(cv::CAP_PROP_FRAME_HEIGHT));
		double FPS = videoFile.get(cv::CAP_PROP_FPS);
		cv::VideoWriter TEST("out.mp4",cv::VideoWriter::fourcc('m', 'p', '4','v'),FPS,S);

		std::cout << "Numero Frames = " << N_frames << std::endl;
		while(true){
			cv::Mat frame;
			videoFile >> frame;
			if(frame.empty()){
				break;
			}

			cv::Mat out = frameProcessing(frame, readUDP[(int)n_frame]);
			TEST << out;
			n_frame++;
			int curr_value = (int)(n_frame*100/N_frames);
			emit updateBar(curr_value);
			cv::imshow("Video", out);
			char c=(char)cv::waitKey(25);
			if(c == 27){
				break;
			}
		}
		videoFile.release();
		cv::destroyAllWindows();
	}

	return;
}

cv::Mat MainWindow::frameProcessing(cv::Mat& img, std::vector<float> readUDP){

	cv::Mat img2 = img.clone(); // copia de imagen para superposición final de la línea de carreras
	cv::Mat invMatrix; //matriz de proyección inversa
	cv::Mat crop = projection(img, invMatrix); // ROI con proyección bidimensional
	cv::Mat X = getEdges(crop); // segmentación de la proyección a imagen binaria
	std::vector<double> pLeft, pRight;
	cv::Mat mask = getMask(crop, pLeft, pRight); // imagen con máscara de la pista
	//####################################################################

	// Mejorar este "diccionario--------------------------------------------
	std::string trackArray[] = {"silverstone_2020_centerline.track","silverstone_2020_innerlimit.track", "silverstone_2020_outerlimit.track","silverstone_2020_racingline.track"};
	bool selCols[] = {false, true, true, false, false, false};
	//Carga lineas pista
	Matrix innerLimit(readFile(SILVERPATH + trackArray[1], trackSkip, nColsTrack, selCols));
	Matrix outerLimit(readFile(SILVERPATH + trackArray[2], trackSkip, nColsTrack, selCols));
	Matrix raceLine(readFile(SILVERPATH+trackArray[3], trackSkip, nColsTrack, selCols));

	//ventana
	Matrix wInnerLimit = Mwindow(innerLimit, readUDP[0], readUDP[1], windowRes);
	Matrix wOuterLimit = Mwindow(outerLimit, readUDP[0], readUDP[1], windowRes);
	Matrix wRaceLine = Mwindow(raceLine, readUDP[0], readUDP[1], windowRes);
	rotation(wInnerLimit, readUDP[2], readUDP[3]);
	rotation(wOuterLimit, readUDP[2], readUDP[3]);
	rotation(wRaceLine, readUDP[2], readUDP[3]);
	// Calculo distancia
	std::vector<double> percentage = manyDistances(wOuterLimit, wInnerLimit, wRaceLine);
	for (int i = 0; i < percentage.size(); i++){
		std::cout << percentage[i] << std::endl;
	}
	std::vector<cv::Point> racingPoints = getDistances(mask, percentage, pLeft, pRight);
	std::vector<double> racePoly = racingPoly(racingPoints);
	drawRacingLine(mask, racePoly);

	// proyeccion inversa
	cv::Mat retrieval = invProjection(mask, invMatrix, 1);
	addMask(img2, 1, retrieval, 0.3);

	return retrieval;
}
