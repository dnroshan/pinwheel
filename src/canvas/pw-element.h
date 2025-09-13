/*
 * pw-element.h
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
#include "canvas/pw-element.h"

G_BEGIN_DECLS

#define PW_TYPE_ELEMENT (pw_element_get_type ())
G_DECLARE_DERIVABLE_TYPE (PwElement, pw_element, PW, ELEMENT, GObject)

struct _PwElementClass
{
    GObjectClass parent_class;

    void (*snapshot) (PwElement *self, GtkSnapshot *snapshot);
};

gdouble pw_element_get_x (PwElement *self);
gdouble pw_element_get_y (PwElement *self);

void  pw_element_set_pos (PwElement *self,
                          gdouble    x,
                          gdouble    y);
void  pw_element_set_x   (PwElement *self,
                          gdouble    value);
void  pw_element_set_y   (PwElement *self,
                          gdouble    value);

void pw_element_snapshot (PwElement *self, GtkSnapshot *snapshot);

G_END_DECLS
