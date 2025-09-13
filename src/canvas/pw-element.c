/*
 * pw-element.c
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

#include "pw-element.h"

typedef struct
{
    PwElement *parent;

    gdouble x, y;

    graphene_matrix_t transform;
    graphene_matrix_t parent_transform;
} PwElementPrivate;

static void compute_parent_transform (PwElementPrivate *priv);

G_DEFINE_TYPE_WITH_PRIVATE (PwElement, pw_element, G_TYPE_OBJECT)

static void
pw_element_class_init (PwElementClass *klass)
{
}

static void
pw_element_init (PwElement *self)
{
    PwElementPrivate *priv = pw_element_get_instance_private (self);

    graphene_matrix_init_identity (&priv->transform);
    graphene_matrix_init_identity (&priv->parent_transform);
}

void
pw_element_snapshot (PwElement *self, GtkSnapshot *snapshot)
{
    PwElementClass *klass;

    g_return_if_fail (PW_IS_ELEMENT (self));

    klass = PW_ELEMENT_GET_CLASS (self);
    g_assert (klass->snapshot);
    klass->snapshot (self, snapshot);
}

void
pw_element_set_pos (PwElement *self,
                    gdouble    x,
                    gdouble    y)
{
    PwElementPrivate *priv;

    g_return_if_fail (PW_IS_ELEMENT (self));
    priv = pw_element_get_instance_private (self);
    priv->x = x;
    priv->y = y;
    compute_parent_transform (priv);
}

void
pw_element_set_x (PwElement *self,
                  gdouble    value)
{
    PwElementPrivate *priv;

    g_return_if_fail (PW_IS_ELEMENT (self));
    priv = pw_element_get_instance_private (self);
    priv->x = value;
    compute_parent_transform (priv);
}

void  pw_element_set_y (PwElement *self,
                        gdouble    value)
{
    PwElementPrivate *priv;

    g_return_if_fail (PW_IS_ELEMENT (self));
    priv = pw_element_get_instance_private (self);
    priv->y = value;
    compute_parent_transform (priv);
}

gdouble
pw_element_get_x (PwElement *self)
{
    PwElementPrivate *priv;

    g_return_val_if_fail (PW_IS_ELEMENT (self), 0.0);
    priv = pw_element_get_instance_private (self);
    return priv->x;
}

gdouble
pw_element_get_y (PwElement *self)
{
    PwElementPrivate *priv;

    g_return_val_if_fail (PW_IS_ELEMENT (self), 0.0);
    priv = pw_element_get_instance_private (self);
    return priv->y;
}

static void
compute_parent_transform (PwElementPrivate *priv)
{
    graphene_point3d_t point = {priv->x, priv->y, 0};
    graphene_matrix_translate (&priv->parent_transform, &point);
}
