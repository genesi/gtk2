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

#ifndef __UBUNTU_MENU_PROXY_MODULE_H__
#define __UBUNTU_MENU_PROXY_MODULE_H__

#include <glib-object.h>
#include <gmodule.h>

G_BEGIN_DECLS

#define UBUNTU_TYPE_MENU_PROXY_MODULE         (ubuntu_menu_proxy_module_get_type ())
#define UBUNTU_MENU_PROXY_MODULE(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), UBUNTU_TYPE_MENU_PROXY_MODULE, UbuntuMenuProxyModule))
#define UBUNTU_MENU_PROXY_MODULE_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST ((k), UBUNTU_TYPE_MENU_PROXY_MODULE, UbuntuMenuProxyModuleClass))
#define UBUNTU_IS_MENU_MODULE_PROXY(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), UBUNTU_TYPE_MENU_PROXY_MODULE))
#define UBUNTU_IS_MENU_PROXY_MODULE_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), UBUNTU_TYPE_MENU_PROXY_MODULE))
#define UBUNTU_MENU_PROXY_MODULE_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), UBUNTU_TYPE_MENU_PROXY_MODULE, UbuntuMenuProxyModuleClass))

typedef struct _UbuntuMenuProxyModule        UbuntuMenuProxyModule;
typedef struct _UbuntuMenuProxyModuleClass   UbuntuMenuProxyModuleClass;
typedef struct _UbuntuMenuProxyModulePrivate UbuntuMenuProxyModulePrivate;

struct _UbuntuMenuProxyModule
{
  GTypeModule parent_instance;

  UbuntuMenuProxyModulePrivate *priv;

  GModule *library;
  gchar   *name;

  void        (* load)     (UbuntuMenuProxyModule *module);
  void        (* unload)   (UbuntuMenuProxyModule *module);
};

struct _UbuntuMenuProxyModuleClass
{
  GTypeModuleClass parent_class;
};

GType                  ubuntu_menu_proxy_module_get_type (void) G_GNUC_CONST;

UbuntuMenuProxyModule *ubuntu_menu_proxy_module_get      (void);

G_END_DECLS

#endif /* __UBUNTU_MENU_PROXY_MODULE_H__ */
