#ifndef OPENGLSIMULATION_H
#define OPENGLSIMULATION_H

#include <vector>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>

#include "geometryengine.h"
#include "observer.h"

class OpenGLSimulation : public QOpenGLWidget, protected QOpenGLFunctions, public Observer
{
    Q_OBJECT
public:
    explicit OpenGLSimulation(QWidget *parent = 0);
    ~OpenGLSimulation();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void updateObserver(QRectF minMaxAngles, QPointF angles, LaserMode laserMode, std::vector<QPointF> calibrationAngles);


protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;

    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;


private:
    void initShaders();
    void initTextures();

    void recalcCameraMat();
    void paintCube(QMatrix4x4 worldMat);
    void paintPlane(QMatrix4x4 worldMat);

private:
    QBasicTimer timer;

    QOpenGLShaderProgram program;
    QOpenGLTexture *servoTexture;

    QOpenGLTexture *grassTexture;
    QOpenGLTexture *laserTexture;
    QOpenGLTexture *greenLaserTexture;

    GeometryEngine *cubeGeometry;
    GeometryEngine *planeGeometry;

    QMatrix4x4 projectionMat;

    double rotationAngle;
    double nickAngle;

    QPoint lastPos;

    QMatrix4x4 cameraMat;

    QVector3D servoSize;
    QVector3D servoSpindle;
    QVector3D servoSpindleSize;
    QVector3D servo2Contact;
    QVector3D laserSize;


    double cameraDistance;

    LaserMode laserMode;

    QPointF actualAngle;
    QPointF actualAngleSpeed;


    QPointF targetAngle;

    std::vector<QPointF> calibrationAngles;

signals:

public slots:

};

#endif // OPENGLSIMULATION_H
