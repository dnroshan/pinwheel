/*
 * pw-rectangle.c
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

#include "pw-element-rectangle.h"

struct _PwElementRectangle
{
    PwElement parent_instance;

    gdouble width, height;

};

static void pw_element_rectangle_snapshot (PwElement *self, GtkSnapshot *snapshot);

G_DEFINE_FINAL_TYPE (PwElementRectangle, pw_element_rectangle, PW_TYPE_ELEMENT)

static void
pw_element_rectangle_class_init (PwElementRectangleClass *klass)
{
    PwElementClass *element_class = PW_ELEMENT_CLASS (klass);
    element_class->snapshot = pw_element_rectangle_snapshot;
}

static void
pw_element_rectangle_init (PwElementRectangle *self)
{
}

static void
pw_element_rectangle_snapshot (PwElement *self, GtkSnapshot *snapshot)
{
    GdkRGBA color = {1.0, 0.0, 0.0, 1.0};

    gtk_snapshot_append_color (snapshot, &color, &GRAPHENE_RECT_INIT (10, 20, 200, 500));
}

PwElement *
pw_element_rectange (gdouble x, gdouble y, gdouble width, gdouble height)
{
    PwElementRectangle *rectangle;

    rectangle = g_object_new (PW_TYPE_ELEMENT_RECTANGLE, NULL);
    return PW_ELEMENT (rectangle);
}
