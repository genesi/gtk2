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

#if defined(GTK_DISABLE_SINGLE_INCLUDES) && !defined (__GTK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gtk/gtk.h> can be included directly."
#endif

#ifndef __UBUNTU_MENU_PROXY_H__
#define __UBUNTU_MENU_PROXY_H__

#include <gtk/gtkwidget.h>
#include <gtk/gtktypeutils.h>

G_BEGIN_DECLS

#define UBUNTU_TYPE_MENU_PROXY           (ubuntu_menu_proxy_get_type ())
#define UBUNTU_MENU_PROXY(o)             (G_TYPE_CHECK_INSTANCE_CAST ((o), UBUNTU_TYPE_MENU_PROXY, UbuntuMenuProxy))
#define UBUNTU_MENU_PROXY_CLASS(k)       (G_TYPE_CHECK_CLASS_CAST ((k), UBUNTU_TYPE_MENU_PROXY, UbuntuMenuProxyClass))
#define UBUNTU_IS_MENU_PROXY(o)          (G_TYPE_CHECK_INSTANCE_TYPE ((o), UBUNTU_TYPE_MENU_PROXY))
#define UBUNTU_IS_MENU_PROXY_CLASS(k)    (G_TYPE_CHECK_CLASS_TYPE ((k), UBUNTU_TYPE_MENU_PROXY))
#define UBUNTU_MENU_PROXY_GET_CLASS(o)   (G_TYPE_INSTANCE_GET_CLASS ((o), UBUNTU_TYPE_MENU_PROXY, UbuntuMenuProxyClass))


typedef struct _UbuntuMenuProxy      UbuntuMenuProxy;
typedef struct _UbuntuMenuProxyClass UbuntuMenuProxyClass;

struct _UbuntuMenuProxy
{
  GObject parent_object;
};

struct _UbuntuMenuProxyClass
{
  GObjectClass parent_class;

  /* vtable */
  void     (* insert)     (UbuntuMenuProxy *proxy, GtkWidget *parent, GtkWidget *child, guint position);
  gboolean (* show_local) (UbuntuMenuProxy *proxy);

  /* signals */
  void (* inserted)  (UbuntuMenuProxy *proxy, GtkWidget *child);
};

GType              ubuntu_menu_proxy_get_type      (void) G_GNUC_CONST;
UbuntuMenuProxy*   ubuntu_menu_proxy_get           (void);
void               ubuntu_menu_proxy_insert        (UbuntuMenuProxy *proxy,
                                                    GtkWidget       *parent,
                                                    GtkWidget       *child,
                                                    guint            position);
gboolean           ubuntu_menu_proxy_show_local    (UbuntuMenuProxy *proxy);
void               ubuntu_menu_proxy_activate_menu (UbuntuMenuProxy *proxy,
                                                    GtkWidget       *widget);

G_END_DECLS

#endif /* __UBUNTU_MENU_PROXY_H__ */
