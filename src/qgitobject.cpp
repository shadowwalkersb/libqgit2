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

#include "qgitobject.h"

#include "qgitoid.h"
#include "qgitrepository.h"

using namespace LibQGit2;

QGitObject::QGitObject(git_object *object)
    : d(object, git_object_close)
{
}

QGitObject::QGitObject(const QGitObject& other)
    : d(other.d)
{
}

QGitObject::~QGitObject()
{
}

QGitOId QGitObject::oid() const
{
    return QGitOId(git_object_id(data()));
}

git_otype QGitObject::type() const
{
    return git_object_type(data());
}

QGitRepository QGitObject::owner() const
{
    return QGitRepository(git_object_owner(data()));
}

QString QGitObject::typeToString(git_otype type)
{
    return QString(git_object_type2string(type));
}

git_otype QGitObject::stringToType(const QString& string)
{
    return git_object_string2type(qPrintable(string));
}

int QGitObject::typeIsLoose(git_otype type)
{
    return git_object_typeisloose(type);
}

size_t QGitObject::size(git_otype type)
{
    return git_object__size(type);
}

git_object* QGitObject::data() const
{
    return d.data();
}

const git_object* QGitObject::constData() const
{
    return d.data();
}
