/*
 * Copyright (C) 2010 Canonical, Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Authors: Cody Russell <bratsche@gnome.org>
 */

#include "config.h"
#include "gtkintl.h"
#include "gtkmarshalers.h"
#include "ubuntumenuproxy.h"
#include "ubuntumenuproxymodule.h"
#include "gtkmodules.h"
#include "gtkprivate.h"
#include "gtkalias.h"

enum {
  PROP_0,
  PROP_SHOW_LOCAL
};

enum {
  INSERTED,
  LOCAL_NOTIFY,
  ACTIVATE_MENU,
  LAST_SIGNAL
};

#define UBUNTU_MENU_PROXY_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), UBUNTU_TYPE_MENU_PROXY, UbuntuMenuProxyPrivate))

typedef struct _UbuntuMenuProxyPrivate UbuntuMenuProxyPrivate;

struct _UbuntuMenuProxyPrivate
{
  gboolean show_local;
};

static guint               menu_proxy_signals[LAST_SIGNAL] = { 0 };
static GObjectClass       *parent_class = NULL;
static UbuntuMenuProxy    *proxy_singleton = NULL;

static void     ubuntu_menu_proxy_real_insert     (UbuntuMenuProxy *proxy,
                                                   GtkWidget    *parent,
                                                   GtkWidget    *child,
                                                   guint         position);
static gboolean ubuntu_menu_proxy_real_show_local (UbuntuMenuProxy *proxy);



/* --------------------------------------------------------- */

G_DEFINE_TYPE (UbuntuMenuProxy, ubuntu_menu_proxy, G_TYPE_OBJECT)

static GObject *
ubuntu_menu_proxy_constructor (GType                  type,
                               guint                  n_params,
                               GObjectConstructParam *params)
{
  GObject *object;

  if (proxy_singleton != NULL)
    {
      object = g_object_ref (proxy_singleton);
    }
  else
    {
      object = G_OBJECT_CLASS (ubuntu_menu_proxy_parent_class)->constructor (type,
                                                                             n_params,
                                                                             params);

      proxy_singleton = UBUNTU_MENU_PROXY (object);
      g_object_add_weak_pointer (object, (gpointer) &proxy_singleton);
    }

  return object;
}

static void
ubuntu_menu_proxy_init (UbuntuMenuProxy *proxy)
{
}

static void
ubuntu_menu_proxy_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  UbuntuMenuProxyPrivate *priv = UBUNTU_MENU_PROXY_GET_PRIVATE (object);

  switch (prop_id)
    {
    case PROP_SHOW_LOCAL:
      g_value_set_boolean (value, priv->show_local);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
ubuntu_menu_proxy_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  UbuntuMenuProxyPrivate *priv = UBUNTU_MENU_PROXY_GET_PRIVATE (object);

  switch (prop_id)
    {
    case PROP_SHOW_LOCAL:
      priv->show_local = g_value_get_boolean (value);
      g_signal_emit (object, menu_proxy_signals[LOCAL_NOTIFY], 0, priv->show_local);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
ubuntu_menu_proxy_class_init (UbuntuMenuProxyClass *class)
{
  GObjectClass *object_class = G_OBJECT_CLASS (class);

  parent_class = g_type_class_peek_parent (class);

  object_class->get_property = ubuntu_menu_proxy_get_property;
  object_class->set_property = ubuntu_menu_proxy_set_property;

  g_object_class_install_property (object_class,
                                   PROP_SHOW_LOCAL,
                                   g_param_spec_boolean ("show-local",
                                                         P_("Show the local menu"),
                                                         P_("Whether the menu is displayed locally"),
                                                         FALSE,
                                                         GTK_PARAM_READWRITE));

  menu_proxy_signals[INSERTED] =
    g_signal_new (I_("inserted"),
                  G_TYPE_FROM_CLASS (class),
                  G_SIGNAL_RUN_LAST,
                  G_STRUCT_OFFSET (UbuntuMenuProxyClass, inserted),
                  NULL, NULL,
                  _gtk_marshal_VOID__OBJECT_UINT,
                  G_TYPE_NONE, 2,
                  GTK_TYPE_WIDGET, G_TYPE_UINT);

  menu_proxy_signals[LOCAL_NOTIFY] =
    g_signal_new (I_("local-notify"),
                  G_TYPE_FROM_CLASS (class),
                  G_SIGNAL_RUN_LAST,
                  NULL,
                  NULL, NULL,
                  _gtk_marshal_VOID__BOOLEAN,
                  G_TYPE_NONE, 1,
                  G_TYPE_BOOLEAN);

  menu_proxy_signals[ACTIVATE_MENU] =
    g_signal_new (I_("activate-menu"),
                  G_TYPE_FROM_CLASS (class),
                  G_SIGNAL_RUN_LAST,
                  NULL,
                  NULL, NULL,
                  _gtk_marshal_VOID__OBJECT,
                  G_TYPE_NONE, 1,
                  G_TYPE_OBJECT);

  class->insert = ubuntu_menu_proxy_real_insert;
  class->show_local = ubuntu_menu_proxy_real_show_local;

  object_class->constructor = ubuntu_menu_proxy_constructor;

  g_type_class_add_private (object_class, sizeof (UbuntuMenuProxyPrivate));
}

UbuntuMenuProxy *
ubuntu_menu_proxy_get (void)
{
  if (!proxy_singleton)
    {
      ubuntu_menu_proxy_module_get ();
    }

  return proxy_singleton;
}

static void
ubuntu_menu_proxy_real_insert (UbuntuMenuProxy *proxy,
                               GtkWidget    *parent,
                               GtkWidget    *child,
                               guint         position)
{
}

static gboolean
ubuntu_menu_proxy_real_show_local (UbuntuMenuProxy *proxy)
{
  return TRUE;
}

void
ubuntu_menu_proxy_insert (UbuntuMenuProxy *proxy,
                          GtkWidget    *parent,
                          GtkWidget    *child,
                          guint         position)
{
  g_return_if_fail (UBUNTU_IS_MENU_PROXY (proxy));

  UBUNTU_MENU_PROXY_GET_CLASS (proxy)->insert (proxy,
                                               parent,
                                               child,
                                               position);
}

gboolean
ubuntu_menu_proxy_show_local (UbuntuMenuProxy *proxy)
{
  g_return_val_if_fail (UBUNTU_IS_MENU_PROXY (proxy), TRUE);

  return UBUNTU_MENU_PROXY_GET_CLASS (proxy)->show_local (proxy);
}

void
ubuntu_menu_proxy_activate_menu (UbuntuMenuProxy *proxy,
                                 GtkWidget       *widget)
{
  g_signal_emit (proxy, menu_proxy_signals[ACTIVATE_MENU], 0, widget);
}

#define __UBUNTU_MENU_PROXY_C__
#include "gtkaliasdef.c"
