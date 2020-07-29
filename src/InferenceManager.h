#ifndef INFERENCEMANAGER_H
#define INFERENCEMANAGER_H

#include <QObject>
#include <QThread>
#include "camera/AsyncCameraCapture.h"
#include "vcam/AbstractVCamInterface.h"
#include "InferenceWorker.h"

class InferenceManager : public QObject {
Q_OBJECT
    Q_PROPERTY(QString rootFolder READ rootFolder)
    Q_PROPERTY(AsyncCameraCapture *camera READ camera WRITE setCamera)
    Q_PROPERTY(AbstractVCamInterface *virtualCamera READ virtualCamera WRITE setVirtualCamera)
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface)
    Q_PROPERTY(bool mirror READ mirror WRITE setMirror)
    Q_PROPERTY(QString avatarPath READ avatarPath WRITE setAvatarPath)

public:
    ~InferenceManager() override;

    QString rootFolder();

    AsyncCameraCapture *camera();

    void setCamera(AsyncCameraCapture *camera);

    AbstractVCamInterface *virtualCamera();

    void setVirtualCamera(AbstractVCamInterface *virtualCamera);

    QAbstractVideoSurface *videoSurface();

    void setVideoSurface(QAbstractVideoSurface *videoSurface);

    bool mirror() const;

    void setMirror(bool mirror);

    QString avatarPath() const;

    void setAvatarPath(const QString &avatarFilename);

    void startWorkerIfReady();

public Q_SLOTS:

    void presentFrame(const QImage &generatedFrame);

private:
    const QString ROOT_FOLDER = QDir::homePath();

    AsyncCameraCapture *m_camera = nullptr;
    AbstractVCamInterface *m_virtualCamera = nullptr;
    QAbstractVideoSurface *m_videoSurface = nullptr;
    bool m_mirror = false;
    QString m_avatarPath;
    QScopedPointer<InferenceWorker> worker;
};


#endif //INFERENCEMANAGER_H
