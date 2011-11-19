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

#include "qgitindex.h"
#include "qgitindexentry.h"

#include "qgitrepository.h"

#include <QtCore/QFile>

using namespace LibQGit2;

QGitIndex::QGitIndex(const QString& indexPath)
{
    git_index_open(&m_index, QFile::encodeName(indexPath));
}

QGitIndex::QGitIndex(const QGitRepository& repository)
{
    git_repository_index(&m_index, repository.data());
}

QGitIndex::QGitIndex( const QGitIndex& other )
{
    m_index = other.m_index;
}

void QGitIndex::reset(git_index *data)
{
    m_index = data;
}

QGitIndex::~QGitIndex()
{
    git_index_free(m_index);
}

void QGitIndex::clear()
{
    return git_index_clear(m_index);
}

int QGitIndex::read() const
{
    return git_index_read(m_index);
}

int QGitIndex::write()
{
    return git_index_write(m_index);
}

int QGitIndex::find(const QString& path)
{
    return git_index_find(m_index, QFile::encodeName(path));
}

int QGitIndex::add(const QString& path, int stage)
{
    return git_index_add(m_index, QFile::encodeName(path), stage);
}

int QGitIndex::remove(int position)
{
    return git_index_remove(m_index, position);
}

int QGitIndex::insert(const QGitIndexEntry &source_entry)
{
    return git_index_append2(m_index, source_entry.data());
}

QGitIndexEntry QGitIndex::get(int n) const
{
    return QGitIndexEntry(git_index_get(m_index, n));
}

unsigned int QGitIndex::entryCount() const
{
    return git_index_entrycount(m_index);
}

git_index* QGitIndex::data() const
{
    return m_index;
}

const git_index* QGitIndex::constData() const
{
    return m_index;
}
