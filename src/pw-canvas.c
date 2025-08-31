/*
 * pw-canvas.c
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

#include "config.h"
#include "pw-canvas.h"

struct _PwCanvas
{
    GtkWidget parent_instance;
};

G_DEFINE_FINAL_TYPE (PwCanvas, pw_canvas, GTK_TYPE_WIDGET)

static void
pw_canvas_class_init (PwCanvasClass *klass)
{
}

static void
pw_canvas_init (PwCanvas *self)
{
}

GtkWidget *
pw_canvas_new (void)
{
    return g_object_new (PW_TYPE_CANVAS, NULL);
}

G_DEFINE_TYPE (PwCanvasObject, pw_canvas_object, G_TYPE_OBJECT)

static void
pw_canvas_object_class_init (PwCanvasObjectClass *klass)
{
}

static void
pw_canvas_object_init (PwCanvasObject *self)
{
}
