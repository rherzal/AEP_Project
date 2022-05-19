# Base this image on core-image-minimal
include recipes-core/images/core-image-minimal.bb
inherit extrausers

# Include modules in root


IMAGE_FEATURES += "ssh-server-dropbear splash"


EXTRA_USERS_PARAMS = "usermod --password \$(openssl passwd -6 aep2022) root;"

IMAGE_INSTALL:append = " hello avahi-daemon restserver gui startup"
CORE_IMAGE_EXTRA_INSTALL += " dhcpcd net-tools ncurses"

