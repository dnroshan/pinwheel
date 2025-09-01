/*
 * pw-canvas.h
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

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PW_TYPE_CANVAS (pw_canvas_get_type ())
G_DECLARE_FINAL_TYPE (PwCanvas, pw_canvas, PW, CANVAS, GtkWidget)

#define PW_TYPE_CANVAS_OBJECT (pw_canvas_object_get_type ())
G_DECLARE_DERIVABLE_TYPE (PwCanvasObject, pw_canvas_object, PW, CANVAS_OBJECT, GObject)

struct _PwCanvasObjectClass
{
    GObjectClass parent_class;

    /* rendering */
    void (*snapshot) (PwCanvasObject *self,
                      GtkSnapshot    *snapshot);

    /* event handlers */

    gboolean (*mouse_down)  (PwCanvasObject *self,
                             gdouble         x,
                             gdouble         y,
                             gint            button,
                             GdkModifierType modifiers);
    gboolean (*mouse_up)    (PwCanvasObject *self,
                             gdouble         x,
                             gdouble         y,
                             gint            button,
                             GdkModifierType modifiers);
    gboolean (*mouse_move)  (PwCanvasObject *self,
                             gdouble         x,
                             gdouble         y,
                             gint            button,
                             GdkModifierType modifiers);
    gboolean (*enter)       (PwCanvasObject *self);
    gboolean (*leave)       (PwCanvasObject *self);
    gboolean (*key_press)   (PwCanvasObject *self,
                             gint            key);
    gboolean (*key_release) (PwCanvasObject *self,
                             gint            key);

    /* hit detection */
    gdouble         (*hit)  (PwCanvasObject *self,
                             gdouble x,
                             gdouble y);
    PwCanvasObject *(*pick) (PwCanvasObject *self,
                             gdouble x,
                             gdouble y);
};

GtkWidget *pw_canvas_new (void);

gboolean pw_canvas_object_is_visible     (PwCanvasObject *self);
gboolean pw_canvas_object_is_active      (PwCanvasObject *self);
gboolean pw_canvas_object_is_interactive (PwCanvasObject *self);

const GdkRectangle *pw_canvas_object_get_bounds (PwCanvasObject *self);
gdouble pw_canvas_object_get_x           (PwCanvasObject *self);
gdouble pw_canvas_object_get_y           (PwCanvasObject *self);
gdouble pw_canvas_object_get_width       (PwCanvasObject *self);
gdouble pw_canvas_object_get_height      (PwCanvasObject *self);

void pw_canvas_object_set_visible     (PwCanvasObject *self, gboolean value);
void pw_canvas_object_set_active      (PwCanvasObject *self, gboolean value);
void pw_canvas_object_set_interactive (PwCanvasObject *self, gboolean value);

void pw_canvas_object_set_bounds (PwCanvasObject *self, const GdkRectangle *bounds);
void pw_canvas_object_set_x      (PwCanvasObject *self, gdouble value);
void pw_canvas_object_set_y      (PwCanvasObject *self, gdouble value);
void pw_canvas_object_set_width  (PwCanvasObject *self, gdouble value);
void pw_canvas_object_set_height (PwCanvasObject *self, gdouble value);

gdouble         pw_canvas_object_hit  (PwCanvasObject *self, gdouble x, gdouble y);
PwCanvasObject *pw_canvas_object_pick (PwCanvasObject *self, gdouble x, gdouble y);

G_END_DECLS
