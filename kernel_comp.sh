#!/bin/sh

sudo dpkg -r linux-headers-3.13.11-ckt39-custom linux-image-3.13.11-ckt39-custom
sudo update-grub
fakeroot make-kpkg --initrd --append-to-version=-custom kernel_image kernel_headers
sudo dpkg -i ../linux-headers-3.13.11-ckt39-custom_3.13.11-ckt39-custom-10.00.Custom_i386.deb ../linux-image-3.13.11-ckt39-custom_3.13.11-ckt39-custom-10.00.Custom_i386.deb
sudo update-grub
