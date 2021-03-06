/***************************************************************************
 *   Copyright (C) 2008-2015 by Ilya Kotov                                 *
 *   forkotov02@ya.ru                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include <QTranslator>
#include <QFile>
#include <QMessageBox>
#include "aacfile.h"
#include "aacmetadatamodel.h"
#include "decoder_aac.h"
#include "decoderaacfactory.h"


// DecoderAACFactory

bool DecoderAACFactory::canDecode(QIODevice *input) const
{
    AACFile aac_file(input, false, false);
    return aac_file.isValid();
}

const DecoderProperties DecoderAACFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("AAC Plugin");
    properties.filters << "*.aac";
    properties.description = tr("AAC Files");
    properties.contentTypes << "audio/aacp" << "audio/aac";
    properties.shortName = "aac";
    properties.hasAbout = true;
    properties.hasSettings = false;
    return properties;
}

Decoder *DecoderAACFactory::create(const QString &, QIODevice *input)
{
    return new DecoderAAC(input);
}

QList<FileInfo *> DecoderAACFactory::createPlayList(const QString &fileName, bool useMetaData, QStringList *)
{
    FileInfo *info = new FileInfo(fileName);

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        AACFile aac_file(&file, useMetaData);
        if (useMetaData)
            info->setMetaData(aac_file.metaData());
        info->setLength(aac_file.length());
    }
    QList <FileInfo*> list;
    list << info;
    return list;
}

MetaDataModel* DecoderAACFactory::createMetaDataModel(const QString &path, QObject *parent)
{
    return new AACMetaDataModel(path, parent);
}

void DecoderAACFactory::showSettings(QWidget *)
{}

void DecoderAACFactory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About AAC Audio Plugin"),
                        tr("Qmmp AAC Audio Plugin")+"\n"+
                        tr("Written by: Ilya Kotov <forkotov02@ya.ru>"));
}

QTranslator *DecoderAACFactory::createTranslator(QObject *parent)
{
    QTranslator *translator = new QTranslator(parent);
    QString locale = Qmmp::systemLanguageID();
    translator->load(QString(":/aac_plugin_") + locale);
    return translator;
}
