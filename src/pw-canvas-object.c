/*
 * pw-canvas-object.c
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
#include "pw-canvas-object.h"


typedef struct
{
    GdkRectangle bounds;
    gboolean active;
    gboolean interactive;
    gboolean visible;

} PwCanvasObjectPrivate;

enum
{
    PROP_VISIBLE = 1,
    PROP_ACTIVE,
    PROP_INTERACTIVE,
    PROP_X,
    PROP_Y,
    PROP_WIDTH,
    PROP_HEIGHT,
    N_PROPS
};

static GParamSpec *pw_canvas_object_properties[N_PROPS] = {NULL, };

G_DEFINE_TYPE_WITH_PRIVATE (PwCanvasObject, pw_canvas_object, G_TYPE_OBJECT)

static void
pw_canvas_object_get_property (GObject    *object,
                               guint       property_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
    PwCanvasObjectPrivate *priv = pw_canvas_object_get_instance_private (PW_CANVAS_OBJECT (object));

    switch (property_id) {
    case PROP_VISIBLE:
        g_value_set_boolean (value, priv->visible);
        break;
    case PROP_ACTIVE:
        g_value_set_boolean (value, priv->active);
        break;
    case PROP_INTERACTIVE:
        g_value_set_boolean (value, priv->interactive);
        break;
    case PROP_X:
        g_value_set_double (value, priv->bounds.x);
        break;
    case PROP_Y:
        g_value_set_double (value, priv->bounds.y);
        break;
    case PROP_WIDTH:
        g_value_set_double (value, priv->bounds.width);
        break;
    case PROP_HEIGHT:
        g_value_set_double (value, priv->bounds.height);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}

static void
pw_canvas_object_set_property (GObject      *object,
                               guint         property_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
    PwCanvasObject *canvas_object = PW_CANVAS_OBJECT (object);

    switch (property_id) {
    case PROP_VISIBLE:
        pw_canvas_object_set_visible (canvas_object, g_value_get_boolean (value));
        break;
    case PROP_ACTIVE:
        pw_canvas_object_set_active (canvas_object, g_value_get_boolean (value));
        break;
    case PROP_INTERACTIVE:
        pw_canvas_object_set_interactive (canvas_object, g_value_get_boolean (value));
        break;
    case PROP_X:
        pw_canvas_object_set_x (canvas_object, g_value_get_double (value));
        break;
    case PROP_Y:
        pw_canvas_object_set_y (canvas_object, g_value_get_double (value));
        break;
    case PROP_WIDTH:
        pw_canvas_object_set_width (canvas_object, g_value_get_double (value));
        break;
    case PROP_HEIGHT:
        pw_canvas_object_set_height (canvas_object, g_value_get_double (value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
        break;
    }
}

static void
pw_canvas_object_class_init (PwCanvasObjectClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->get_property = pw_canvas_object_get_property;
    object_class->set_property = pw_canvas_object_set_property;

    pw_canvas_object_properties[PROP_VISIBLE] =
        g_param_spec_boolean ("visible",
                              NULL, NULL,
                              TRUE,
                              G_PARAM_READWRITE);

    pw_canvas_object_properties[PROP_ACTIVE] =
        g_param_spec_boolean ("active",
                              NULL, NULL,
                              TRUE,
                              G_PARAM_READWRITE);

    pw_canvas_object_properties[PROP_INTERACTIVE] =
        g_param_spec_boolean ("interactive",
                              NULL, NULL,
                              TRUE,
                              G_PARAM_READWRITE);

    pw_canvas_object_properties[PROP_X] =
        g_param_spec_double ("x", NULL, NULL,
                             -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
                             G_PARAM_READWRITE);

    pw_canvas_object_properties[PROP_Y] =
        g_param_spec_double ("y", NULL, NULL,
                             -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
                             G_PARAM_READWRITE);

    pw_canvas_object_properties[PROP_WIDTH] =
        g_param_spec_double ("width", NULL, NULL,
                             -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
                             G_PARAM_READWRITE);

    pw_canvas_object_properties[PROP_HEIGHT] =
        g_param_spec_double ("height", NULL, NULL,
                             -G_MAXDOUBLE, G_MAXDOUBLE, 0.0,
                             G_PARAM_READWRITE);

    g_object_class_install_properties (object_class, N_PROPS, pw_canvas_object_properties);
}

static void
pw_canvas_object_init (PwCanvasObject *self)
{
}

gboolean
pw_canvas_object_is_visible (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), FALSE);
    priv = pw_canvas_object_get_instance_private (self);
    return priv->visible;
}

gboolean
pw_canvas_object_is_active (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), FALSE);
    priv = pw_canvas_object_get_instance_private (self);
    return priv->active;
}

gboolean
pw_canvas_object_is_interactive (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), FALSE);
    priv = pw_canvas_object_get_instance_private (self);
    return priv->interactive;
}

const GdkRectangle *
pw_canvas_object_get_bounds (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), NULL);
    priv = pw_canvas_object_get_instance_private (self);
    return &priv->bounds;
}

gdouble
pw_canvas_object_get_x (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), -1.0);
    priv = pw_canvas_object_get_instance_private (self);
    return priv->bounds.x;
}

gdouble
pw_canvas_object_get_y (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), -1.0);
    priv = pw_canvas_object_get_instance_private (self);
    return priv->bounds.y;
}

gdouble
pw_canvas_object_get_width (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), -1.0);
    priv = pw_canvas_object_get_instance_private (self);
    return priv->bounds.width;
}

gdouble
pw_canvas_object_get_height (PwCanvasObject *self)
{
    PwCanvasObjectPrivate *priv;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), -1.0);
    priv = pw_canvas_object_get_instance_private (self);
    return priv->bounds.height;
}

void
pw_canvas_object_set_visible (PwCanvasObject *self,
                              gboolean        value)
{
    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->visible = value;
    g_object_notify_by_pspec (G_OBJECT (self), pw_canvas_object_properties[PROP_VISIBLE]);
}

void
pw_canvas_object_set_active (PwCanvasObject *self,
                             gboolean        value)
{
    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->active = value;
    g_object_notify_by_pspec (G_OBJECT (self), pw_canvas_object_properties[PROP_ACTIVE]);
}

void
pw_canvas_object_set_interactive (PwCanvasObject *self,
                                  gboolean        value)
{
    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->interactive = value;
    g_object_notify_by_pspec (G_OBJECT (self), pw_canvas_object_properties[PROP_INTERACTIVE]);
}

void
pw_canvas_object_set_bounds (PwCanvasObject     *self,
                             const GdkRectangle *bounds)
{

    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->bounds = *bounds;
}

void
pw_canvas_object_set_x (PwCanvasObject *self,
                        gdouble         value)
{
    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->bounds.x = value;
}

void
pw_canvas_object_set_y (PwCanvasObject *self,
                        gdouble         value)
{
    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->bounds.y = value;
}

void
pw_canvas_object_set_width (PwCanvasObject *self,
                            gdouble         value)
{
    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->bounds.width = value;
}

void
pw_canvas_object_set_height (PwCanvasObject *self,
                             gdouble         value)
{
    PwCanvasObjectPrivate *priv;

    g_return_if_fail (PW_IS_CANVAS_OBJECT (self));
    priv = pw_canvas_object_get_instance_private (self);
    priv->bounds.height = value;
}

gdouble
pw_canvas_object_hit (PwCanvasObject *self,
                      gdouble         x,
                      gdouble         y)
{
    PwCanvasObjectClass *klass;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), -1.0);
    klass = PW_CANVAS_OBJECT_GET_CLASS (self);
    g_return_val_if_fail (klass, -1.0);
    return klass->hit (self, x, y);
}

PwCanvasObject *
pw_canvas_object_pick (PwCanvasObject *self,
                       gdouble         x,
                       gdouble         y)
{
    PwCanvasObjectClass *klass;

    g_return_val_if_fail (PW_IS_CANVAS_OBJECT (self), NULL);
    klass = PW_CANVAS_OBJECT_GET_CLASS (self);
    g_return_val_if_fail (klass, NULL);
    return klass->pick (self, x, y);
}

