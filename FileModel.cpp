#include "FileModel.h"

FileModel::FileModel(QObject *a_parent)
    :QFileSystemModel(a_parent),
      m_selectionModel(new QItemSelectionModel(this)),
      m_emptyFile(new FileInfo(this))
{

    // =============================== Signals ===============================

    connect(this, &QFileSystemModel::rootPathChanged, [this](const QString &newPath){
        Q_UNUSED(newPath)

        emit rootPathChanged();
    });

    connect(m_selectionModel, &QItemSelectionModel::currentChanged,[this](const QModelIndex &current, const QModelIndex &previous) {
        Q_UNUSED(current)
        Q_UNUSED(previous)

        emit selectedFileChanged();
    });


    // =========================== rows Inserted ===========================

    connect(this, &QAbstractItemModel::rowsInserted,
                 [this](const QModelIndex &a_parent, int a_first, int a_last)
    {

        for (int i = a_first; i <= a_last; i++) {
            auto curIndex = index(i, 0, a_parent);

            if (isDir(curIndex))
                continue;

            //Choose .avi and .mp3 only
            QString fileSuffix = fileInfo(curIndex).suffix();
            if (fileSuffix.compare("avi", Qt::CaseInsensitive) &&
                fileSuffix.compare("mp3", Qt::CaseInsensitive))
                continue;

            QString fPath (filePath(curIndex));
            const char *fPathCStr = fPath.toStdString().c_str();

            //Open input
            int ret;
            if ((ret = avformat_open_input(&m_fmtCtx, fPathCStr, nullptr, nullptr)) < 0) {
                qWarning() << "File not found" <<  fPathCStr << ret;
                avformat_close_input(&m_fmtCtx);
                continue;
            }

            //Find stream input
            if ((ret = avformat_find_stream_info(m_fmtCtx, nullptr))) {
                qWarning() << "Cannot find stream information: "<<fPathCStr<<ret;
                avformat_close_input(&m_fmtCtx);
                continue;
            }

            FileInfo *file = new FileInfo(m_fmtCtx, this);
            m_files.insert(fPath, file);

            avformat_close_input(&m_fmtCtx);

        }
    });

    // =========================== rows Removed ===========================

    connect(this, &QAbstractItemModel::rowsRemoved,
                 [this](const QModelIndex &a_parent, int a_first, int a_last)
    {

        for (int i = a_first; i <= a_last; i++) {
            auto curIndex = index(i, 0, a_parent);

            if (isDir(curIndex))
                continue;

            QString fPath (filePath(curIndex));

            if (m_files.contains(fPath)) {
                delete m_files[fPath];
                m_files.remove(fPath);
            }

        }
    });
}

FileInfo *FileModel::selectedFile() const
{
    auto selectedIndex = m_selectionModel->currentIndex();
    QString selectedPath = filePath(selectedIndex);

    if (selectedIndex.isValid() && !isDir(selectedIndex) && m_files.contains(selectedPath))
        return m_files.value(selectedPath);
    else
        return m_emptyFile;
}

QModelIndex FileModel::rootIndex()
{
    return index(rootPath());
}
