/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "qgitrepository.h"

#include <QtCore/QFile>

using namespace LibQGit2;

QGitRepository::QGitRepository(const QString& path, unsigned isBare)
{
    git_repository_init(&m_repository, QFile::encodeName(path), isBare);
}

QGitRepository::QGitRepository(git_repository *repository)
    : m_repository(repository)
{
}

QGitRepository::QGitRepository( const QGitRepository& other )
{
    m_repository = other.m_repository;
}

QGitRepository::~QGitRepository()
{
    git_repository_free(m_repository);
}

int QGitRepository::open(const QString& path)
{
    return git_repository_open(&m_repository, QFile::encodeName(path));
}

int QGitRepository::open2(const QString& gitDir,
                      const QString& gitObjectDirectory,
                      const QString& gitIndexFile,
                      const QString& gitWorkTree)
{
    return git_repository_open2(&m_repository,
                                QFile::encodeName(gitDir),
                                QFile::encodeName(gitObjectDirectory),
                                QFile::encodeName(gitIndexFile),
                                QFile::encodeName(gitWorkTree));
}


int QGitRepository::open3(const QString& gitDir,
                      QGitDatabase *objectDatabase,
                      const QString& gitIndexFile,
                      const QString& gitWorkTree)
{
    return git_repository_open3(&m_repository,
                                QFile::encodeName(gitDir),
                                objectDatabase->data(),
                                QFile::encodeName(gitIndexFile),
                                QFile::encodeName(gitWorkTree));
}

QGitRef QGitRepository::lookup(const QString& name)
{
    git_reference *ref;
    git_reference_lookup(&ref, data(), QFile::encodeName(name));
    return QGitRef(ref);
}

QGitRef QGitRepository::createRef(const QString& name, const QGitOId& oid, bool force)
{
    git_reference *ref;
    git_reference_create_oid(&ref, data(), QFile::encodeName(name), oid.data(), force);
    return QGitRef(ref);
}

QGitRef QGitRepository::createSymbolicRef(const QString& name, const QString& target, bool force)
{
    git_reference *ref;
    git_reference_create_symbolic(&ref, data(), QFile::encodeName(name), QFile::encodeName(target), force);
    return QGitRef(ref);
}

QGitDatabase* QGitRepository::database() const
{
    QGitDatabase *database = new QGitDatabase(git_repository_database(m_repository));
    return database;
}

int QGitRepository::index(QGitIndex& index) const
{
    git_index *idx;
    int ret = git_repository_index(&idx, m_repository);
    index.reset(idx);
    return ret;
}

git_repository* QGitRepository::data() const
{
    return m_repository;
}

const git_repository* QGitRepository::constData() const
{
    return m_repository;
}

