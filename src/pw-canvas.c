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

static void pw_canvas_get_property (GObject   *object,
                                    guint      property_id,
                                    GValue     *value,
                                    GParamSpec *pspec);

static void pw_canvas_set_property (GObject      *object,
                                    guint         property_id,
                                    const GValue *value,
                                    GParamSpec   *pspec);

static void pw_canvas_dispose      (GObject *self);
static void pw_canvas_finalize     (GObject *self);

static GtkSizeRequestMode pw_canvas_get_request_mode (GtkWidget *self);

static void pw_canvas_measure       (GtkWidget      *widget,
                                     GtkOrientation  orientation,
                                     gint            for_size,
                                     gint           *minimum,
                                     gint           *natural,
                                     gint           *minimum_baseline,
                                     gint           *natural_baseline);

static void pw_canvas_size_allocate (GtkWidget   *widget,
                                     gint         width,
                                     gint         height,
                                     gint         baseline);

static void pw_canvas_snapshot      (GtkWidget   *self,
                                     GtkSnapshot *snapshot);

static void pw_canvas_button_press_cb   (PwCanvas *self,
                                         gint      n_press,
                                         gdouble   x,
                                         gdouble   y,
                                         gpointer  user_data);

static void pw_canvas_button_release_cb (PwCanvas *self,
                                         gint      n_press,
                                         gdouble   x,
                                         gdouble   y,
                                         gpointer  user_data);

static void pw_canvas_enter_cb  (PwCanvas *self,
                                 gdouble   x,
                                 gdouble   y,
                                 gpointer  user_data);

static void pw_canvas_leave_cb  (PwCanvas *self,
                                 gdouble   x,
                                 gdouble   y,
                                 gpointer  user_data);

static void pw_canvas_motion_cb (PwCanvas *self,
                                 gdouble   x,
                                 gdouble   y,
                                 gpointer  user_data);

static gboolean pw_canvas_key_pressed (PwCanvas*       self,
                                       guint           keyval,
                                       guint           keycode,
                                       GdkModifierType state,
                                       gpointer        user_data);

static gboolean pw_canvas_key_released (PwCanvas*      self,
                                       guint           keyval,
                                       guint           keycode,
                                       GdkModifierType state,
                                       gpointer        user_data);

G_DEFINE_FINAL_TYPE (PwCanvas, pw_canvas, GTK_TYPE_WIDGET)

static void
pw_canvas_class_init (PwCanvasClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    object_class->get_property = pw_canvas_get_property;
    object_class->set_property = pw_canvas_set_property;
    object_class->dispose      = pw_canvas_dispose;
    object_class->finalize     = pw_canvas_finalize;

    widget_class->measure       = pw_canvas_measure;
    widget_class->get_request_mode = pw_canvas_get_request_mode;
    widget_class->size_allocate = pw_canvas_size_allocate;
    widget_class->snapshot      = pw_canvas_snapshot;
}

static void
pw_canvas_init (PwCanvas *self)
{
    GtkGesture *gesture_click;
    GtkEventController *motion_controller;
    GtkEventController *key_controller;

    gesture_click = gtk_gesture_click_new ();
    gtk_gesture_single_set_button (GTK_GESTURE_SINGLE (gesture_click), 0);
    g_signal_connect_swapped (gesture_click, "pressed", G_CALLBACK (pw_canvas_button_press_cb), self);
    g_signal_connect_swapped (gesture_click, "released", G_CALLBACK (pw_canvas_button_release_cb), self);
    gtk_widget_add_controller (GTK_WIDGET (self), GTK_EVENT_CONTROLLER (gesture_click));

    motion_controller = gtk_event_controller_motion_new ();
    g_signal_connect_swapped (motion_controller, "enter", G_CALLBACK (pw_canvas_enter_cb), self);
    g_signal_connect_swapped (motion_controller, "leave", G_CALLBACK (pw_canvas_leave_cb), self);
    g_signal_connect_swapped (motion_controller, "motion", G_CALLBACK (pw_canvas_motion_cb), self);
    gtk_widget_add_controller (GTK_WIDGET (self), motion_controller);

    key_controller = gtk_event_controller_key_new ();
    g_signal_connect_swapped (key_controller, "key-pressed", G_CALLBACK (pw_canvas_key_pressed), self);
    g_signal_connect_swapped (key_controller, "key-released", G_CALLBACK (pw_canvas_key_released), self);
    gtk_widget_add_controller (GTK_WIDGET (self), key_controller);

    gtk_widget_set_focusable (GTK_WIDGET (self), TRUE);
}

static void
pw_canvas_get_property (GObject    *object,
                        guint       property_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
}

static void
pw_canvas_set_property (GObject      *object,
                        guint         property_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
}

static void
pw_canvas_dispose (GObject *self)
{
    G_OBJECT_CLASS (pw_canvas_parent_class)->dispose (self);
}

static void
pw_canvas_finalize (GObject *self)
{
    G_OBJECT_CLASS (pw_canvas_parent_class)->finalize (self);
}

static GtkSizeRequestMode
pw_canvas_get_request_mode (GtkWidget *self)
{
    return GTK_SIZE_REQUEST_HEIGHT_FOR_WIDTH;
}

static void
pw_canvas_measure (GtkWidget      *widget,
                   GtkOrientation  orientation,
                   gint            for_size,
                   gint           *minimum,
                   gint           *natural,
                   gint           *minimum_baseline,
                   gint           *natural_baseline)
{
}

static void
pw_canvas_size_allocate (GtkWidget *widget,
                         gint       width,
                         gint       height,
                         gint       baseline)
{
}

static void
pw_canvas_snapshot (GtkWidget   *self,
                    GtkSnapshot *snapshot)
{
}

static void
pw_canvas_button_press_cb (PwCanvas *self,
                           gint      n_press,
                           gdouble   x,
                           gdouble   y,
                           gpointer  user_data)
{
    g_print ("button press\n");
}

static void
pw_canvas_button_release_cb (PwCanvas *self,
                             gint      n_press,
                             gdouble   x,
                             gdouble   y,
                             gpointer  user_data)
{
    g_print ("button release\n");
}

static void
pw_canvas_enter_cb (PwCanvas *self,
                    gdouble   x,
                    gdouble   y,
                    gpointer  user_data)
{
    gtk_widget_grab_focus (GTK_WIDGET (self));
    g_print ("enter\n");
}

static void
pw_canvas_leave_cb (PwCanvas *self,
                    gdouble   x,
                    gdouble   y,
                    gpointer  user_data)
{
    g_print ("leave\n");
}

static void
pw_canvas_motion_cb (PwCanvas *self,
                     gdouble   x,
                     gdouble   y,
                     gpointer  user_data)
{
}

static gboolean
pw_canvas_key_pressed (PwCanvas*       self,
                       guint           keyval,
                       guint           keycode,
                       GdkModifierType state,
                       gpointer        user_data)
{
    g_print ("key press\n");
    return TRUE;
}

static gboolean
pw_canvas_key_released (PwCanvas*       self,
                        guint           keyval,
                        guint           keycode,
                        GdkModifierType state,
                        gpointer        user_data)
{
    g_print ("key release\n");
    return TRUE;
}

GtkWidget *
pw_canvas_new (void)
{
    return g_object_new (PW_TYPE_CANVAS, NULL);
}
