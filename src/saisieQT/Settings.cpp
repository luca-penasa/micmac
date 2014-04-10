#include "Settings.h"

cSettingsDlg::cSettingsDlg(QWidget *parent, cParameters *params) : QDialog(parent), Ui::settingsDialog()
{
    setupUi(this);

    setWindowFlags(Qt::Tool/*Qt::Dialog | Qt::WindowStaysOnTopHint*/);

    _parameters = params;
    _oldParameters = *params;

    refresh();

    setUpdatesEnabled(true);
}

cSettingsDlg::~cSettingsDlg()
{}

void cSettingsDlg::setParameters(cParameters &params)
{
    if (!_parameters)
        _parameters = new cParameters();

     _parameters = &params;
}

void cSettingsDlg::on_NBF_x_spinBox_valueChanged(int value)
{
    int y = _parameters->getNbFen().y();
    _parameters->setNbFen(QPoint(value, y));
}

void cSettingsDlg::on_NBF_y_spinBox_valueChanged(int value)
{
    int x = _parameters->getNbFen().x();
    _parameters->setNbFen(QPoint(x, value));
}

void cSettingsDlg::on_WindowWidth_spinBox_valueChanged(int value)
{
    int y = _parameters->getSzFen().height();
    _parameters->setSzFen(QSize(value, y));
}

void cSettingsDlg::on_WindowHeight_spinBox_valueChanged(int value)
{
    int x = _parameters->getSzFen().width();
    _parameters->setSzFen(QSize(x, value));
}

void cSettingsDlg::on_LineThickness_doubleSpinBox_valueChanged(double val)
{
    _parameters->setLineThickness(val);

    emit lineThicknessChanged(val);
}

void cSettingsDlg::on_PointDiameter_doubleSpinBox_valueChanged(double val)
{
    _parameters->setPointDiameter(val);

    emit pointDiameterChanged(val);
}

void cSettingsDlg::on_GammaDoubleSpinBox_valueChanged(double val)
{
    _parameters->setGamma(val);

    emit gammaChanged((float)val);
}

void cSettingsDlg::on_zoomWin_spinBox_valueChanged(int val)
{
    _parameters->setZoomWindowValue(val);

    emit zoomWindowChanged((float)val);
}

void cSettingsDlg::on_RadiusSpinBox_valueChanged(int val)
{
    _parameters->setSelectionRadius(val);

    emit selectionRadiusChanged(val);
}

void cSettingsDlg::on_shiftStep_doubleSpinBox_valueChanged(double val)
{
    _parameters->setShiftStep(val);

    emit shiftStepChanged(val);
}

void cSettingsDlg::on_PrefixTextEdit_textChanged(QString val)
{
    _parameters->setDefPtName(val);

    emit prefixTextEdit(val);
}

void cSettingsDlg::enableMarginSpinBox(bool show)
{
    doubleSpinBoxSz->setEnabled(show);
    label_Margin->setEnabled(show);
    label_pixels->setEnabled(show);
}

void cSettingsDlg::on_radioButtonStd_toggled(bool checked)
{
    if (checked)
    {
        _parameters->setPtCreationMode(eNSM_Pts);
        _parameters->setPtCreationWindowSize(-1);

        enableMarginSpinBox(false);
    }
}

void cSettingsDlg::on_radioButtonMin_toggled(bool checked)
{
    if (checked)
    {
        _parameters->setPtCreationMode(eNSM_MinLoc);
        enableMarginSpinBox(!radioButtonStd->isChecked());
    }
}

void cSettingsDlg::on_radioButtonMax_toggled(bool checked)
{
    if (checked)
    {
        _parameters->setPtCreationMode(eNSM_MaxLoc);
        enableMarginSpinBox(!radioButtonStd->isChecked());
    }
}

void cSettingsDlg::on_doubleSpinBoxSz_valueChanged(double val)
{
    _parameters->setPtCreationWindowSize(val);
}

void  cSettingsDlg::on_okButton_clicked()
{
    on_applyButton_clicked();

    _parameters->write();

    accept();
}

void cSettingsDlg::on_cancelButton_clicked()
{
    _parameters->read();

    refresh();

    reject();
}

void cSettingsDlg::on_applyButton_clicked()
{
    //TODO: a corriger
    emit nbFenChanged(_parameters->getNbFen() != _oldParameters.getNbFen());
}

void cSettingsDlg::on_resetButton_clicked()
{
    _parameters->read();

    refresh();
}

void cSettingsDlg::refresh()
{
    NBF_x_spinBox->setValue(_parameters->getNbFen().x());
    NBF_y_spinBox->setValue(_parameters->getNbFen().y());

    WindowWidth_spinBox->setValue( _parameters->getSzFen().width());
    WindowHeight_spinBox->setValue(_parameters->getSzFen().height());

    LineThickness_doubleSpinBox->setValue(_parameters->getLineThickness());
    PointDiameter_doubleSpinBox->setValue(_parameters->getPointDiameter());
    GammaDoubleSpinBox->setValue(_parameters->getGamma());

    zoomWin_spinBox->setValue(_parameters->getZoomWindowValue());
    PrefixTextEdit->setText(_parameters->getDefPtName());
    RadiusSpinBox->setValue(_parameters->getSelectionRadius());

    switch (_parameters->getPtCreationMode())
    {
        case eNSM_Pts:
        {
            radioButtonStd->setChecked(true);
            enableMarginSpinBox(false);
            break;
        }
        case eNSM_MinLoc:
        {
            radioButtonMin->setChecked(true);
            enableMarginSpinBox();
            break;
        }
        case eNSM_MaxLoc:
        {
            radioButtonMax->setChecked(true);
            enableMarginSpinBox();
            break;
        }
        case eNSM_GeoCube:
        case eNSM_Plaquette:
        case eNSM_NonValue:
            break;
    }

    doubleSpinBoxSz->setValue(_parameters->getPtCreationWindowSize());

    update();
}

cParameters::cParameters():
    _fullScreen(false),
    _position(QPoint(100,100)),
    _nbFen(QPoint(1,1)),
    _szFen(QSize(800,600)),
    _lineThickness(2.f),
    _pointDiameter(2.f),
    _gamma(1.f),
    _zoomWindow(3.f),
    _ptName(QString("100")),
    _postFix(QString("_mask")),
    _radius(50),
    _eType(eNSM_Pts),
    _sz(5.f)
{}

cParameters& cParameters::operator =(const cParameters &params)
{
    _fullScreen     = params._fullScreen;
    _position       = params._position;
    _nbFen          = params._nbFen;
    _szFen          = params._szFen;

    _lineThickness  = params._lineThickness;
    _pointDiameter  = params._pointDiameter;
    _gamma          = params._gamma;

    _zoomWindow     = params._zoomWindow;
    _ptName         = params._ptName;
    _postFix        = params._postFix;
    _radius         = params._radius;
    _shiftStep      = params._shiftStep;

    _eType          = params._eType;
    _sz             = params._sz;

    return *this;
}

bool cParameters::operator!=(cParameters &p)
{
    if ((p._fullScreen != _fullScreen) ||
            (p._position != _position) ||
            (p._nbFen    != _nbFen)    ||
            (p._szFen    != _szFen)    ||
            (p._lineThickness  != _lineThickness) ||
            (p._pointDiameter  != _pointDiameter) ||
            (p._gamma          != _gamma) ||
            (p._zoomWindow     != _zoomWindow) ||
            (p._ptName         != _ptName)  ||
            (p._postFix        != _postFix) ||
            (p._radius         != _radius)  ||
            (p._shiftStep      != _shiftStep)  ||
            (p._eType          != _eType)   ||
            (p._sz             != _sz)) return true;
    return  false;
}

float zoomClip(float val)
{
    float zoom = val;

    if (zoom < GL_MIN_ZOOM) zoom = GL_MAX_ZOOM;
    else if (zoom > GL_MAX_ZOOM) zoom = GL_MAX_ZOOM;

    return zoom;
}

void cParameters::read()
{
     QSettings settings(QApplication::organizationName(), QApplication::applicationName());

#ifdef _DEBUG
    std::cout << "settings location: " << settings.fileName().toStdString().c_str() << std::endl;
#endif

     settings.beginGroup("MainWindow");
     setNbFen(          settings.value("NbFen", QPoint(1, 1)    ).toPoint());
     setFullScreen(     settings.value("openInFullScreen", false).toBool());
     setPosition(       settings.value("pos",   QPoint(200, 200)).toPoint());
     setSzFen(          settings.value("size",  QSize(800, 600) ).toSize());
     settings.endGroup();

     settings.beginGroup("Drawing settings");
     setLineThickness(  settings.value("linethickness", 2.f     ).toFloat());
     setPointDiameter(  settings.value("pointdiameter",2.f      ).toFloat());
     setGamma(          settings.value("gamma",1.f              ).toFloat());
     settings.endGroup();

     settings.beginGroup("Misc");
     setDefPtName(      settings.value("defPtName", QString("100")).toString());
     setPostFix(        settings.value("postFix",   QString("_mask")).toString());
     setZoomWindowValue(zoomClip( settings.value("zoom", 3.0).toFloat()));
     setSelectionRadius( settings.value("radius",50).toInt());
     setShiftStep(settings.value("shiftStep", 0.5f).toFloat());
     settings.endGroup();

     settings.beginGroup("Point creation");
     setPtCreationMode( static_cast<eTypePts> (settings.value("Mode", eNSM_Pts).toInt()));
     setPtCreationWindowSize( settings.value("WindowSize",3.f).toFloat());
     settings.endGroup();
}

void cParameters::write()
{
     QSettings settings(QApplication::organizationName(), QApplication::applicationName());

     settings.beginGroup("MainWindow");
     settings.setValue("size",              _szFen      );
     settings.setValue("pos",               _position   );
     settings.setValue("NbFen",             _nbFen      );
     settings.setValue("openInFullScreen",  _fullScreen );
     settings.endGroup();

     settings.beginGroup("Drawing settings");
     settings.setValue("linethickness", QString::number(_lineThickness,'f',1)  );
     settings.setValue("pointdiameter", QString::number(_pointDiameter,'f',1)  );
     settings.setValue("gamma",         QString::number(_gamma        ,'f',1)  );
     settings.endGroup();

     settings.beginGroup("Misc");
     settings.setValue("defPtName", _ptName    );
     settings.setValue("postFix",   _postFix   );
     settings.setValue("radius",    _radius    );
     settings.setValue("shiftStep", _shiftStep );
     settings.setValue("zoom",      QString::number(zoomClip(_zoomWindow),'f',2)    );
     settings.endGroup();

     settings.beginGroup("Point creation");
     settings.setValue("Mode", _eType   );
     settings.setValue("WindowSize", _sz);
     settings.endGroup();
}
