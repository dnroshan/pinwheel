/*
 * pw-rectangle.h
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

#include "pw-element.h"

G_BEGIN_DECLS

#define PW_TYPE_ELEMENT_RECTANGLE (pw_element_rectangle_get_type ())
G_DECLARE_FINAL_TYPE (PwElementRectangle, pw_element_rectangle, PW, ELEMENT_RECTANGLE, PwElement)

PwElement *pw_element_rectange (gdouble x, gdouble y, gdouble width, gdouble height);

G_END_DECLS
