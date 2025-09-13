/*
 * pw-element-group.c
 *
 * Copyright 2025 Dilnavas Roshan <dilnavasroshan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "pw-element-group.h"

struct _PwElementGroup
{
    PwElement parent_instance;

    GList *elements;
};

static void pw_element_group_finalize (GObject *self);
static void pw_element_group_snapshot (PwElement   *element,
                                       GtkSnapshot *snapshot);

G_DEFINE_FINAL_TYPE (PwElementGroup, pw_element_group, PW_TYPE_ELEMENT)

static void
pw_element_group_class_init (PwElementGroupClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    PwElementClass *element_class = PW_ELEMENT_CLASS (klass);

    object_class->finalize = pw_element_group_finalize;
    element_class->snapshot = pw_element_group_snapshot;
}

static void
pw_element_group_init (PwElementGroup *self)
{
}

static void
pw_element_group_finalize (GObject *self)
{
    PwElementGroup *element_group = PW_ELEMENT_GROUP (self);

    g_list_free (element_group->elements);

    G_OBJECT_CLASS (pw_element_group_parent_class)->finalize (self);
}

static void
pw_element_group_snapshot (PwElement   *self,
                           GtkSnapshot *snapshot)
{
    PwElement *element;
    PwElementGroup *element_group = PW_ELEMENT_GROUP (self);

    for (GList *list = element_group->elements; list; list = list->next) {
        element = PW_ELEMENT (list->data);
        pw_element_snapshot (element, snapshot);
    }
}

PwElement *
pw_element_group_new (void)
{
    PwElementGroup *element_group;

    element_group = g_object_new (PW_TYPE_ELEMENT_GROUP, NULL);
    return PW_ELEMENT (element_group);
}

void
pw_element_group_add (PwElementGroup *self,
                      PwElement      *element)
{
    g_return_if_fail (PW_IS_ELEMENT_GROUP (self));
    self->elements = g_list_append (self->elements, element);
}

void pw_element_group_remove (PwElementGroup *self,
                              PwElement      *element)
{
    g_return_if_fail (PW_IS_ELEMENT_GROUP (self));
    self->elements = g_list_remove (self->elements, element);
}
