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

#include "qgittree.h"

#include "qgittreeentry.h"
#include "qgitrepository.h"
#include "qgitoid.h"

#include <QtCore/QFile>

using namespace LibQGit2;

QGitTree::QGitTree(git_tree *tree)
    : m_tree(tree)
{
}

QGitTree::QGitTree( const QGitTree& other )
{
    m_tree = other.m_tree;
}

QGitTree::~QGitTree()
{
}

int QGitTree::lookup(QGitRepository& repository, const QGitOId& id)
{
    return git_tree_lookup(&m_tree, repository.data(), id.data());
}

QGitOId QGitTree::id()
{
    return QGitOId(git_tree_id(m_tree));
}

size_t QGitTree::entryCount()
{
    return git_tree_entrycount(m_tree);
}

QGitTreeEntry QGitTree::entryByName(const QString& fileName)
{
    return QGitTreeEntry(git_tree_entry_byname(m_tree, QFile::encodeName(fileName)));
}

QGitTreeEntry QGitTree::entryByIndex(int idx)
{
    return QGitTreeEntry(git_tree_entry_byindex(m_tree, idx));
}

git_tree* QGitTree::data() const
{
    return m_tree;
}

const git_tree* QGitTree::constData() const
{
    return m_tree;
}
